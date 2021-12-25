#ifndef _USER_DEV_SPI_H_
#define _USER_DEV_SPI_H_
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>
#define LCD_HOST    VSPI_HOST
#define DMA_CHAN    2

#define PIN_NUM_MISO -1
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  18
#define PIN_NUM_CS -1

void lcd_cmd(const uint8_t cmd);
void VSPI_data16(const uint16_t dat);
void vspi_init(void);
void VSPI_data_x(uint16_t *dat,uint32_t len);

#endif
