#include "user_led.h"
#include "driver/ledc.h"


#define LEDC_HS_TIMER          LEDC_TIMER_0
#define LEDC_HS_MODE           LEDC_HIGH_SPEED_MODE
#define LEDC_HS_CH0_GPIO       (22)
#define LEDC_HS_CH0_CHANNEL    LEDC_CHANNEL_0


ledc_channel_config_t ledc_RED_cfg = {
    .channel    = LEDC_CHANNEL_0,
    .duty       = 0,
    .gpio_num   = LEDC_HS_CH0_GPIO,
    .speed_mode = LEDC_HS_MODE,
    .hpoint     = 0,
    .timer_sel  = LEDC_HS_TIMER
}; 

void LED_tim_init(void)
{
    const ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_8_BIT, // resolution of PWM duty
        .freq_hz = 5000,                      // frequency of PWM signal
        .speed_mode = LEDC_HS_MODE,           // timer mode
        .timer_num = LEDC_HS_TIMER,            // timer index
        .clk_cfg = LEDC_AUTO_CLK,              // Auto select the source clock
    };
    ledc_timer_config(&ledc_timer);
}



void user_led_set_duty(uint8_t duty)
{
    ledc_set_duty(ledc_RED_cfg.speed_mode, ledc_RED_cfg.channel, 255-duty);
    ledc_update_duty(ledc_RED_cfg.speed_mode, ledc_RED_cfg.channel);
}

void led_init(void)
{
    LED_tim_init();

    ledc_channel_config(&ledc_RED_cfg);

    ledc_fade_func_install(0);  


}




void led_task(void *arg)
{
    while (1)
    {
        user_led_set_duty(50);
        vTaskDelay(500/portTICK_PERIOD_MS);
        user_led_set_duty(100);
        vTaskDelay(500/portTICK_PERIOD_MS);
        user_led_set_duty(200);
        vTaskDelay(500/portTICK_PERIOD_MS);

    }
    
}



