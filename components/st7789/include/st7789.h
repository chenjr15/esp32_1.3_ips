#ifndef _USER_LCD_H_
#define _USER_LCD_H_

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stdio.h"
#include <string.h>

// LCD SPI定义
#define LCD_HOST VSPI_HOST
#define DMA_CHAN 2

#define PIN_NUM_MISO -1
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  18
#define PIN_NUM_CS   -1

// LCD SPI 通信频率
#define LCD_SPI_FREQ (SPI_MASTER_FREQ_20M * 3)

// LCD 宽高定义
#define LCD_W 240
#define LCD_H 240
// LCD 控制引脚
#define LCD_RES GPIO_NUM_33
#define LCD_DC  GPIO_NUM_27
#define LCD_BLK GPIO_NUM_32

#define BLK_ON()  gpio_set_level(LCD_BLK, 1);
#define BLK_OFF() gpio_set_level(LCD_BLK, 0);

#define LCD_SCL_SET() gpio_set_level(LCD_SCL, 1);
#define LCD_SCL_CLR() gpio_set_level(LCD_SCL, 0);
#define LCD_SDA_SET() gpio_set_level(LCD_SDA, 1);
#define LCD_SDA_CLR() gpio_set_level(LCD_SDA, 0);
#define LCD_CS_SET()  gpio_set_level(LCD_CS, 1);
#define LCD_CS_CLR()  gpio_set_level(LCD_CS, 0);
#define LCD_RES_SET() gpio_set_level(LCD_RES, 1);
#define LCD_RES_CLR() gpio_set_level(LCD_RES, 0);

#define LCD_DC_SET() gpio_set_level(LCD_DC, 1);
#define LCD_DC_CLR() gpio_set_level(LCD_DC, 0);

void LCD_IO_deinit(void);
void LCD_IO_Init(void);
void LCD_Clear(uint16_t Color);
void LCD_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
              uint16_t *color);

void lcd_cmd(const uint8_t cmd);
void vspi_data16(const uint16_t dat);
void vspi_init();
void vspi_data_x(uint16_t *dat, uint32_t len);

#endif
