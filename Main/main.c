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

	
	
	uint16_t timeout = 0;
	//uart2_sendBytes(MyArray,4);   
    while(1==1)
    {
    	systick_delay_ms(1);
    	rs485_host_process(10);
        timeout++;
		if(timeout == 100)
		{
			timeout = 0;
			modbus_06_set_req(0x01,0x0000,0x1234);
		}
       // uart2_sendByte(0x11);
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






