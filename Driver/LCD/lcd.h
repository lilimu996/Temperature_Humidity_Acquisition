#ifndef __LCD_H
#define __LCD_H

#include "SWM341.h"
#include "ugui.h"



typedef struct
{
  uint16_t width;			/*lcd的水平像素*/
  uint16_t height;			/*lcd的竖直像素*/
} LCD_DEV;


extern LCD_DEV lcddev;



/*---------------LCD_PORT----------------*/
	#define LCD_GPIO_RST                GPIOD
    #define LCD_PIN_RST                 PIN1

    #define LCD_GPIO_BL                 GPIOD
    #define LCD_PIN_BL                  PIN9

    #define LCD_PORT_BL                 PORTD
    #define LCD_PORT_FUNC_BL            PORTD_PIN9_PWM1B
    #define LCD_PWMN_BL                 PWM1
    #define LCD_PWMN_MSK_BL             PWM1_MSK



/*---------------分辨率----------------*/
#define LCD_HDOT		(480)
#define LCD_VDOT		(272)
#define LCD_DIRH	1		// 水平显示？


void lcd_init(void);
void draw_point(uint16_t x,uint16_t y,uint32_t color);
void fill_color(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t color);


void ug_init();




#endif
