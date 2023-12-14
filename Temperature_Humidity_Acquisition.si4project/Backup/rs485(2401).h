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
















#endif

