/**************************************************************
	author:MrzhangF1ghter 
	Last Edit time:2018-4-30
	此为RainbowBoard LED例程 使用wiringPi库
	彩虹板上led灯物理连接如下
	灯   | GPIO | wPi |排针号|
	LED1 BCM23->pin4	16    
	LED2 BCM27->pin2	13
	LED3 BCM22->pin3	15
	LED4 BCM5 ->pin21	29
**************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<wiringPi.h>//wiringPi路径
int main()
{
		int leds_pin[4]={4,2,3,21};//定义一个存放led对应gpio引脚号的整形数组
		int i;//定义一个用于循环计数变量
		printf("Welcome to IODevelopBoard!\n");//打印欢迎信息
		printf("LEDS test,wiringPi version\n");//打印欢迎信息
		wiringPiSetup();//wiringPi库初始化
		/*用循环一条语句设置完所有LED引脚为OUTPUT模式，
		函数原型digitalWrite (int pin, int value)*/
		for(i=0;i<4;i++)
		{
			pinMode(leds_pin[i],OUTPUT);//设置led_pin[i]引脚为输出模式
			digitalWrite(leds_pin[i],HIGH);//初始化为高电平
		}
		
		while(1)//流水灯
		{
			for(i=0;i<4;i++)
			{
				digitalWrite(leds_pin[i],LOW);//LED1引脚低电平（低电平点亮）
				printf("LED%d is on!\n",i+1);
				sleep(1);//程序休眠1秒
				digitalWrite(leds_pin[i],HIGH);//LED1引脚高电平（高电平熄灭）
				printf("LED%d is off!\n",i+1);
				sleep(1);//程序休眠1秒
			}
		}
}
