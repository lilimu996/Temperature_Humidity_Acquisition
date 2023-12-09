#ifndef __LCD_H
#define __LCD_H

#include "SWM341.h"

/*---------------LCD_PORT----------------*/
#define LCD_GPIO_RST 				GPIOD
#define LCD_PIN_RST 				PIN1
#define LCD_GPIO_BL                 GPIOD
#define LCD_PIN_BL                  PIN9


/*---------------分辨率----------------*/
#define LCD_HDOT		(1024)
#define LCD_VDOT		(600)


void lcd_init(void);
void lcd_port_init(void);
void MemoryInit(void);




#endif
