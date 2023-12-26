#ifndef __LCD_H
#define __LCD_H

#include "SWM341.h"
#include "ugui.h"



typedef struct
{
  uint8_t width;			/*lcd的水平像素*/
  uint8_t height;			/*lcd的竖直像素*/
} LCD_DEV;


extern LCD_DEV lcddev;



/*---------------LCD_PORT----------------*/
#define LCD_GPIO_RST 				GPIOD
#define LCD_PIN_RST 				PIN1
#define LCD_GPIO_BL                 GPIOD
#define LCD_PIN_BL                  PIN9


/*---------------分辨率----------------*/
#define LCD_HDOT		(1024)
#define LCD_VDOT		(600)
#define LCD_DIRH	1		// 水平显示？


void lcd_init(void);
void lcd_port_init(void);
void draw_point(uint16_t x,uint16_t y,uint32_t color);

void MemoryInit(void);
void ug_init();




#endif
