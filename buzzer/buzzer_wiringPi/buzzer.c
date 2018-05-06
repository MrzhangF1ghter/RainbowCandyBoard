/********************************************************************************* 
  *Copyright(C),MrzhangF1ghter studio
  *FileName:buzzer.c
  *Author:MrzhangF1ghter 
  *Version:1.0 
  *Date:2018/5/6 
  *Description:树莓派彩虹IO扩展板蜂鸣器代码 wiringPi版本。
  *Others:Learn more from：https://github.com/MrzhangF1ghter/RainbowCandyBoard
  *Function List:
  *History:
  *compile:gcc -o buzzer buzzer.c -lbcm2835
  彩虹板上蜂鸣器物理连接如下
	蜂鸣器 | GPIO | wPi |排针号|
	BUZEER 	BCM12	pin26		32
**********************************************************************************/ 
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
				digitalWrite(BUZZER_PIN,HIGH);//蜂鸣器引脚低电平（高电平响）
				printf("BUZZER is on!\n");
				sleep(1);//程序休眠1秒
				digitalWrite(BUZZER_PIN,LOW);//蜂鸣器引脚高电平（低电平关闭）
				printf("BUZZER is off!\n");
				sleep(1);//程序休眠1秒
		}
}
