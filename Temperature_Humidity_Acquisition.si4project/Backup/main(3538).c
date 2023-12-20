#include "main.h"
#include "../Driver/UART/uart.h"
#include "../Driver/LCD/lcd.h"
#include "../Driver/RS485/rs485_host.h"


extern CircleBuffer_t CirBuf;

int main(void)
{
    uint32_t i;
    SystemInit();
	systick_init();
	SerialInit();
    uart2_init();
    printf("%s\r\n",__TIME__);
    GPIO_Init(GPIOA, PIN0, 0, 1, 0, 0);     //输入，上拉使能，接KEY
    GPIO_Init(GPIOA, PIN5, 1, 0, 0, 0);     //输出， 接LED
 #ifdef LCD_USE   
	MemoryInit();
	lcd_init();
	LCD_Start(LCD);
	ug_init();
	UG_FillScreen(C_RED);
#endif

	rs485_host_process(10);
	
	
	//uart2_sendBytes(MyArray,4);   
    while(1==1)
    {
       
        uart2_sendByte(0x11);
//		if(get_uart2_msgStatus())
//		{
//			clear_uart2_msgStatus();
//		}

//        if(GPIO_GetBit(GPIOA, PIN0) == 0)       //按键被按下
//        {
//            GPIO_SetBit(GPIOA, PIN5);
//        }
//        else
//        {
//            GPIO_ClrBit(GPIOA, PIN5);
//        }
       
		
    }


}






