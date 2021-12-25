#include "user_key.h"




void key_ev_create(void)
{
    KEY_Event_Handle = xEventGroupCreate();
    if(KEY_Event_Handle!=NULL)
    {
        printf("KEY_Event_Handle ok\r\n");

    }else{
        printf("KEY_Event_Handle err\r\n");

    }
}


void key_scan_task(void *arg)
{
    gpio_pad_select_gpio(GPIO_NUM_36);
    gpio_set_direction(GPIO_NUM_36,GPIO_MODE_INPUT);

    while (1)
    {
        if(gpio_get_level(GPIO_NUM_36)==0){
            xEventGroupSetBits(KEY_Event_Handle,KEY1_SHORT_PRESS_EVENT);/* 触发一个短按事件 */

        }else{
        }
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
    
}






