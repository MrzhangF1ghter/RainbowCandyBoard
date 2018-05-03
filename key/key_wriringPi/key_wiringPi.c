#include<stdio.h>
#include<unistd.h>
#include<wiringPi.h>//wiringPi路径

#define LED1 0//宏定义LED1为GPIO17，wiringPi库为wPi0 (GPIO_GEN0)
#define LED2 2
#define LED3 3
#define LED4 21

#define KEY1 22//宏定义LED1为GPIO17，wiringPi库为wPi0 (GPIO_GEN0)
#define KEY2 23
#define KEY3 24
#define KEY4 25
int main()
{
		int leds_pin[4]={0,2,3,21};//存放led对应gpio引脚号的数组
		int keys_pin[4]={22,23,24,25};//存放led对应gpio引脚号的数组
		int i,count=0;//计数变量
		printf("Welcome to IODevelopBoard!\n");
		printf("KEYs test,wiringPi version\n");
		wiringPiSetup();//wiringPi库初始化
		/*用循环一条语句设置完所有按键引脚为OUTPUT模式，
		函数原型digitalWrite (int pin, int value)*/
		for(i=0;i<4;i++)
		{
			//LED初始化
			pinMode(leds_pin[i],OUTPUT);
			digitalWrite(leds_pin[i],HIGH);//初始化为高电平
			//按键初始化
			pinMode(keys_pin[i],INPUT);
			pullUpDnControl(keys_pin[i],PUD_UP);
		}
		
		while(1)//流水灯
		{
			//扫描按键法
			for(int i=0;i<4;i++)
			{
				if(!digitalRead(keys_pin[i]))
				{
						delay(20);
						if(!digitalRead(keys_pin[i]))
						{
							while(!digitalRead(keys_pin[i]));//等待松手
						}
						printf("key%d has pressed!\n",i+1);
						count++;
						if(count%2==0)
							digitalWrite(leds_pin[i],LOW);//通过一个变量来颠倒灯的状态
						else
							digitalWrite(leds_pin[i],HIGH);//初始化为高电平
						if(count==2)
							count=0;
				}
			}
		}
	}