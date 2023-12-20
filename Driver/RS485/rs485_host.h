#ifndef __RS485_HOST_H__
#define __RS485_HOST_H__

#include <stdint.h>
#include "rs485.h"
typedef enum
{
    RS485_HOST_INIT = 0,
    RS485_HOST_START_RECV,
    RS485_HOST_RECVING,
    RS485_HOST_RECV_OK,
	RS485_HOST_RECV_TIMEOUT,
}rs485_state_e;

typedef struct
{
    uint8_t (*send)(uint8_t *buff, uint16_t len);
    uint8_t (*recv)(uint8_t *buff, uint16_t len);
    uint8_t (*process)(rs485_state_e state,uint8_t *buff, uint16_t len);
    uint16_t (*get_recv_size)(void);
    uint8_t *cache;
    uint16_t cache_len;
    uint16_t recv_len;
    uint16_t ack_timeout;
    uint16_t frame_timeout;
    uint16_t ack_tick;
    uint16_t frame_tick;
    rs485_state_e state;
} RS485_Host_t;

void rs485_host_process(uint16_t delay);
uint8_t rs485_host_send(RS485_Host_t *host, uint8_t *buff, uint16_t len);
uint8_t rs485_host_add(RS485_Host_t *host);
uint8_t rs485_host_init(void);

#endif
