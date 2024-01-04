/**
 *******************************************************************************************************************************************
 * @file        dev_sdram.h
 * @brief       芯片内置 SDRAM
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
#ifndef __DEV_SDRAM_H__
#define __DEV_SDRAM_H__

#include "SWM341.h"

/**
 * @brief   初始化 SDRAM Control 将芯片内置的 SDRAM 映射至 MCU 总线地址上
 * @note    本函数在 SDRAM 上电工作期间只能被调用一次, 不可重复初始化
 */
void sdram_init(void);

/**
 * @brief   配置芯片内置的 SDRAM 驱动端口
 */
void sdram_port_init(void);

#endif //__DEV_SDRAM_H__
