
/**
 * @file lv_port_indev_templ.h
 *
 */

 /*Copy this file as "lv_port_indev.h" and set this value to "1" to enable content*/
#if 1

#ifndef LV_PORT_INDEV_TEMPL_H
#define LV_PORT_INDEV_TEMPL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"

    /*********************
 *      DEFINES
 *********************/
    // #define KEY_NUM 3U
    // #define GPIO_INPUT_IO_0 0
    // #define GPIO_INPUT_IO_1 4
    // #define GPIO_INPUT_IO_2 16
    // #define GPIO_INPUT_IO_2 17
    // #define GPIO_INPUT_PIN_SEL ((1ULL << GPIO_INPUT_IO_0) | (1ULL << GPIO_INPUT_IO_1) | (1ULL << GPIO_INPUT_IO_2))
    // #define ESP_INTR_FLAG_DEFAULT 0

#define KEY_NUM (sizeof(KEY_PIN) / sizeof(uint32_t))

#define KEY_DOWN 0U
    void lv_port_indev_init(void);
    /**********************
 *      TYPEDEFS
 **********************/

    /**********************
 * GLOBAL PROTOTYPES
 **********************/
    lv_group_t *input_group;

    /**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_PORT_INDEV_TEMPL_H*/

#endif /*Disable/Enable content*/
