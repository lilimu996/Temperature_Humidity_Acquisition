#include "main.h"
#include "../Driver/UART/uart.h"
#include "../Driver/LCD/lcd.h"
#include "../Driver/RS485/rs485.h"


extern CircleBuffer_t CirBuf;

int main(void)
{
    
    SystemInit();
	SerialInit();
    uart2_init();
    
    GPIO_Init(GPIOA, PIN0, 0, 1, 0, 0);     //输入，上拉使能，接KEY
    GPIO_Init(GPIOA, PIN5, 1, 0, 0, 0);     //输出， 接LED
 #ifdef LCD_USE   
	MemoryInit();
	lcd_init();
	LCD_Start(LCD);
	ug_init();
	UG_FillScreen(C_RED);
#endif
	uint8_t MyArray[] = {0x42, 0x43, 0x44, 0x45};
	uart2_sendBytes(MyArray,4);
	uart2_sendByte(1);
    uint32_t i;
    while(1==1)
    {
        uart2_sendByte(1);
		if(get_uart2_msgStatus())
		{
			clear_uart2_msgStatus();
			UART_INTEn(UART2, UART_IT_TX_THR);
		}

        if(GPIO_GetBit(GPIOA, PIN0) == 0)       //按键被按下
        {
            GPIO_SetBit(GPIOA, PIN5);
        }
        else
        {
            GPIO_ClrBit(GPIOA, PIN5);
        }
        for(i = 0; i < 1000000; i++) __NOP();
		
    }


}






