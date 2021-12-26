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
#include "lv_port_indev.h"
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
   assert(err == ESP_OK);
}



void lvgl_task(void *arg)
{
   while (true)
   {
      vTaskDelay(((10)/ portTICK_PERIOD_MS));
      lv_task_handler();
   }
   
}

static void btn_event_cb(lv_event_t *e)
{
   lv_event_code_t code = lv_event_get_code(e);
   lv_obj_t *btn = lv_event_get_target(e);
   if (code == LV_EVENT_CLICKED)
   {
      static uint8_t cnt = 0;
      cnt++;

      /*Get the first child of the button which is the label and change its text*/
      lv_obj_t *label = lv_obj_get_child(btn, 0);
      lv_label_set_text_fmt(label, "%3d", cnt);
   }
}

lv_obj_t *sw;
void GUI_APP_init(void)
{
   //lvgl内核初始化
   lv_init();
   //lvgl显示接口初始化
   lv_port_disp_init();
   //lvgl 输入初始化
   lv_port_indev_init();
   // 创建定时器
   _lv_timer_create();
   // lv_obj_t * img_temp = lv_label_create(lv_scr_act());
   // lv_obj_align(img_temp,LV_ALIGN_CENTER,0,0);

   // 设置FLOW布局
   lv_obj_set_flex_flow(lv_scr_act(), LV_FLEX_FLOW_COLUMN);
   lv_obj_set_flex_align(lv_scr_act(), LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

   lv_obj_t *label_num = lv_label_create(lv_scr_act()); /*Add a label to the button*/
   // lv_obj_add_style(label_num, &style_num_label, 0);
   // 用Style的模式没用，要直接设置obj的字体
   lv_obj_set_style_text_font(label_num, &lv_font_montserrat_48, 0);
   lv_label_set_text(label_num, "19:49");
   /*Set the labels text*/
   // lv_obj_set_size(label_num, 50, 30);
   lv_obj_center(label_num);

   lv_obj_t *btn = lv_btn_create(lv_scr_act()); /*Add a button the current screen*/
   //  lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
   //  lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
   lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL); /*Assign a callback to the button*/

   lv_obj_t *label = lv_label_create(btn); /*Add a label to the button*/
   lv_label_set_text(label, "  0");        /*Set the labels text*/
   lv_obj_set_size(btn, 50, 30);
   lv_obj_center(label);
   // 创建开关

   sw = lv_switch_create(lv_scr_act());
   lv_obj_add_state(sw, LV_STATE_CHECKED);
   // 加入控制组
   lv_group_add_obj(input_group, btn);
   lv_group_add_obj(input_group, sw);
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
