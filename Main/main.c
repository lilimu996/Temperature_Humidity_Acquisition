#include "main.h"
#include "../Driver/UART/uart.h"
#include "../Driver/LCD/lcd.h"
#include "../Driver/RS485/rs485_host.h"
#include "../Driver/TF/FatFs/ff.h"

extern CircleBuffer_t CirBuf;
extern RS485_Host_t rs485_host_device1;
FATFS fatfs;

char str[] __attribute__((aligned(4))) = 
			"Hi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\n"
			"Hi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\n"
			"Hi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\n"
			"Hi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\n"
			"Hi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\n"
			"Hi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\n"
			"Hi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\n";
char buf[1024] __attribute__((aligned(4))) = {0};


int main(void)
{
    uint32_t i;
    
    uint32_t len;
	FRESULT  res;
	FIL filw, filr;
  	/*系统初始化*/  
    SystemInit();
	systick_init();
	/*UART1初始化为打印串口*/
	SerialInit();
#ifdef RS485_USE
	/*UART2初始化为485串口*/
    uart2_init();
	/*modbus主机初始化*/
	rs485_host_init();
	/*添加modbus主机1*/
	rs485_host_add(&rs485_host_device1);
#endif
    printf("%s\r\n",__TIME__);
//    GPIO_Init(GPIOA, PIN0, 0, 1, 0, 0);     //输入，上拉使能，接KEY
//    GPIO_Init(GPIOA, PIN5, 1, 0, 0, 0);     //输出， 接LED
 #ifdef LCD_USE   
 	/*lcd初始化*/
	MemoryInit();
	lcd_init();
	LCD_Start(LCD);
	ug_init();
	UG_FillScreen(C_RED);
#endif

	
	
    uint16_t timeout = 0;
	uint8_t MyArray[] = {0x11,0x22,0x33};
	/*等待sd卡完成初始化*/
	systick_delay_ms(1);
#ifdef SD_USE
	/*sd卡文件系统读写测试*/
	/*初始化sd卡分区*/
	res = f_mount(&fatfs, "sd:", 1);
	if(res != FR_OK)
	{
		printf("sdcard init fail!\r\n");
		goto loop_forever;
	}
	/*新建文件test.txt*/
	res = f_open(&filw, "sd:test.txt", FA_CREATE_ALWAYS | FA_WRITE);
	if(res != FR_OK)
	{
		printf("create file fail!\r\n");
		goto loop_forever;
	}
	/*将str写入文件*/
	res = f_write(&filw, str, strlen(str), &len);
	if(res != FR_OK)
	{
		printf("write file fail!\r\n");
		goto loop_forever;
	}
	/*关闭文件*/
	f_close(&filw);
	/*打开文件test.txt*/
	res = f_open(&filr, "sd:test.txt", FA_OPEN_EXISTING | FA_READ);
	if(res != FR_OK)
	{
		printf("open file fail!\r\n");
		goto loop_forever;
	}
	/*读文件内容*/
	res = f_read(&filr, buf, sizeof(buf)-1, &len);
	if(res != FR_OK)
	{
		printf("read file fial!\r\n");
		goto loop_forever;
	}
	f_close(&filr);
	/*比较读写是否一致*/
	if(strcmp(buf, str) == 0)
	{
		printf("read string == write string\r\n");
	}
	else
	{
		printf("read string != write string\r\n");
	}		
loop_forever:
	while(1==1)
	{
	}
#endif	
	//uart2_sendBytes(MyArray,4);   
    while(1==1)
    {
    	//uart2_sendBytes(MyArray,3);
#ifdef RS485_USE
    	/*modbus主机测试*/
    	systick_delay_ms(1);
        rs485_host_process(10);
        timeout++;
		if(timeout == 100)
		{
			timeout = 0;
            //printf("rs485 running+%d\r\n",timeout);
			modbus_06_set_req(0x01,0x0000,0x1234);
		}
#endif
		systick_delay_ms(100);
        //printf("timeout+%d\r\n",timeout);
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






