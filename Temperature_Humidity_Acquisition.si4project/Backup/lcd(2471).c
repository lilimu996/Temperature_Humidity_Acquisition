#include "lcd.h"


/** A screen sized buffer */
//uint32_t LCD_Buffer[1024*600] __attribute__((section(".SDRAM1")));
//UG_GUI gui;

LCD_DEV lcddev={0};


/*******************************************************************************************************************************************
 * Public Function
 *******************************************************************************************************************************************/
/**
 * @brief   初始化 LCD 模块, 并根据实际分辨率进行配置
 * @note    若用户选择了自定义的屏, 仅 LCD 屏参适配项 与 初始化时序 需要根据不同的屏进行适配调整
 */
void lcd_init(void)
{
	
	uint32_t i;
	LCD_InitStructure LCD_initStruct;
	
	/* 复位时序请参考屏幕厂家提供的规格书描述进行 */
    GPIO_Init(LCD_GPIO_RST, LCD_PIN_RST, 1, 1, 0, 0);
    GPIO_AtomicClrBit(LCD_GPIO_RST, LCD_PIN_RST);
    for(i = 0; i < 1000000; i++) __NOP();
    GPIO_AtomicSetBit(LCD_GPIO_RST, LCD_PIN_RST); 
    /* 注意:若屏幕需要进行特定时序/参数的初始化（如SPI）,则应在 复位后~LCD_Start前 之间进行 */
	
	/*点亮背光*/
	GPIO_Init(LCD_GPIO_BL, LCD_PIN_BL, 1, 1, 0, 0);
	GPIO_AtomicSetBit(LCD_GPIO_BL, LCD_PIN_BL); 
	
	lcd_port_init();

	lcddev.width  = (uint8_t)LCD_HDOT;
	lcddev.height = (uint8_t)LCD_VDOT;
	
	LCD_initStruct.ClkDiv = 3;
	LCD_initStruct.Format = LCD_FMT_RGB888;
	LCD_initStruct.HnPixel = LCD_HDOT;
	LCD_initStruct.VnPixel = LCD_VDOT;
	LCD_initStruct.Hfp = 64;
	LCD_initStruct.Hbp = 140;
	LCD_initStruct.Vfp = 12;
	LCD_initStruct.Vbp = 20;
	LCD_initStruct.HsyncWidth = 20;
	LCD_initStruct.VsyncWidth = 3;
	LCD_initStruct.DataSource = (uint32_t)SDRAMM_BASE;
	LCD_initStruct.Background = C_RED;
	LCD_initStruct.SampleEdge = LCD_SAMPLE_FALL;	// ATK-4342 RGBLCD 下降沿采样
	LCD_initStruct.IntEOTEn = 1;
	LCD_Init(LCD, &LCD_initStruct);
	    
}


/**
 * @brief   初始化 LCD 驱动端口
 */
void lcd_port_init(void)
{
	
	/* R- 8 bit : [ 0 ~ 7 ] */
	PORT_Init(PORTC, PIN4, PORTC_PIN4_LCD_R0, 0);
	PORT_Init(PORTC, PIN5, PORTC_PIN5_LCD_R1, 0);
	PORT_Init(PORTC, PIN8, PORTC_PIN8_LCD_R2, 0);
	PORT_Init(PORTC, PIN9, PORTC_PIN9_LCD_R3, 0);
	PORT_Init(PORTC, PIN10, PORTC_PIN10_LCD_R4, 0);
	PORT_Init(PORTC, PIN11, PORTC_PIN11_LCD_R5, 0);
	PORT_Init(PORTC, PIN12, PORTC_PIN12_LCD_R6, 0);
	PORT_Init(PORTC, PIN13, PORTC_PIN13_LCD_R7, 0);

	/* G- 8 bit : [ 0 ~ 7 ] */
	PORT_Init(PORTA, PIN12, PORTA_PIN12_LCD_G0, 0);
	PORT_Init(PORTA, PIN13, PORTA_PIN13_LCD_G1, 0);
	PORT_Init(PORTA, PIN14, PORTA_PIN14_LCD_G2, 0);
	PORT_Init(PORTA, PIN15, PORTA_PIN15_LCD_G3, 0);
	PORT_Init(PORTC, PIN0, PORTC_PIN0_LCD_G4, 0);
	PORT_Init(PORTC, PIN1, PORTC_PIN1_LCD_G5, 0);
	PORT_Init(PORTC, PIN2, PORTC_PIN2_LCD_G6, 0);
	PORT_Init(PORTC, PIN3, PORTC_PIN3_LCD_G7, 0);

	/* B- 8 bit : [ 0 ~ 7 ] */
	PORT_Init(PORTB, PIN1, PORTB_PIN1_LCD_B0, 0);
	PORT_Init(PORTB, PIN11, PORTB_PIN11_LCD_B1, 0);
	PORT_Init(PORTB, PIN13, PORTB_PIN13_LCD_B2, 0);
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


//void LCD_Handler(void)
//{
//	LCD_INTClr(LCD);
//	
//	LCD_Start(LCD);
//}

#if 1
void MemoryInit(void)
{
	SDRAM_InitStructure SDRAM_InitStruct;
	
	PORT_Init(PORTM, PIN13, PORTM_PIN13_SDR_CLK, 0);
	PORT_Init(PORTM, PIN14, PORTM_PIN14_SDR_CKE, 0);
	PORT_Init(PORTB, PIN7,  PORTB_PIN7_SDR_WE,   0);
	PORT_Init(PORTB, PIN8,  PORTB_PIN8_SDR_CAS,  0);
	PORT_Init(PORTB, PIN9,  PORTB_PIN9_SDR_RAS,  0);
	PORT_Init(PORTB, PIN10, PORTB_PIN10_SDR_CS,  0);
	PORT_Init(PORTE, PIN15, PORTE_PIN15_SDR_BA0, 0);
	PORT_Init(PORTE, PIN14, PORTE_PIN14_SDR_BA1, 0);
	PORT_Init(PORTN, PIN14, PORTN_PIN14_SDR_A0,  0);
	PORT_Init(PORTN, PIN13, PORTN_PIN13_SDR_A1,  0);
	PORT_Init(PORTN, PIN12, PORTN_PIN12_SDR_A2,  0);
	PORT_Init(PORTN, PIN11, PORTN_PIN11_SDR_A3,  0);
	PORT_Init(PORTN, PIN10, PORTN_PIN10_SDR_A4,  0);
	PORT_Init(PORTN, PIN9,  PORTN_PIN9_SDR_A5,   0);
	PORT_Init(PORTN, PIN8,  PORTN_PIN8_SDR_A6,   0);
	PORT_Init(PORTN, PIN7,  PORTN_PIN7_SDR_A7,   0);
	PORT_Init(PORTN, PIN6,  PORTN_PIN6_SDR_A8,   0);
	PORT_Init(PORTN, PIN3,  PORTN_PIN3_SDR_A9,   0);
	PORT_Init(PORTN, PIN15, PORTN_PIN15_SDR_A10, 0);
	PORT_Init(PORTN, PIN2,  PORTN_PIN2_SDR_A11,  0);
	PORT_Init(PORTM, PIN15, PORTM_PIN15_SDR_A12, 0);
	PORT_Init(PORTE, PIN7,  PORTE_PIN7_SDR_D0,   1);
	PORT_Init(PORTE, PIN6,  PORTE_PIN6_SDR_D1,   1);
	PORT_Init(PORTE, PIN5,  PORTE_PIN5_SDR_D2,   1);
	PORT_Init(PORTE, PIN4,  PORTE_PIN4_SDR_D3,   1);
	PORT_Init(PORTE, PIN3,  PORTE_PIN3_SDR_D4,   1);
	PORT_Init(PORTE, PIN2,  PORTE_PIN2_SDR_D5,   1);
	PORT_Init(PORTE, PIN1,  PORTE_PIN1_SDR_D6,   1);
	PORT_Init(PORTE, PIN0,  PORTE_PIN0_SDR_D7,   1);
	PORT_Init(PORTE, PIN8,  PORTE_PIN8_SDR_D8,   1);
	PORT_Init(PORTE, PIN9,  PORTE_PIN9_SDR_D9,   1);
	PORT_Init(PORTE, PIN10, PORTE_PIN10_SDR_D10, 1);
	PORT_Init(PORTE, PIN11, PORTE_PIN11_SDR_D11, 1);
	PORT_Init(PORTE, PIN12, PORTE_PIN12_SDR_D12, 1);
	PORT_Init(PORTE, PIN13, PORTE_PIN13_SDR_D13, 1);
	PORT_Init(PORTC, PIN14, PORTC_PIN14_SDR_D14, 1);
	PORT_Init(PORTC, PIN15, PORTC_PIN15_SDR_D15, 1);
	PORT_Init(PORTB, PIN6,  PORTB_PIN6_SDR_LDQM, 0);
	PORT_Init(PORTM, PIN12, PORTM_PIN12_SDR_UDQM,0);
	
	SDRAM_InitStruct.Size = SDRAM_SIZE_8MB;
	SDRAM_InitStruct.ClkDiv = SDRAM_CLKDIV_1;
	SDRAM_InitStruct.CASLatency = SDRAM_CASLATENCY_2;
	SDRAM_InitStruct.RefreshTime = 64;
	SDRAM_InitStruct.TimeTRP  = SDRAM_TRP_3;
	SDRAM_InitStruct.TimeTRCD = SDRAM_TRCD_3;
	SDRAM_InitStruct.TimeTRC  = SDRAM_TRC_15;
	SDRAM_Init(&SDRAM_InitStruct);
}
#endif
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


#if 0
/*----------------在屏幕上绘制像素点----------------*/
void _HW_DrawPoint(UG_S16 x, UG_S16 y, UG_COLOR c)
{	
#if LCD_DIRH
	LCD_Buffer[y * LCD_HDOT + x] = c;
#else
	LCD_Buffer[(LCD_VDOT - x) * LCD_HDOT + y] = c;
#endif
}

/*----------------ugui初始化----------------*/
void ug_init(void)
{
#if LCD_DIRH
	UG_Init(&gui,(void(*)(UG_S16,UG_S16,UG_COLOR))_HW_DrawPoint, LCD_HDOT, LCD_VDOT);
#else
	UG_Init(&gui,(void(*)(UG_S16,UG_S16,UG_COLOR))_HW_DrawPoint, LCD_VDOT, LCD_HDOT);
#endif

}
#endif



