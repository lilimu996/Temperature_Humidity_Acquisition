#include "btim.h"
#include "lvgl.h"

/****************************************************************************************************************************************** 
* 函数名称:	btim1_init()
* 功能说明:	初始化基本BTIMR1,1ms触发一次中断，为lvgl提供时基
* 输    入: uint8_t data			要发送的字节	
* 输    出: 
* 注意事项: 无
******************************************************************************************************************************************/

void btim1_lvgltim_init()
{
    /*BTIMER时钟来源      系统时钟150MHZ*/
    TIMR_Init(BTIMR1,TIMR_MODE_TIMER,150,1000,1);	//每1ms秒钟触发一次中断
    TIMR_Start(BTIMR1);
}

void BTIMR1_Handler(void)
{
	TIMR_INTClr(BTIMR1);
	/*lvgl时间，1ms*/
	lv_tick_inc(1);
	
}







