/********************************************************************************* 
  *Copyright(C),MrzhangF1ghter studio
  *FileName:buzzer.c
  *Author:MrzhangF1ghter 
  *Version:1.0 
  *Date:2018/5/6 
  *Description:树莓派彩虹IO扩展板蜂鸣器代码 bcm2835 c库版本。
  *Others:Learn more from：https://github.com/MrzhangF1ghter/RainbowCandyBoard
  *Function List:
  *History:
  *compile:gcc -o buzzer buzzer.c -lbcm2835
  彩虹板上蜂鸣器物理连接如下
	蜂鸣器 | GPIO | wPi |排针号|
	BUZEER 	BCM12	pin26		32
**********************************************************************************/ 
#include <bcm2835.h>
#include <stdio.h>
#define BUZZER_PIN 12//宏定义蜂鸣器引脚
int main()
{
	printf("Welcome to IODevelopBoard!\n");//打印欢迎信息
	printf("BUZZER test,wiringPi version\n");//打印欢迎信息
	if (!bcm2835_init())return -1;//若初始化失败，则返回-1失败码
	bcm2835_gpio_fsel(BUZZER_PIN, BCM2835_GPIO_FSEL_OUTP);//利用循环和数组配置引脚
	while (1)
	{
			bcm2835_gpio_write(BUZZER_PIN, HIGH);//高电平鸣叫
			bcm2835_delay(100);//延时500ms
	    bcm2835_gpio_write(BUZZER_PIN, LOW);//低电平关闭
	   	bcm2835_delay(500);
	}
	bcm2835_close();
	return 0;
}
