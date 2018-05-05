#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <time.h>
#include "SSD1306.h"

char value[11]={'0','1','2','3','4','5','6','7','8','9',':'};
int main(int argc,char **argv)
{
	time_t now;//定义时间结构体
	struct tm *timenow;
	if(wiringPiSetup() < 0)return 1;
	printf("OLED Test Program wiringPi version.\n");
	SSD1306_begin();
	SSD1306_string(0,16,"RainbowI/O",16,1);
	SSD1306_display();
	delay(2000);
	SSD1306_display();	
	while(1)
	{
		time(&now);//获取当前时间赋值
		timenow = localtime(&now);
		SSD1306_char3216(0,16, value[timenow->tm_hour/10]);//分离运算
		
    	SSD1306_char3216(16,16, value[timenow->tm_hour%10]);
    	SSD1306_char3216(32,16, ':');
    	SSD1306_char3216(48,16, value[timenow->tm_min/10]);
    	SSD1306_char3216(64,16, value[timenow->tm_min%10]);
    	SSD1306_char3216(80,16, ':');
    	SSD1306_char3216(96,16, value[timenow->tm_sec/10]);
    	SSD1306_char3216(112,16, value[timenow->tm_sec%10]);
		SSD1306_display();
    }
	return 0;
}

