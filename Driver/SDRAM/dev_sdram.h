/**
 *******************************************************************************************************************************************
 * @file        dev_sdram.h
 * @brief       оƬ���� SDRAM
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
 * @brief   ��ʼ�� SDRAM Control ��оƬ���õ� SDRAM ӳ���� MCU ���ߵ�ַ��
 * @note    �������� SDRAM �ϵ繤���ڼ�ֻ�ܱ�����һ��, �����ظ���ʼ��
 */
void sdram_init(void);

/**
 * @brief   ����оƬ���õ� SDRAM �����˿�
 */
void sdram_port_init(void);

#endif //__DEV_SDRAM_H__
