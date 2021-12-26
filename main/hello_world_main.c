/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
/*C:\Windows\system32\cmd.exe /k ""C:\Users\60394\.espressif\idf_cmd_init.bat"*/

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include <string.h>
#include "esp_log.h"
#include "freertos/queue.h"
#include "user_dev_inc.h"
#include "User_mid_LCD.h"
#include "driver/gpio.h"
#include "lvgl.h"
#include "lv_port_disp.h"



static const char* TAG = "lv_gui_app";


static esp_timer_handle_t lvgl_timer_handle = NULL;


static IRAM_ATTR void lv_timer_cb(void *arg)
{
   lv_tick_inc(1);
}

static esp_timer_create_args_t lvgl_timer = {
    .callback = &lv_timer_cb,
    .arg = NULL,
    .name ="lvgl_timer",
    .dispatch_method = ESP_TIMER_TASK
};

void _lv_timer_create(void)
{
   esp_err_t err = esp_timer_create(&lvgl_timer, &lvgl_timer_handle);
   err = esp_timer_start_periodic(lvgl_timer_handle, 1000 );//1毫秒回调
   if(err!=ESP_OK){
      ESP_LOGE(TAG,"lvgl定时器创建失败！\r\n");
   }else{
      ESP_LOGI(TAG,"lvgl定时器创建成功\r\n");
      
   }

}



void lvgl_task(void *arg)
{
   while (true)
   {
      vTaskDelay(((10)/ portTICK_PERIOD_MS));
      lv_task_handler();
   }
   
}

#if 0

LV_IMG_DECLARE(hutao0);
LV_IMG_DECLARE(hutao1);
LV_IMG_DECLARE(hutao2);
LV_IMG_DECLARE(hutao3);
LV_IMG_DECLARE(hutao4);
LV_IMG_DECLARE(hutao5);
LV_IMG_DECLARE(hutao6);
LV_IMG_DECLARE(hutao7);
LV_IMG_DECLARE(hutao8);
LV_IMG_DECLARE(hutao9);
LV_IMG_DECLARE(hutao10);

IRAM_ATTR void IMG_task(void *arg)
{
   lv_obj_t * img_temp = lv_img_create(lv_scr_act());
   lv_obj_align(img_temp,LV_ALIGN_CENTER,0,0);
   while (true)
   {
      lv_img_set_src(img_temp,&hutao0);
      vTaskDelay(((100)/ portTICK_PERIOD_MS)); 
      lv_img_set_src(img_temp,&hutao1);
      vTaskDelay(((100)/ portTICK_PERIOD_MS)); 
      lv_img_set_src(img_temp,&hutao2);
      vTaskDelay(((100)/ portTICK_PERIOD_MS)); 
      lv_img_set_src(img_temp,&hutao3);
      vTaskDelay(((100)/ portTICK_PERIOD_MS)); 
      lv_img_set_src(img_temp,&hutao4);
      vTaskDelay(((100)/ portTICK_PERIOD_MS)); 
      lv_img_set_src(img_temp,&hutao5);
      vTaskDelay(((100)/ portTICK_PERIOD_MS)); 
      lv_img_set_src(img_temp,&hutao6);
      vTaskDelay(((100)/ portTICK_PERIOD_MS)); 
      lv_img_set_src(img_temp,&hutao7);
      vTaskDelay(((100)/ portTICK_PERIOD_MS)); 
      lv_img_set_src(img_temp,&hutao8);
      vTaskDelay(((100)/ portTICK_PERIOD_MS)); 
      lv_img_set_src(img_temp,&hutao9);
      vTaskDelay(((100)/ portTICK_PERIOD_MS)); 
      lv_img_set_src(img_temp,&hutao10);
      vTaskDelay(((100)/ portTICK_PERIOD_MS)); 

      lv_qrcode_create(lv_scr_act(),100,lv_color_hex3(1),lv_color_hex3(1));
   } 
}

#endif 

void GUI_APP_init(void)
{
    lv_init();						//lvgl内核初始化
    lv_port_disp_init();			//lvgl显示接口初始化
    _lv_timer_create();
   // lv_obj_t * img_temp = lv_label_create(lv_scr_act());
   // lv_obj_align(img_temp,LV_ALIGN_CENTER,0,0);

    lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
   //  lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Button");                     /*Set the labels text*/
    lv_obj_center(label);

//     xTaskCreatePinnedToCore(lvgl_task,"lvgl_task",4096,NULL,2,NULL,APP_CPU_NUM);
// //   xTaskCreatePinnedToCore(GUI_task,"GUI_task",4096*2,NULL,3,NULL,APP_CPU_NUM);
//    xTaskCreatePinnedToCore(IMG_task,"IMG_task",4096*2,NULL,3,NULL,APP_CPU_NUM);
//   xTaskCreatePinnedToCore(qc_task,"qc_task",4096*3,NULL,3,NULL,APP_CPU_NUM);

}

 
void app_main(void)
{
   GUI_APP_init();
   while (true)
   {
      vTaskDelay(((10)/ portTICK_PERIOD_MS));
      lv_task_handler();
   }
}
