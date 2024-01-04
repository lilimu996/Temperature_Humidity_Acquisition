/**
 * @file main.c
 *
 */


/*********************
 *      INCLUDES
 *********************/
#include "main.h"
#include "../Driver/UART/uart.h"
#include "../Driver/LCD/lcd.h"
#include "../Driver/RS485/rs485_host.h"
#include "../Driver/TF/FatFs/ff.h"
#include "../Driver/TIMER/btim.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_demo_stress.h"
#include "../Driver/SDRAM/dev_sdram.h"

/*******************************************************************************************************************************************
 * Public Variable
 *******************************************************************************************************************************************/
extern CircleBuffer_t CirBuf;
extern RS485_Host_t rs485_host_device1;
FATFS fatfs;

//char str[] __attribute__((aligned(4))) = 
//			"Hi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\n"
//			"Hi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\n"
//			"Hi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\n"
//			"Hi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\n"
//			"Hi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\n"
//			"Hi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\n"
//			"Hi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\nHi from Synwit!\n";
//char buf[1024] __attribute__((aligned(4))) = {0};

/*******************************************************************************************************************************************
 * Public Function
 *******************************************************************************************************************************************/
/**
 * @brief   C_Main
 */
int main(void)
{
    uint32_t i;
    
    uint32_t len;
	FRESULT  res;
	FIL filw, filr;
  	/*系统初始化*/  
    SystemInit();
	systick_init();
    sdram_init();
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

	/*初始化定时器、LVGL库、输入输出设备*/
#define lvgl_use 0
#if lvgl_use   
    
	btim1_lvgltim_init();
	lv_init();
	lv_port_disp_init();
    
    /*lvgl stress测试*/
    lv_demo_stress();
    //lv_demo_benchmark();
//	/*打点函数测试*/
//    uint16x2_t x,y;
//    for(x=5;x<512;x++)
//    {
//        for(y=5;y<512;y++)
//        {
//            draw_point(x,y,C_YELLOW);
//        }
//    }
    //fill_color(50,300,512,500,C_RED);
	
#endif    
	/*lvgl测试代码*/
//	lv_obj_t* switch_obj = lv_switch_create(lv_scr_act());
//	lv_obj_set_size(switch_obj, 120, 60);
//	lv_obj_align(switch_obj, LV_ALIGN_CENTER, 0, 0);
	/*通过串口1打印编译时间*/
    printf("%s\r\n",__TIME__);
//    GPIO_Init(GPIOA, PIN0, 0, 1, 0, 0);     //输入，上拉使能，接KEY
    /*初始化LED GPIO*/
    GPIO_Init(GPIOA, PIN5, 1, 0, 0, 0);     //输出， 接LED
#define LCD_USE 0
#if LCD_USE   
 	/*lcd初始化*/
	//MemoryInit();
	lcd_init();
	LCD_Start(LCD);
	ug_init();
	UG_FillScreen(C_RED);
	systick_delay_ms(2000);
	UG_FillScreen(C_GREEN);
#endif
    lcd_init();
	
	
    uint16_t timeout = 0;
	uint8_t MyArray[] = {0x11,0x22,0x33};
	/*等待sd卡完成初始化*/
	//systick_delay_ms(1);
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
    	/*每5ms调用一次lv_timer_handler*/
    	systick_delay_ms(5);
    	//lv_timer_handler();
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
        systick_delay_ms(100);
#endif
		
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






