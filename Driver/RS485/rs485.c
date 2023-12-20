#include "rs485.h"
#include "rs485_host.h"
#include "./CRC//modbus_crc16.h"
#define RS485_HOST_DEVICE1_CACHE_LEN 128
#define FRAME_TIMEOUT 5
#define ACK_TIMEOUT 90


CircleBuffer_t CirBuf;
volatile bool msg_rcvd = false;
uint16_t uart2_sendCount;
RS485_Host_t rs485_host_device1 = {0};
uint8_t rs485_host_dev1_cache[RS485_HOST_DEVICE1_CACHE_LEN] = {0};


typedef struct{
	uint8_t code;
	uint8_t (*process)(uint8_t *buff,uint16_t len);
}modbus_process_t;

void UART2_Handler(void)
{
	uint32_t chr;
    
	/**读取数据到CirBuf**/
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

	
}


void uart2_init(void)
{
	UART_InitStructure UART_initStruct;
	PORT_Init(RS485_RX_PORT, RS485_RX_PIN, PORTB_PIN13_UART2_RX, 1);	//RS485_RX配置为UART2输入引脚
	PORT_Init(RS485_TX_PORT, RS485_TX_PIN, PORTB_PIN11_UART2_TX, 0);	//RS485_TX配置为UART2输出引脚

 	UART_initStruct.Baudrate = 115200;
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

/****************************************************************************************************************************************** 
* 函数名称:	uart2_sendByte()
* 功能说明:	发送一个字节的数据
* 输    入: uint8_t data			要发送的字节	
* 输    出: 
* 注意事项: 无
******************************************************************************************************************************************/

void uart2_sendByte(uint8_t data)
{
	UART_WriteByte(UART2, data);
	 while(UART_IsTXBusy(UART2));
}
/****************************************************************************************************************************************** 
* 函数名称:	uart2_sendBytes()
* 功能说明:	发送指定字节的数据
* 输    入: uint8_t data			要发送的数据
		   uint16_t Size		要发送的数据长度
* 输    出: 
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t uart2_sendBytes(uint8_t *pData, uint16_t Size)
{
	uart2_sendCount = 0;
	while(uart2_sendCount < Size)
	{
		uart2_sendByte(pData[uart2_sendCount++]);
	}
	return 0;
}
/****************************************************************************************************************************************** 
* 函数名称:	uart2_readBytes()
* 功能说明:	接收指定字节的数据
* 输    入: uint8_t data			要接收的数据
		   uint16_t Size		要接收的数据长度
* 输    出: 
* 注意事项: 无
******************************************************************************************************************************************/
void uart2_readBytes(uint8_t *pData, uint16_t Size)
{ 
	if(Size>CirBuf_Count(&CirBuf))
	{
		printf("Read length longger than buff data length!");
		return;
	}
	uint32_t i;
	if(CirBuf_Count(&CirBuf) == Size)
	{
		CirBuf_Read(&CirBuf,pData,Size);
	}
	else
	{
		printf("Data length mismatch!");
	}
	CirBuf_Clear(&CirBuf);
}

uint8_t modbus_8x_process(uint8_t *buff,uint16_t len){
	printf("device:0x%02X,err code:0x%02X\r\n",buff[0],buff[1]);
	return 0;
}
uint8_t modbus_unknow_code_process(uint8_t *buff,uint16_t len){
	printf("device:0x%02X,code:0x%02X\r\n",buff[0],buff[1]);
	return 0;
}

uint8_t modbus_03_process(uint8_t *buff,uint16_t len){
	printf("device:0x%02X,\r\n",buff[0]);
  	int data_size = buff[2];
	if(data_size != len-1-1-1){
		printf("data_len:%d,recv_len:%d\r\n",data_size,len);
		return 1;
	}
	
	for(int i = 0;i< data_size;){
		printf("reg(%d):0x%04X\r\n",i/2,buff[i+3]<<8|buff[i+4]);
		i += 2;
	}
	return 0;
}
uint8_t modbus_06_process(uint8_t *buff,uint16_t len){
	printf("device:0x%02X,\r\n",buff[0]);
	for(int i = 0;i< len;i++){
		printf("0x%02X\r\n",buff[i]);
	}
	return 0;
}
modbus_process_t my_process[] = {
	{0x03,modbus_03_process},
	{0x06,modbus_06_process},
};




/****************************************************************************************************************************************** 
* 函数名称:	modbus_protocol_decode()
* 功能说明:	解码modbus报文
* 输    入: 	rs485_state_e state 主机的接收状态
			uint8_t *buff		准备编码的数据
			uint16_t len		数据的长度
* 输    出: 
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t modbus_protocol_decode(uint8_t *buff,uint16_t len){
	//err code
	if(len < (1+1+1+2) || len > 256){
			printf("recv len err:%d",len);
	}

	uint16_t crc = modbus_crc16(buff,len-2);
	if(crc != ((buff[len-1]<<8) | buff[len-2])){
		printf("crc err: 0x%04X",crc);
	}
	len = len- 2;
	//process err code
	if(buff[1]&0x80){
		modbus_8x_process(&buff[0],len);
		return 0;
	}
	
	int i = 0;
	for(i=0;i<sizeof(my_process)/sizeof(modbus_process_t);i++){	  
			if((my_process[i].code) == buff[1]){
				my_process[i].process(&buff[0],len);
				return 0;
			}
	}
	
	//process unknow code
	modbus_unknow_code_process(&buff[0],len);
	return 0;
}

/****************************************************************************************************************************************** 
* 函数名称:	host_device1_process()
* 功能说明:	
* 输    入: 	rs485_state_e state 主机的接收状态
			uint8_t *buff		准备编码的数据
			uint16_t len		数据的长度
* 输    出: 
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t host_device1_process(rs485_state_e state,uint8_t *buff, uint16_t len)
{
	if(state == RS485_HOST_RECV_TIMEOUT){
		printf("recv timeout");
	}else if(state == RS485_HOST_RECV_OK){
		modbus_protocol_decode(buff,len);
	}
  return 0;
}
uint8_t modbus_protocol_encode(uint8_t *buff,uint16_t len){
	uint16_t crc = modbus_crc16(buff,len);
	buff[len] = crc & 0xff;
	buff[len+1] = crc >> 8;
	return 0;
}
uint8_t modbus_06_set_req(uint8_t slave_id,uint16_t reg_addr,uint16_t reg_value){
	uint8_t buff[16] = {0};
	buff[0] = slave_id;
	buff[1] = 0x06;
	buff[2] = reg_addr >> 8;
	buff[3] = reg_addr & 0xff;
	buff[4] = reg_value >> 8;
	buff[5] = reg_value & 0xff;
	modbus_protocol_encode(buff,6);
	return rs485_host_send(&rs485_host_device1, buff,8);
}
/****************************************************************************************************************************************** 
* 函数名称:	host_device1_get_recv_size()
* 功能说明:	查询串口接收到的数据大小
* 输    入: 	
* 输    出: 
* 注意事项: 无
******************************************************************************************************************************************/

uint16_t host_device1_get_recv_size(void)
{
  return CirBuf_Count(&CirBuf);
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

/****************************************************************************************************************************************** 
* 函数名称:	rs485_host_devices_init()
* 功能说明:	初始化一个485主机
* 输    入: 	
* 输    出: 
* 注意事项: 无
******************************************************************************************************************************************/
void rs485_host_devices_init(void)
{
  rs485_host_device1.send = uart2_sendBytes;
  rs485_host_device1.recv = uart2_sendBytes;
  rs485_host_device1.process = host_device1_process;
  rs485_host_device1.cache = rs485_host_dev1_cache;
  rs485_host_device1.get_recv_size = host_device1_get_recv_size;
  rs485_host_device1.cache_len = RS485_HOST_DEVICE1_CACHE_LEN;
  rs485_host_device1.ack_timeout = ACK_TIMEOUT;
  rs485_host_device1.frame_timeout = FRAME_TIMEOUT;
  rs485_host_device1.frame_tick = 0;
  rs485_host_device1.ack_tick = 0;
  rs485_host_device1.state = RS485_HOST_INIT;
}

