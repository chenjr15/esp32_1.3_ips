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

static const char* TAG = "main";
 
void app_main(void)
{
   LCD_IO_Init();
   uint32_t i = 0;
   while (true)
   {
      LCD_Clear(i++);

      vTaskDelay(((100) / portTICK_PERIOD_MS));
   }
   
}
