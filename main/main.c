#include <stdio.h>
#include <string.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_spi_flash.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#include "sdkconfig.h"

#include "gui.h"
#include "lvgl.h"
#include "st7789.h"
#include "wifi_connect.h"

static const char *TAG = "main";

void lvgl_task(void *arg) {
  while (true) {
    vTaskDelay(((10) / portTICK_PERIOD_MS));
    lv_task_handler();
  }
}

void app_main(void) {
  wifi_init_sta();
  gui_init();
  char wifi_status_buf[64] = {0};
  xTaskCreate(lvgl_task, "lvgl_task", 4096, NULL, 1, NULL);

  setWifiStatus(wifi_status_buf);

  while (true) {
    vTaskDelay(((10) / portTICK_PERIOD_MS));
    // lv_task_handler();
    // 阻塞等待WIFI事件
    /* Waiting until either the connection is established (WIFI_CONNECTED_BIT)
     * or connection failed for the maximum number of re-tries (WIFI_FAIL_BIT).
     * The bits are set by event_handler() (see above) */
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                           WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                           pdTRUE, pdFALSE, portMAX_DELAY);

    /* xEventGroupWaitBits() returns the bits before the call returned, hence we
     * can test which event actually happened. */
    if (bits & WIFI_CONNECTED_BIT) {
      ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
               EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
      snprintf(wifi_status_buf, 64, "%s:\n" IPSTR, EXAMPLE_ESP_WIFI_SSID,
               IP2STR(&curIPInfo.ip));
    } else if (bits & WIFI_FAIL_BIT) {
      ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
               EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
      snprintf(wifi_status_buf, 64, "Failed: %s", EXAMPLE_ESP_WIFI_SSID);

    } else {
      ESP_LOGE(TAG, "UNEXPECTED EVENT");
      snprintf(wifi_status_buf, 64, "UNEXPECTED EVENT");
    }
    setWifiStatus(wifi_status_buf);
  }
  // 取消监听
  // /* The event will not be processed after unregister */
  // ESP_ERROR_CHECK(esp_event_handler_instance_unregister(
  //     IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip));
  // ESP_ERROR_CHECK(esp_event_handler_instance_unregister(
  //     WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id));
  // vEventGroupDelete(s_wifi_event_group);
}
