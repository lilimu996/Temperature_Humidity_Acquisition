/**
 *******************************************************************************************************************************************
 * @file        dev_systick.c
 * @brief       系统滴答定时器
 * @details     /
 * @since       Change Logs:
 * Date         Author       Notes
 * 2022-12-08   lzh          the first version
 * @remark		/
 *******************************************************************************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION
 * REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
 * FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
 * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
 * -ECTION WITH THEIR PRODUCTS.
 *
 * @copyright   2012 Synwit Technology
 *******************************************************************************************************************************************
 */
#include "dev_systick.h"

/** SysTick ticks */
static volatile uint32_t Systick_Tick = 0;

void systick_init(void)
{
    /* SystemFrequency / 1000  =>  1ms中断一次 */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        /* Capture error */
        while (1)
            ;
    }
}

void systick_stop(void)
{
    /* Disable SysTick IRQ and SysTick Timer */
    SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
}

void systick_inc_tick(void)
{
    ++Systick_Tick;
}

uint32_t systick_get_tick(void)
{
    return Systick_Tick;
}

void systick_delay_ms(const uint32_t ms)
{
    uint32_t tickstart = 0;
    for (tickstart = Systick_Tick; Systick_Tick - tickstart < ms;)
        ;
}

void systick_delay_us(const uint32_t us)
{
    /* 不超过 ms */
    uint32_t reload = SysTick->LOAD;
    uint32_t ticks = 0;
    uint32_t told = 0, tnow = 0, tcnt = 0;
    /* 获得延时经过的 tick 数 */
    ticks = us * reload / 1000;
    /* 获得当前时间 */
    told = SysTick->VAL;
    for (;;)
    {
        /* 循环获得当前时间, 直到达到指定的时间后退出循环 */
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            tcnt += ((tnow < told) ? (told - tnow) : (reload - tnow + told));
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}
void systick_delay_Ms(const uint32_t ms)
{
	uint32_t i;
	for(i=0;i<ms;i++)
	{
		systick_delay_us(1000);
	}

}


void SysTick_Handler(void)
{	
	systick_inc_tick();
}







