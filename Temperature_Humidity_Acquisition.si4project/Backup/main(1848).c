#include "main.h"
#include "../Driver/LCD/lcd.h"
#include "ugui.h"

int main(void)
{
    
    SystemInit();
	

    GPIO_Init(GPIOA, PIN0, 0, 1, 0, 0);     //输入，上拉使能，接KEY
    GPIO_Init(GPIOA, PIN5, 1, 0, 0, 0);     //输出， 接LED
    
	MemoryInit();
	lcd_init();
	LCD_Start(LCD);
	ug_init();
	UG_FillScreen(C_RED);
    while(1==1)
    {

        if(GPIO_GetBit(GPIOA, PIN0) == 0)       //按键被按下
        {
            GPIO_SetBit(GPIOA, PIN5);
        }
        else
        {
            GPIO_ClrBit(GPIOA, PIN5);
        }
		
    }

    






}






