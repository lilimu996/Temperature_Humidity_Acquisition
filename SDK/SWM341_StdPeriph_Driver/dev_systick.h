/**
 *******************************************************************************************************************************************
 * @file        dev_systick.h
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
#ifndef __DEV_SYSTICK_H__
#define __DEV_SYSTICK_H__

#include "SWM341.h"

void systick_init(void);
void systick_stop(void);
void systick_inc_tick(void);
uint32_t systick_get_tick(void);
void systick_delay_ms(const uint32_t ms);
void systick_delay_us(const uint32_t us);
void systick_delay_Ms(const uint32_t ms);


#endif //__DEV_SYSTICK_H__
