/**
 *******************************************************************************************************************************************
 * @file        dev_sdram.c
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
#include "dev_sdram.h"
#define SIZE_8MB                (0x00800000)
#define SDRAMM_SIZE SIZE_8MB

/**
 * @brief   初始化 SDRAM Control 将芯片内置的 SDRAM 映射至 MCU 总线地址上
 * @note    本函数在 SDRAM 上电工作期间只能被调用一次, 不可重复初始化
 */
void sdram_init(void)
{
    /* 配置内部叠封 <未引出> 的端口 */
    sdram_port_init();

    SDRAM_InitStructure SDRAM_InitStruct;

#if (SDRAMM_SIZE == SIZE_2MB)
    SDRAM_InitStruct.Size = SDRAM_SIZE_2MB;
#elif (SDRAMM_SIZE == SIZE_8MB)
    SDRAM_InitStruct.Size = SDRAM_SIZE_8MB;
#elif (SDRAMM_SIZE == SIZE_16MB)
    SDRAM_InitStruct.Size = SDRAM_SIZE_16MB;
#elif (SDRAMM_SIZE == SIZE_32MB)
    SDRAM_InitStruct.Size = SDRAM_SIZE_32MB;
#else /* Default */
    SDRAM_InitStruct.Size = SDRAM_SIZE_8MB;
#endif
    /* 一分频: 即与 MCU 主频相同 */
    SDRAM_InitStruct.ClkDiv = SDRAM_CLKDIV_1;
    
    SDRAM_InitStruct.CASLatency = SDRAM_CASLATENCY_3;
    SDRAM_InitStruct.TimeTRP  = SDRAM_TRP_2;
    SDRAM_InitStruct.TimeTRCD = SDRAM_TRCD_2;
    SDRAM_InitStruct.TimeTRC  = SDRAM_TRC_9;
    SDRAM_Init(&SDRAM_InitStruct);
}

/**
 * @brief   配置芯片内置的 SDRAM 驱动端口
 */
void sdram_port_init(void)
{
    /* 配置内部叠封 <未引出> 的端口 */
    PORT_Init(PORTM, PIN13, PORTM_PIN13_SDR_CLK, 0);
    PORT_Init(PORTM, PIN14, PORTM_PIN14_SDR_CKE, 0);
    PORT_Init(PORTB, PIN7,  PORTB_PIN7_SDR_WE,   0);
    PORT_Init(PORTB, PIN8,  PORTB_PIN8_SDR_CAS,  0);
    PORT_Init(PORTB, PIN9,  PORTB_PIN9_SDR_RAS,  0);
    PORT_Init(PORTB, PIN10, PORTB_PIN10_SDR_CS,  0);
    PORT_Init(PORTE, PIN15, PORTE_PIN15_SDR_BA0, 0);
    PORT_Init(PORTE, PIN14, PORTE_PIN14_SDR_BA1, 0);
    PORT_Init(PORTN, PIN14, PORTN_PIN14_SDR_A0,  0);
    PORT_Init(PORTN, PIN13, PORTN_PIN13_SDR_A1,  0);
    PORT_Init(PORTN, PIN12, PORTN_PIN12_SDR_A2,  0);
    PORT_Init(PORTN, PIN11, PORTN_PIN11_SDR_A3,  0);
    PORT_Init(PORTN, PIN10, PORTN_PIN10_SDR_A4,  0);
    PORT_Init(PORTN, PIN9,  PORTN_PIN9_SDR_A5,   0);
    PORT_Init(PORTN, PIN8,  PORTN_PIN8_SDR_A6,   0);
    PORT_Init(PORTN, PIN7,  PORTN_PIN7_SDR_A7,   0);
    PORT_Init(PORTN, PIN6,  PORTN_PIN6_SDR_A8,   0);
    PORT_Init(PORTN, PIN3,  PORTN_PIN3_SDR_A9,   0);
    PORT_Init(PORTN, PIN15, PORTN_PIN15_SDR_A10, 0);
    PORT_Init(PORTN, PIN2,  PORTN_PIN2_SDR_A11,  0);
    PORT_Init(PORTM, PIN15, PORTM_PIN15_SDR_A12, 0);
    PORT_Init(PORTE, PIN7,  PORTE_PIN7_SDR_D0,   1);
    PORT_Init(PORTE, PIN6,  PORTE_PIN6_SDR_D1,   1);
    PORT_Init(PORTE, PIN5,  PORTE_PIN5_SDR_D2,   1);
    PORT_Init(PORTE, PIN4,  PORTE_PIN4_SDR_D3,   1);
    PORT_Init(PORTE, PIN3,  PORTE_PIN3_SDR_D4,   1);
    PORT_Init(PORTE, PIN2,  PORTE_PIN2_SDR_D5,   1);
    PORT_Init(PORTE, PIN1,  PORTE_PIN1_SDR_D6,   1);
    PORT_Init(PORTE, PIN0,  PORTE_PIN0_SDR_D7,   1);
    PORT_Init(PORTE, PIN8,  PORTE_PIN8_SDR_D8,   1);
    PORT_Init(PORTE, PIN9,  PORTE_PIN9_SDR_D9,   1);
    PORT_Init(PORTE, PIN10, PORTE_PIN10_SDR_D10, 1);
    PORT_Init(PORTE, PIN11, PORTE_PIN11_SDR_D11, 1);
    PORT_Init(PORTE, PIN12, PORTE_PIN12_SDR_D12, 1);
    PORT_Init(PORTE, PIN13, PORTE_PIN13_SDR_D13, 1);
    PORT_Init(PORTC, PIN14, PORTC_PIN14_SDR_D14, 1);
    PORT_Init(PORTC, PIN15, PORTC_PIN15_SDR_D15, 1);
    PORT_Init(PORTB, PIN6,  PORTB_PIN6_SDR_LDQM, 0);
    PORT_Init(PORTM, PIN12, PORTM_PIN12_SDR_UDQM,0);
}
