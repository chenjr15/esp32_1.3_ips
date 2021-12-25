#include "User_dev_spi.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include <stdio.h>

static spi_device_handle_t spi;    //创建spi


static const spi_bus_config_t buscfg={   //spi定义
    .miso_io_num=PIN_NUM_MISO,
    .mosi_io_num=PIN_NUM_MOSI,
    .sclk_io_num=PIN_NUM_CLK,
    .quadwp_io_num=-1,
    .quadhd_io_num=-1,
    .max_transfer_sz=4094
};

static const spi_device_interface_config_t devcfg = {
    .clock_speed_hz = SPI_MASTER_FREQ_40M,
    .mode = 2,
    .spics_io_num = PIN_NUM_CS,
    .queue_size = 7
    };

void vspi_init(void)
{
    spi_bus_initialize(SPI3_HOST,&buscfg,DMA_CHAN);
    spi_bus_add_device(SPI3_HOST, &devcfg, &spi);
}

/*------------------------------------LCD传输8位指令---------------------------------------*/
void lcd_cmd(const uint8_t cmd)
{
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=8;                     //Command is 8 bits
    t.tx_buffer=&cmd;               //The data is the cmd itself
    t.user=(void*)0;                //D/C needs to be set to 0
    ret=spi_device_polling_transmit(spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.
}
/*------------------------------------LCD传输16位指令---------------------------------------*/

void VSPI_data16(const uint16_t dat)
{
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=16;                     //Command is 8 bits
    t.tx_buffer=&dat;               //The data is the cmd itself
    t.user=(void*)0;                //D/C needs to be set to 0
    ret=spi_device_polling_transmit(spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.
}

IRAM_ATTR void VSPI_data_x(uint16_t *dat,uint32_t len)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=len;                     //Command is 8 bits
    t.tx_buffer=dat;               //The data is the cmd itself
    t.user=(void*)0;                //D/C needs to be set to 0
    esp_err_t ret=spi_device_polling_transmit(spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.
}
