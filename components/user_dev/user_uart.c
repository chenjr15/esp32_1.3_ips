#include "user_uaer.h"


QueueHandle_t uart1_queue;


void uart_task(void *arg)
{
    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .stop_bits = UART_STOP_BITS_1,
        .parity    = UART_PARITY_DISABLE,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk= UART_SCLK_REF_TICK,
    };

    int intr_alloc_flags = 0;

    uart_event_t event;

    #if CONFIG_UART_ISR_IN_IRAM
    intr_alloc_flags = ESP_INTR_FLAG_IRAM;
    #endif
    uart_param_config(UART_NUM_1,&uart_config);
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1, 1024, 0, 20, &uart1_queue, intr_alloc_flags));
    uart_set_pin(UART_NUM_1,17,16,-1,-1);

    uint8_t *data = (uint8_t *) malloc(1024*8);
    while (true)
    {
        int ret = xQueueReceive(uart1_queue,&event,(portTickType)portMAX_DELAY);
        if(ret!=0){
            switch (event.type)
            {
            case UART_DATA:{
                uart_read_bytes(UART_NUM_1, data, event.size, 10000/portTICK_PERIOD_MS);
                uart_write_bytes(UART_NUM_1,data,event.size);

            }break;
            
            default:
                break;
            }
        }

 
       

        /* code */
    }
    

}








