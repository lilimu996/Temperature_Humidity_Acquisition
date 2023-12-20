#ifndef __RS485_H
#define __RS485_H

#include "SWM341.h"
#include "CircleBuffer.h"

/*---------------UART2_RX_TX_PORT----------------*/
#define RS485_TX_PORT                  PORTB
#define RS485_TX_PIN				   PIN11

#define RS485_RX_PORT				   PORTB
#define RS485_RX_PIN				   PIN13



void uart2_init(void);
bool get_uart2_msgStatus(void);
void clear_uart2_msgStatus(void);
void uart2_sendByte(uint8_t data);
uint8_t uart2_sendBytes(uint8_t *pData, uint16_t Size);
uint8_t modbus_06_set_req(uint8_t slave_id,uint16_t reg_addr,uint16_t reg_value);














#endif

