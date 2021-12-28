
#ifndef __WIFI_CONNECT_H__
#define __WIFI_CONNECT_H__
#include "freertos/event_groups.h"
void wifi_init_sta();
/* FreeRTOS event group to signal when we are connected*/
EventGroupHandle_t s_wifi_event_group;
#endif