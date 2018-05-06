/********************************************************************************* 
  *Copyright(C),MrzhangF1ghter studio
  *FileName:led.c
  *Author:MrzhangF1ghter 
  *Version:1.0 
  *Date:2018/5/6 
  *Description:树莓派彩虹IO扩展板LED代码 bcm2835版本。
  *Others:Learn more from：https://github.com/MrzhangF1ghter/RainbowCandyBoard
  *Function List:
  *History:
  *compile:gcc -o led led.c -lwiringPi
  彩虹板上按键物理连接如下
   灯 | GPIO | wPi |排针号|
   LED1 BCM17	pin0	 11    
   LED2 BCM27	pin2	 13
   LED3 BCM22	pin3	 15
   LED4 BCM5 	pin21  29
**********************************************************************************/ 
#include <bcm2835.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	int leds_pin[4]={17,27,22,5};//定义一个存放led对应gpio引脚号的整形数组
	int i;//定义一个用于循环计数变量
	printf("Welcome to IODevelopBoard!\n");//打印欢迎信息
	printf("LEDS test,wiringPi version\n");//打印欢迎信息
	if (!bcm2835_init())return -1;//若初始化失败，则返回-1失败码
	for(i=0;i<4;i++)
	{
	    bcm2835_gpio_fsel(leds_pin[i], BCM2835_GPIO_FSEL_OUTP);//利用循环和数组配置引脚
	}
	while (1)
	{
		for(i=0;i<4;i++)
		{
			bcm2835_gpio_write(leds_pin[i], LOW);//低电平点亮
			bcm2835_delay(500);//延时500ms
	    bcm2835_gpio_write(leds_pin[i], HIGH);//高电平熄灭
	    bcm2835_delay(500);
		}
	}
	bcm2835_close();
	return 0;
}
