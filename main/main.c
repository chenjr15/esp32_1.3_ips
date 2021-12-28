#include <stdio.h>
#include <string.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_spi_flash.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#include "sdkconfig.h"

#include "gui.h"
#include "lvgl.h"
#include "st7789.h"

static const char *TAG = "main";

void lvgl_task(void *arg) {
  while (true) {
    vTaskDelay(((10) / portTICK_PERIOD_MS));
    lv_task_handler();
  }
}

void app_main(void) {
  gui_init();
  while (true) {
    vTaskDelay(((10) / portTICK_PERIOD_MS));
    lv_task_handler();
  }
}
