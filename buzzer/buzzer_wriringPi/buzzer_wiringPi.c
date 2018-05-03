/**************************************************************
	author:MrzhangF1ghter 
	Last Edit time:2018-4-30
	此为RainbowBoard 蜂鸣器例程 使用wiringPi库
	彩虹板上led灯物理连接如下
	蜂鸣器   | GPIO | wPi |排针号|
	BUZEER BCM12->pin26	32
**************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<wiringPi.h>//wiringPi路径
#define BUZZER_PIN 26
int main()
{
		int i;//定义一个用于循环计数变量
		printf("Welcome to IODevelopBoard!\n");//打印欢迎信息
		printf("BUZZER test,wiringPi version\n");//打印欢迎信息
		wiringPiSetup();//wiringPi库初始化
		pinMode(BUZZER_PIN,OUTPUT);//设置BUZZER_PIN引脚为输出模式
		digitalWrite(BUZZER_PIN,HIGH);//初始化为高电平
		
		while(1)//隔一秒响一次
		{
				digitalWrite(BUZZER_PIN,LOW);//蜂鸣器引脚低电平（低电平响）
				printf("BUZZER is on!\n");
				sleep(1);//程序休眠1秒
				digitalWrite(BUZZER_PIN,HIGH);//蜂鸣器引脚高电平（高电平关闭）
				printf("BUZZER is off!\n");
				sleep(1);//程序休眠1秒
		}
}
