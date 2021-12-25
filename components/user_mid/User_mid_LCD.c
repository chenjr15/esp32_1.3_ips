#include "User_mid_LCD.h"
#define DELAY(X) vTaskDelay(((X)/ portTICK_PERIOD_MS))



/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(uint8_t dat)
{
	LCD_DC_SET();//写数据
	lcd_cmd(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(uint16_t dat)
{
	LCD_DC_SET();//写数据
	//VSPI_data16(dat);
	
	lcd_cmd(dat>>8);
	lcd_cmd(dat);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(uint8_t dat)
{
	LCD_DC_CLR();//写命令
	lcd_cmd(dat);
}


/*x1=0 y1=0 x2=4 y2=4*/

/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	LCD_WR_REG(0x2a);//列地址设置
	LCD_WR_DATA(x1);
	LCD_WR_DATA(x2);
	LCD_WR_REG(0x2b);//行地址设置
	LCD_WR_DATA(y1+80);
	LCD_WR_DATA(y2+80);
	LCD_WR_REG(0x2c);//储存器写
}



/******************************************************************************
      函数说明：LCD清屏函数
      入口数据：无
      返回值：  无
******************************************************************************/
void LCD_Clear(uint16_t Color)
{
	LCD_Address_Set(0,0,LCD_W-1,LCD_H-1);
	LCD_DC_SET();//写数据
	uint16_t color_temp[240*2];
	memset(color_temp, Color, sizeof(color_temp));
    for(uint16_t i=0;i<LCD_W/2;i++){
	 	VSPI_data_x(color_temp,240*16*2);
	}
}


/*16bit rgb 565*/
IRAM_ATTR void LCD_Fill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t *color)	
{
	uint32_t size = (x2+1-x1)*(y2+1-y1)*2;
	LCD_Address_Set(x1,y1,x2,y2);
	LCD_DC_SET();//写数据
	uint32_t send_cnt 	= size/480;//需要整行刷新多少行
	uint32_t send_cnt2	= size%480;//整行刷不完还剩多少字节

	if(size==0)
	{
		printf("size=%u\r\n",size);
		return;
	}
	for(int i=0;i<send_cnt;i++){
		VSPI_data_x(&color[i*240],240*16);
	}
	if(send_cnt2!=0){
		VSPI_data_x(&color[send_cnt*240],send_cnt2*8);
	}
}





void LCD_IO_deinit(void)
{
	BLK_OFF();
	DELAY(100);
	LCD_RES_CLR();
	DELAY(100);
	LCD_RES_SET();
	DELAY(100);
}
/*st7789*/
void LCD_IO_Init(void)
{
    gpio_pad_select_gpio(LCD_RES);   
    gpio_pad_select_gpio(LCD_DC);   
    gpio_set_direction(LCD_RES,GPIO_MODE_OUTPUT);    //设置io19为输出模式
    gpio_set_direction(LCD_DC,GPIO_MODE_OUTPUT);    //设置io19为输出模式

	vspi_init();
	LCD_RES_CLR();
	DELAY(100);
	LCD_RES_SET();
	DELAY(100);
	//BLK_OFF();
	DELAY(100);

	LCD_WR_REG(0x11); 
	DELAY(120);

	LCD_WR_REG(0x36);
	LCD_WR_DATA8(0xc0);
	LCD_WR_REG(0x3A); 
	LCD_WR_DATA8(0x05);

	LCD_WR_REG(0xB2);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x33); 

	LCD_WR_REG(0xB7); 
	LCD_WR_DATA8(0x35);  

	LCD_WR_REG(0xBB);
	LCD_WR_DATA8(0x19);

	LCD_WR_REG(0xC0);
	LCD_WR_DATA8(0x2C);

	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);
	LCD_WR_DATA8(0x12);   

	LCD_WR_REG(0xC4);
	LCD_WR_DATA8(0x20);  

	LCD_WR_REG(0xC6); 
	LCD_WR_DATA8(0x0F);    

	LCD_WR_REG(0xD0); 
	LCD_WR_DATA8(0xA4);
	LCD_WR_DATA8(0xA1);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2B);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0x4C);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x0B);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x23);

	LCD_WR_REG(0xE1);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2C);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x44);
	LCD_WR_DATA8(0x51);
	LCD_WR_DATA8(0x2F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x20);
	LCD_WR_DATA8(0x23);

	LCD_WR_REG(0x21); 

	LCD_WR_REG(0x11);

	LCD_WR_REG(0x29);



	LCD_Clear(0x0000);

}






