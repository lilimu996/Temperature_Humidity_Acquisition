#include "touch.h"
#include "string.h"
#include "/LCD/lcd.h"


#define TP_MAX_POINTS        (5) /**< 电容屏支持的点数,固定最大为5点 */

/*******************************************************************************************************************************************
 * Public Variable
 *******************************************************************************************************************************************/
/** 触摸点数据流 */
static tp_data_t TP_Points_Data[TP_MAX_POINTS];
uint8_t iicInit(void);
static uint8_t tp_read_regs(uint16_t reg, uint8_t *buf, uint8_t len);
static uint8_t tp_write_regs(uint16_t reg, uint8_t *buf, uint8_t len);
/** 中断标志 */
typedef enum
{
    NO = 0, /**< 未触发中断 */
    OK      /**< 已触发中断 */
    /* 可以枚举拓展 ++ 累计触发次数 */
} irq_flag_t;

/** TP_INT 边沿脉冲触发标志 */
static volatile uint8_t IRQ_Flag_TP = NO;

dev_tp_t Dev_TP = {
    .point = TP_Points_Data,
    .points_num = TP_MAX_POINTS,
    .type = TP_TYPE_CT,
    .mode = TP_MODE_INT_RX,
    /* Callback Register */
    .init_cb = gt9x_init,
    .read_cb = gt9x_read_points,
    .close_cb = touch_close,

};

/*******************************************************************************************************************************************
 * Public Function
 *******************************************************************************************************************************************/
/**
 * @brief   EXTI TP_INT ISR Callback (GPIO 输入边沿中断)
 */
void isr_exti_tp_int(void)
{
    if (EXTI_State(Static_GPIO_INT, Static_PIN_INT))
    {
        EXTI_Clear(Static_GPIO_INT, Static_PIN_INT);
        IRQ_Flag_TP = OK;
    }
}
/**
 * @brief   初始化触摸设备驱动
 * @param   dev : 设备句柄
 * @retval  0     : success
 * @retval  other : error code
 */
uint8_t touch_init(dev_tp_t *dev)
{
    uint8_t res = 1;
    
    for (uint16_t i = 0; i < dev->points_num; ++i)
    {
        dev->point[i].x = 0;
        dev->point[i].y = 0;
        dev->point[i].event = TP_EVENT_RELEASED;
        dev->point[i].width = 0;
        dev->point[i].track_id = 0;
    }
    
    res = dev->init_cb();
    
    if (dev->mode == TP_MODE_INT_RX)
    {
        /* 中断方式选用边沿触发，则需要在 TP_IC 初始化中设置 TP 芯片的扫描方式为中断触发，
         * 如此才能使得长时间按压时不断触发 TP_INT 边沿脉冲信号
         */
        GPIO_Init(Static_GPIO_INT, Static_PIN_INT, 0, 0, 0, 0);
        EXTI_Init(Static_GPIO_INT, Static_PIN_INT, EXTI_FALL_EDGE); /* EXTI_FALL_EDGE - 下降沿触发 / EXTI_RISE_EDGE - 上升沿触发 */
        NVIC_EnableIRQ( Static_INT_IRQn);
        EXTI_Open(Static_GPIO_INT, Static_PIN_INT);
    }
    return res;
}

/**
 * @brief   触摸事件处理
 * @param   dev : 设备句柄
 * @retval  /
 * @note    INT 中断触发->查询扫描
 */
void touch_handler(dev_tp_t *dev)
{
    uint8_t points = 0;
    
    if (dev->mode == TP_MODE_INT_RX) /* 中断 INT 触发模式 */
    {
        if (IRQ_Flag_TP == OK)
        {
            IRQ_Flag_TP = NO;
            
            points = dev->read_cb(dev->point, 1);
            /*
            printf("Your Touch point num = [%d], event <%s>, [x] = [%d], [y] = [%d]\r\n",
                   points, (dev->point[0].event == TP_EVENT_PRESSED) ? "press" : "release", dev->point[0].x, dev->point[0].y
            );*/
        }
    }
    else if (dev->mode == TP_MODE_POLLING_RDONLY) /* 轮询读取模式 */
    {
        points = dev->read_cb(dev->point, 1);
    }

    if (dev->point->event == TP_EVENT_PRESSED)
    {
        /* 手指触摸释放时长 */
        extern volatile uint32_t Systick_Ms_TP;
        Systick_Ms_TP = 0;
    }
}
/**
 * @brief   初始化 TP_IC 
 * @param   /
 * @retval  0     : success
 * @retval  other : error code
 */
uint8_t gt9x_init(void)
{
    uint8_t temp[5] = {0};

    iicInit();

    GPIO_Init(Static_GPIO_INT, Static_PIN_INT, 0, 0, 1, 0); /* 设置下拉, 选中 IIC 地址 */

    GPIO_Init(Static_GPIO_RST, Static_PIN_RST, 1, 1, 0, 0); /* 复位 */
    GPIO_AtomicClrBit(Static_GPIO_RST, Static_PIN_RST);
    systick_delay_ms(10);
    GPIO_AtomicSetBit(Static_GPIO_RST, Static_PIN_RST);
    systick_delay_ms(60);

    temp[0] = 0x02;
    tp_write_regs(GT9x_CTRL, temp, 1); /* 软复位 */
    systick_delay_ms(100);
    temp[0] = 0x00;
    tp_write_regs(GT9x_CTRL, temp, 1); /* 软复位结束 */
    systick_delay_ms(100);
    
    tp_read_regs(GT9x_PID, temp, 4);
    //printf("Touch IC id:%s\r\n", temp);
     if (NULL != strstr((const char *)temp, "911")) /* ID 验证 */
    {
        printf("GT911 is Ready!\r\n");
        return 1;
    }
    return 0;
}
/**
 * @brief   读取触摸点数据
 * @param   p_data : 触摸点数据
 * @param   points : 需要读取的触点个数
 * @retval  返回读取到的触点信息的个数
 */
uint8_t gt9x_read_points(tp_data_t *p_data, uint8_t points)
{
    uint8_t touch_status = 0, touch_points = 0, temp = 0, i = 0;
    uint8_t buf[5] = {0};

    tp_read_regs(GT9x_GSTID, &touch_status, 1);
    /* 触摸点有效 */
    if ( (touch_status & 0x80) && ((touch_status & 0x0F) < 6))
    {
        temp = 0;
        tp_write_regs(GT9x_GSTID, &temp, 1); /* 清除 READY 标志 */
        
        touch_points = points;
        /* 期望读取的触摸点数已超过实际驱动中可读取的最大点数 */
        if (touch_points > (touch_status & 0x0F))
            touch_points = touch_status & 0x0F;
        
        if (touch_points == 0) /* 无触摸点按下 */
        {
            p_data[i].event = TP_EVENT_RELEASED;
            return 0;
        }
        
        for (i = 0; i < touch_points; ++i)
        {
            tp_read_regs(GT9x_TP_Tab[i], buf, 4); /* 读取 X/Y 坐标值 */

            /* 个别屏模组的 TP_IC 型号虽相同, 但其基准原点不一定相同(屏幕模组液晶装配位置),
             * 需要在此添加偏移手动校准, 如读者使用本例程未包含的屏幕型号模组, 请自己尝试添加偏移修正
             */
            uint16_t temp_l = (((uint16_t)buf[1] << 8) + buf[0]);
            uint16_t temp_h = (((uint16_t)buf[3] << 8) + buf[2]);
            //printf("[temp_l] = [%d], [temp_h] = [%d]\r\n", temp_l, temp_h);
            
            /* 异常坐标值抛弃 */
            if (temp_l == 0xFFFF || temp_h == 0xFFFF)
            {
                continue;
            }
            /* 坐标值有效, 视为按下 */
            p_data[i].event = TP_EVENT_PRESSED;
            
            p_data[i].x = /*LCD_HDOT -*/ temp_l; // x 坐标偏移

            p_data[i].y = LCD_VDOT - temp_h; /* y 坐标偏移 */
        }
    }
    return touch_points;
}
/*******************************************************************************************************************************************
 * Pravite Function
 *******************************************************************************************************************************************/


/**
 * @brief   初始化 IIC
 * @param   /
 * @retval  0     : success
 * @retval  other : error code
 */
uint8_t iicInit(void){
	I2C_InitStructure I2C_initStruct; 
    PORT_Init(Static_PORT_SCL, Static_PIN_SCL, Static_PIN_SCL_FUN, 1); 
    Static_PORT_SCL->PULLU |= (1 << Static_PIN_SCL); 
    Static_PORT_SCL->OPEND |= (1 << Static_PIN_SCL); 
    PORT_Init(Static_PORT_SDA, Static_PIN_SDA, Static_PIN_SDA_FUN, 1); 
    Static_PORT_SDA->PULLU |= (1 << Static_PIN_SDA); 
    Static_PORT_SDA->OPEND |= (1 << Static_PIN_SDA); 
    I2C_initStruct.Master = 1; 
    I2C_initStruct.Addr10b = 0; 
    I2C_initStruct.MstClk = 400000; 
    I2C_initStruct.TXEmptyIEn = 0; 
    I2C_initStruct.RXNotEmptyIEn = 0; 
    I2C_Init(Static_IIC_X, &I2C_initStruct); 
    I2C_Open(Static_IIC_X); 
	return 0;
}
/**
 * @brief   iic 延时
 */
static void iic_delay(void)
{
    for (uint32_t i = 0; i < CyclesPerUs * 8; ++i)
        __NOP();
}
/**
 * @brief   读取从机寄存器
 */
static uint8_t tp_read_regs(uint16_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    uint8_t ack;

    ack = Static_IIC_Start(GT9x_ADDR | 0);
    if (ack == 0)
        goto rd_fail;

    ack = Static_IIC_Write(reg >> 8);
    if (ack == 0)
        goto rd_fail;

    ack = Static_IIC_Write(reg & 0XFF);
    if (ack == 0)
        goto rd_fail;

    iic_delay(); /* 此处必须延时等待一会再启动 */

    ack = Static_IIC_Start(GT9x_ADDR | 1); /* ReStart */
    if (ack == 0)
        goto rd_fail;

    for (i = 0; i < len - 1; i++)
    {
        buf[i] = Static_IIC_Read(1);
    }
    buf[i] = Static_IIC_Read(0);

    Static_IIC_Stop();
    iic_delay();
    return 0;

rd_fail:
    Static_IIC_Stop();
    iic_delay();
    return 1;
}

/**
 * @brief   写入从机寄存器
 */
static uint8_t tp_write_regs(uint16_t reg, uint8_t *buf, uint8_t len)
{
    uint32_t i;
    uint8_t ack;

    ack = Static_IIC_Start(GT9x_ADDR | 0);
    if (ack == 0)
        goto wr_fail;

    ack = Static_IIC_Write(reg >> 8);
    if (ack == 0)
        goto wr_fail;

    ack = Static_IIC_Write(reg & 0XFF);
    if (ack == 0)
        goto wr_fail;

    for (i = 0; i < len; i++)
    {
        ack = Static_IIC_Write(buf[i]);
        if (ack == 0)
            goto wr_fail;
    }

    Static_IIC_Stop();
    iic_delay();
    return 0;

wr_fail:
    Static_IIC_Stop();
    iic_delay();
    return 1;
}
/**
 * @brief   关闭 Touch 设备通讯接口, 进入低功耗前使用
 * @note    Touch IC 自身一般支持通过发送指令设置来进入低功耗/休眠模式, 详见各型号数据手册/驱动实现.
 */
static void touch_close(void)
{
    NVIC_DisableIRQ(Static_INT_IRQn);
    EXTI_Close(Static_GPIO_INT, Static_PIN_INT);
    I2C_Close(Static_IIC_X );
}
