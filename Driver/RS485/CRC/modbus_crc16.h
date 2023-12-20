#ifndef __MODBUS_CRC16_H__
#define __MODBUS_CRC16_H__

#include "stdint.h"

uint16_t modbus_crc16(uint8_t *puchMsg, uint16_t usDataLen);

#endif
