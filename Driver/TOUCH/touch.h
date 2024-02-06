#ifndef __TOUCH_H
#define __TOUCH_H

#include "SWM341.h"


/*******************************************************************************************************************************************
 * Private Define
 *******************************************************************************************************************************************/
/** 触摸事件枚举 */

/* 硬件 IIC */
#define Static_PORT_SCL         PORTA
#define Static_PIN_SCL          PIN1
#define Static_PIN_SCL_FUN      PORTA_PIN1_I2C0_SCL

#define Static_PORT_SDA         PORTA
#define Static_PIN_SDA          PIN0
#define Static_PIN_SDA_FUN      PORTA_PIN0_I2C0_SDA

#define Static_IIC_X            I2C0

#define Static_IIC_Start(addr)          I2C_Start(Static_IIC_X, addr, 1)
#define Static_IIC_Read(ack)            I2C_Read(Static_IIC_X, ack, 1)
#define Static_IIC_Write(data)          I2C_Write(Static_IIC_X, data, 1)
#define Static_IIC_Stop()               I2C_Stop(Static_IIC_X, 1)


#define Static_GPIO_RST         GPIOA
#define Static_PIN_RST          PIN5

#define Static_GPIO_INT         GPIOD
#define Static_PIN_INT          PIN0
#define Static_INT_IRQn         GPIOD_IRQn
#define Static_INT_Handler      GPIOD_Handler

/** 按 8 位地址的方式定义(7 bit 器件地址 + 1 bit 读写控制位) */
#define GT9x_ADDR       0xBA

/* GT9xx 部分寄存器定义 */
#define GT9x_CTRL       0x8040  /**< 控制寄存器 */
#define GT9x_CFGS       0x8047  /**< 配置寄存器 */
#define GT9x_CHECK      0x80FF  /**< 校验和寄存器 */
#define GT9x_PID        0x8140  /**< 产品ID寄存器 */

#define GT9x_GSTID      0x814E  /**< 当前检测到的触摸情况 */
#define GT9x_TP1        0x8150  /**< 第一个触摸点数据地址 */
#define GT9x_TP2        0x8158  /**< 第二个触摸点数据地址 */
#define GT9x_TP3        0x8160  /**< 第三个触摸点数据地址 */
#define GT9x_TP4        0x8168  /**< 第四个触摸点数据地址 */
#define GT9x_TP5        0x8170  /**< 第五个触摸点数据地址 */

static const uint16_t GT9x_TP_Tab[5] = {GT9x_TP1, GT9x_TP2, GT9x_TP3, GT9x_TP4, GT9x_TP5};
/*******************************************************************************************************************************************
 * Public Typedef
 *******************************************************************************************************************************************/
/** 触摸事件枚举 */
typedef enum
{
    TP_EVENT_RELEASED = 0, /**< 触屏释放 */
    TP_EVENT_PRESSED       /**< 触屏按下 */
} tp_event_t;

/** 触摸数据结构体 */
typedef struct
{
    uint16_t x;         /**< 触摸点 X 轴坐标 */
    uint16_t y;         /**< 触摸点 Y 轴坐标 */
    tp_event_t event;   /**< 触摸事件(抬起/按下/移动等等) */
    uint8_t width;      /**< 触摸点的宽度大小(Reserve) */
    uint8_t track_id;   /**< 每个触摸点的触摸轨迹(Reserve) */
} tp_data_t;

/** 触摸屏种类枚举 */
typedef enum
{
    TP_TYPE_CT = 0, /**< 电容式触摸屏 */
    TP_TYPE_RT      /**< 电阻式触摸屏 */
} tp_type_t;

/** 触摸屏工作模式 */
typedef enum
{
    TP_MODE_POLLING_RDONLY = 0, /**< 轮询模式 */
    TP_MODE_INT_RX              /**< 中断接收模式(INT触发) */
} tp_mode_t;


/** 触摸屏设备类 */
typedef struct
{
    tp_data_t *point;          /**< 触摸点数据 */
    const uint8_t points_num;  /**< 触摸点上限 */
    const tp_type_t type;      /**< 触摸设备类型 */
    const tp_mode_t mode;      /**< 触摸设备工作模式 */

    /** (return: 0 - success    other - error_code)<触摸设备初始化>(None) */
    uint8_t (*const init_cb)(void);

    /** (返回读取到的触点信息的个数)<读取触摸点数据>(触摸点数据, 期望读取的触摸点数) */
    uint8_t (*const read_cb)(tp_data_t *p_data, uint8_t points);
    
    /** 关闭触摸设备(eg: 低功耗) */
    void (*const close_cb)(void);
} dev_tp_t;


/*******************************************************************************************************************************************
 * Public Variable
 *******************************************************************************************************************************************/
/** 触摸屏设备 */
extern dev_tp_t Dev_TP;

/*******************************************************************************************************************************************
 * Public Function
 *******************************************************************************************************************************************/
uint8_t gt9x_init(void);
uint8_t gt9x_read_points(tp_data_t *p_data, uint8_t points);
static void iic_delay(void);
static void touch_close(void);
#endif
