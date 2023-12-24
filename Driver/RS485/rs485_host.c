#include "rs485_host.h"
#include "stdio.h"
#include "rs485.h"
#define HOST_MAX_COUNT 2
uint8_t host_count = 0;
static RS485_Host_t *host_arr[HOST_MAX_COUNT];

uint8_t rs485_host_init(void)
{
	rs485_host_devices_init();
    return 0;
}

uint8_t rs485_host_add(RS485_Host_t *host)
{
    host_arr[host_count] = host;
    host_count++;
    return 0;
}

uint8_t rs485_host_send(RS485_Host_t *host, uint8_t *buff, uint16_t len)
{
    host->send(buff, len);
    host->state = RS485_HOST_START_RECV;
    host->recv_len = 0;
    host->frame_tick = 0;
    host->ack_tick = 0;
    host->recv(host->cache, host->cache_len);
	  printf("send\r\n");
    return 0;
}

void rs485_host_process(uint16_t delay)
{
    for (int i = 0; i < host_count; i++)
    {
        if (host_arr[i]->state == RS485_HOST_INIT)
        {
            continue;
        }

        if (host_arr[i]->state == RS485_HOST_START_RECV)
        {
            if (host_arr[i]->recv_len != host_arr[i]->get_recv_size())
            {
                host_arr[i]->state = RS485_HOST_RECVING;
                host_arr[i]->recv_len = host_arr[i]->get_recv_size();
            }
            host_arr[i]->ack_tick += delay;
            continue;
        }

        if (host_arr[i]->state == RS485_HOST_RECVING)
        {
            host_arr[i]->ack_tick += delay;
            host_arr[i]->frame_tick += delay;
            if (host_arr[i]->ack_tick >= host_arr[i]->ack_timeout)
            {
                host_arr[i]->state = RS485_HOST_RECV_TIMEOUT;
                host_arr[i]->process(host_arr[i]->state,host_arr[i]->cache, host_arr[i]->recv_len);
                host_arr[i]->state = RS485_HOST_INIT;
                continue;
            }

            if (host_arr[i]->frame_tick >= host_arr[i]->frame_timeout)
            {
                if (host_arr[i]->recv_len != host_arr[i]->get_recv_size())
                {
                    host_arr[i]->frame_tick = 0;
                    host_arr[i]->recv_len = host_arr[i]->get_recv_size();
                    continue;
                }
                host_arr[i]->state = RS485_HOST_RECV_OK;
                host_arr[i]->process(host_arr[i]->state,host_arr[i]->cache, host_arr[i]->recv_len);
                host_arr[i]->state = RS485_HOST_INIT;
            }
        }
    }
}
