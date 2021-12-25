#ifndef _USER_LCD_H_
#define _USER_LCD_H_

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "user_dev_inc.h"
#include "stdio.h"

#define LCD_W 240
#define LCD_H 240

#define LCD_RES GPIO_NUM_33
#define LCD_DC GPIO_NUM_27
#define LCD_BLK GPIO_NUM_32
#define BLK_ON()    gpio_set_level(LCD_BLK,1);
#define BLK_OFF()   gpio_set_level(LCD_BLK,0);

#define LCD_SCL_SET() gpio_set_level(LCD_SCL,1);
#define LCD_SCL_CLR() gpio_set_level(LCD_SCL,0);
#define LCD_SDA_SET() gpio_set_level(LCD_SDA,1);
#define LCD_SDA_CLR() gpio_set_level(LCD_SDA,0);
#define LCD_CS_SET() gpio_set_level(LCD_CS,1);
#define LCD_CS_CLR() gpio_set_level(LCD_CS,0);
#define LCD_RES_SET() gpio_set_level(LCD_RES,1);
#define LCD_RES_CLR() gpio_set_level(LCD_RES,0);

#define LCD_DC_SET() gpio_set_level(LCD_DC,1);
#define LCD_DC_CLR() gpio_set_level(LCD_DC,0);

void LCD_IO_deinit(void);
void LCD_IO_Init(void);
void LCD_Clear(uint16_t Color);
void LCD_Fill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t *color);	

#endif
