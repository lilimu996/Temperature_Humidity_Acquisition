#include "rs485.h"



CircleBuffer_t CirBuf;
volatile bool msg_rcvd = false;


void UART2_Handler(void)
{
	uint32_t chr;

	/**中断状态查询**/
	if(UART_INTStat(UART2, UART_IT_RX_THR | UART_IT_RX_TOUT))
	{
		while(UART_IsRXFIFOEmpty(UART2) == 0)
		{
			if(UART_ReadByte(UART2, &chr) == 0)
			{
				CirBuf_Write(&CirBuf, (uint8_t *)&chr, 1);
			}
		}
		
		if(UART_INTStat(UART2, UART_IT_RX_TOUT))
		{
			UART_INTClr(UART2, UART_IT_RX_TOUT);
			
			msg_rcvd = true;
		}
	}
	
	if(UART_INTStat(UART2, UART_IT_TX_THR))
	{
		while(!UART_IsTXFIFOFull(UART2))
		{
			if(!CirBuf_Empty(&CirBuf))
			{
				CirBuf_Read(&CirBuf, (uint8_t *)&chr, 1);
				
				UART_WriteByte(UART2, chr);
			}
			else
			{
				UART_INTDis(UART2, UART_IT_TX_THR);
				
				break;
			}
		}
	}
}



void uart2_init(void)
{
	UART_InitStructure UART_initStruct;
	PORT_Init(RS485_RX_PORT, RS485_RX_PIN, PORTB_PIN13_UART2_RX, 1);	//RS485_RX配置为UART2输入引脚
	PORT_Init(RS485_TX_PORT, RS485_TX_PIN, PORTB_PIN11_UART2_TX, 0);	//RS485_TX配置为UART2输出引脚

 	UART_initStruct.Baudrate = 57600;
	UART_initStruct.DataBits = UART_DATA_8BIT;
	UART_initStruct.Parity = UART_PARITY_NONE;
	UART_initStruct.StopBits = UART_STOP_1BIT;
	UART_initStruct.RXThreshold = 3;
	UART_initStruct.RXThresholdIEn = 1;
	UART_initStruct.TXThreshold = 3;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutTime = 10;		//10个字符时间内未接收到新的数据则触发超时中断
	UART_initStruct.TimeoutIEn = 1;
 	UART_Init(UART2, &UART_initStruct);
	UART_Open(UART2);
}

/**查询串口接收状态**/
bool get_uart2_msgStatus(void)
{
	return msg_rcvd;
}
void clear_uart2_msgStatus(void)
{
	msg_rcvd=false;
}


