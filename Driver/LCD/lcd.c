#include "lcd.h"


LCD_DEV lcddev={0};
/*******************************************************************************************************************************************
 * Private Prototype
 *******************************************************************************************************************************************/
static void lcd_set_parameter(LCD_InitStructure *lcd_parameter);
static void lcd_port_init(void);


/*******************************************************************************************************************************************
 * Public Function
 *******************************************************************************************************************************************/
/**
 * @brief   初始化 LCD 模块, 并根据实际分辨率进行配置
 * @note    若用户选择了自定义的屏, 仅 LCD 屏参适配项 与 初始化时序 需要根据不同的屏进行适配调整
 */
void lcd_init(void)
{
	
	/* 复位时序请参考屏幕厂家提供的规格书描述进行 */
    GPIO_Init(LCD_GPIO_RST, LCD_PIN_RST, 1, 1, 0, 0);
    GPIO_AtomicClrBit(LCD_GPIO_RST, LCD_PIN_RST);
    systick_delay_ms(1);
    GPIO_AtomicSetBit(LCD_GPIO_RST, LCD_PIN_RST);
    
    /* 注意:若屏幕需要进行特定时序/参数的初始化（如SPI）,则应在 复位后~LCD_Start前 之间进行 */

    LCD_InitStructure LCD_initStruct;
    /* LCD 屏参适配（以及部分屏幕需要 SPI 初始化也在此函数内进行） */
    lcd_set_parameter(&LCD_initStruct);

    /* 分辨率及色彩 */
    LCD_initStruct.HnPixel = LCD_HDOT;
    LCD_initStruct.VnPixel = LCD_VDOT;
    LCD_initStruct.Format =  LCD_FMT_RGB565;
    /* 背景色 */
    LCD_initStruct.Background = (LCD_initStruct.Format == LCD_FMT_RGB888) ? 0xFFFFFF : 0xFFFF;
    /* 图层 1 被 lvgl 使用, 此处仅做初始化临时值, 在 disp_flush() 会切换至 lcdbuf_gui/show 帧缓冲区域 */
    LCD_initStruct.DataSource = (uint32_t)SDRAMM_BASE;
    
    /* 0-失能传输完成中断, 刷完一帧自动开始刷新下一帧(用户无须参与)
     * 1-使能传输完成中断, 须在中断内软件启动刷新下一帧(开启后可提供接口以测试实际帧率) 
     */
    LCD_initStruct.IntEOTEn = 0;

    /* LCD 端口适配 */
    lcd_port_init();

    /* LCD 模块初始化 */
    LCD_Init(LCD, &LCD_initStruct);
    
     lcddev.height = (uint16_t)LCD_VDOT;
     lcddev.width = (uint16_t)LCD_HDOT;
    /* 点亮背光 */
    GPIO_Init(LCD_GPIO_BL, LCD_PIN_BL, 1, 1, 0, 0);
    GPIO_AtomicSetBit(LCD_GPIO_BL, LCD_PIN_BL); /* 点亮背光 */
    LCD_Start(LCD);
	    
}
/*******************************************************************************************************************************************
 * Private Function
 *******************************************************************************************************************************************/
static void lcd_set_parameter(LCD_InitStructure *lcd_parameter)
{
    LCD_InitStructure LCD_initStruct;

    /*  一些屏参的计算参考示例, 实际请依据屏幕规格书为准
        HSYNC Blanking = 160 DCLK = HS Pulse Width + HS Back Porch
        HS Pulse Width = 1 ~ 140 DCLK
        1 Horizontal Line = 1344 DCLK   (1200 ~ 1400)

        VSYNC Blanking = 23 H     = VS Pulse Width + VS Back Porch
        VS Pulse Width = 1 ~ 20 H
        VSYNC period time = 635 H       (624 ~ 750)
    */
    /* [480*272] 晶力泰 4.3 寸屏 + CTP */
    LCD_initStruct.ClkDiv = 10;
    LCD_initStruct.Hfp = 5;
    LCD_initStruct.Hbp = 40;
    LCD_initStruct.Vfp = 8;
    LCD_initStruct.Vbp = 8;
    LCD_initStruct.HsyncWidth = 5;
    LCD_initStruct.VsyncWidth = 5;
    LCD_initStruct.SampleEdge = LCD_SAMPLE_FALL;

    lcd_parameter->ClkDiv = LCD_initStruct.ClkDiv;
    lcd_parameter->Hfp = LCD_initStruct.Hfp;
    lcd_parameter->Hbp = LCD_initStruct.Hbp;
    lcd_parameter->Vfp = LCD_initStruct.Vfp;
    lcd_parameter->Vbp = LCD_initStruct.Vbp;
    lcd_parameter->HsyncWidth = LCD_initStruct.HsyncWidth;
    lcd_parameter->VsyncWidth = LCD_initStruct.VsyncWidth;
    lcd_parameter->SampleEdge = LCD_initStruct.SampleEdge;
}


/**
 * @brief   初始化 LCD 驱动端口
 */
static void lcd_port_init(void)
{
	
	/* 针对SWM34SVET6_Demo板上使用RGB565接口时多余IO未接地, 故程序中强制拉低, 用户也可做其他用途 */

    /* R- 8 bit : [ 0 ~ 7 ] */
    GPIO_Init(GPIOC, PIN4, 1, 0, 0, 0);
    GPIO_Init(GPIOC, PIN5, 1, 0, 0, 0);
    GPIO_Init(GPIOC, PIN8, 1, 0, 0, 0);
    GPIO_AtomicClrBit(GPIOC, PIN4);
    GPIO_AtomicClrBit(GPIOC, PIN5);
    GPIO_AtomicClrBit(GPIOC, PIN8);
    /* R- 5 bit : [ 3 ~ 7 ] */
    PORT_Init(PORTC, PIN9, PORTC_PIN9_LCD_R3, 0);
    PORT_Init(PORTC, PIN10, PORTC_PIN10_LCD_R4, 0);
    PORT_Init(PORTC, PIN11, PORTC_PIN11_LCD_R5, 0);
    PORT_Init(PORTC, PIN12, PORTC_PIN12_LCD_R6, 0);
    PORT_Init(PORTC, PIN13, PORTC_PIN13_LCD_R7, 0);

    /* G- 8 bit : [ 0 ~ 7 ] */
    GPIO_Init(GPIOA, PIN12, 1, 0, 0, 0);
    GPIO_Init(GPIOA, PIN13, 1, 0, 0, 0);
    GPIO_AtomicClrBit(GPIOA, PIN12);
    GPIO_AtomicClrBit(GPIOA, PIN13);
    /* G- 6 bit : [ 2 ~ 7 ] */
    PORT_Init(PORTA, PIN14, PORTA_PIN14_LCD_G2, 0);
    PORT_Init(PORTA, PIN15, PORTA_PIN15_LCD_G3, 0);
    PORT_Init(PORTC, PIN0, PORTC_PIN0_LCD_G4, 0);
    PORT_Init(PORTC, PIN1, PORTC_PIN1_LCD_G5, 0);
    PORT_Init(PORTC, PIN2, PORTC_PIN2_LCD_G6, 0);
    PORT_Init(PORTC, PIN3, PORTC_PIN3_LCD_G7, 0);

    /* B- 8 bit : [ 0 ~ 7 ] */
    GPIO_Init(GPIOB, PIN1, 1, 0, 0, 0);
    GPIO_Init(GPIOB, PIN11, 1, 0, 0, 0);
    GPIO_Init(GPIOB, PIN13, 1, 0, 0, 0);
    GPIO_AtomicClrBit(GPIOB, PIN1);
    GPIO_AtomicClrBit(GPIOB, PIN11);
    GPIO_AtomicClrBit(GPIOB, PIN13);
    /* B- 5 bit : [ 3 ~ 7 ] */
    PORT_Init(PORTB, PIN15, PORTB_PIN15_LCD_B3, 0);
    PORT_Init(PORTA, PIN2, PORTA_PIN2_LCD_B4, 0);
    PORT_Init(PORTA, PIN9, PORTA_PIN9_LCD_B5, 0);
    PORT_Init(PORTA, PIN10, PORTA_PIN10_LCD_B6, 0);
    PORT_Init(PORTA, PIN11, PORTA_PIN11_LCD_B7, 0);

    /* CLK / VS / HS / DE */
    PORT_Init(PORTB, PIN5, PORTB_PIN5_LCD_DCLK, 0);
    PORT_Init(PORTB, PIN2, PORTB_PIN2_LCD_VSYNC, 0);

    PORT_Init(PORTM, PIN8, PORTM_PIN8_LCD_HSYNC, 0);
    PORT_Init(PORTM, PIN11, PORTM_PIN11_LCD_DEN, 0);
}




/*******************************************************************************************************************************************
 * Public Function
 *******************************************************************************************************************************************/
/**
 * @brief   在指定的位置填充颜色
 * @note    
 */
//void draw_point(uint16_t x,uint16_t y,uint32_t color)
//{
//#if LCD_DIRH
//	LCD_Buffer[y * LCD_HDOT + x] = color;
//#else
//	LCD_Buffer[(LCD_VDOT - x) * LCD_HDOT + y] = c;
//#endif

//}
/*******************************************************************************************************************************************
 * Public Function
 *******************************************************************************************************************************************/
/**
 * @brief   在指定的区域填充颜色
 * @note    
 */
//void fill_color(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t color)
//{
//	uint16_t x,y;
//	
//	for(y = y1;y <= y2;y++)
//	{
//		for(x = x1;x <= x2;x++)
//		{
//			draw_point(x,y,color);
//		}
//	}
//}

/**
 * @brief   LCD ISR Callback
 */
void isr_lcd_transfer_done(void)
{
    LCD_INTClr(LCD);
    LCD_Start(LCD);
}




