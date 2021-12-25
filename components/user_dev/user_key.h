#ifndef _USER_KEY_H_
#define _USER_KEY_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

EventGroupHandle_t KEY_Event_Handle;

#define KEY1_SHORT_PRESS_EVENT (0X01<<1)

#endif


