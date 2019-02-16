/**************************************************************
	author:MrzhangF1ghter 
	Last Edit time:2018-4-30
	��ΪRainbowBoard LED���� ʹ��wiringPi��
	�ʺ����led��������������
	��   | GPIO | wPi |�����|
	LED1 BCM23->pin4	16    
	LED2 BCM27->pin2	13
	LED3 BCM22->pin3	15
	LED4 BCM5 ->pin21	29
**************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<wiringPi.h>//wiringPi·��
int main()
{
		int leds_pin[4]={4,2,3,21};//����һ�����led��Ӧgpio���źŵ���������
		int i;//����һ������ѭ����������
		printf("Welcome to IODevelopBoard!\n");//��ӡ��ӭ��Ϣ
		printf("LEDS test,wiringPi version\n");//��ӡ��ӭ��Ϣ
		wiringPiSetup();//wiringPi���ʼ��
		/*��ѭ��һ���������������LED����ΪOUTPUTģʽ��
		����ԭ��digitalWrite (int pin, int value)*/
		for(i=0;i<4;i++)
		{
			pinMode(leds_pin[i],OUTPUT);//����led_pin[i]����Ϊ���ģʽ
			digitalWrite(leds_pin[i],HIGH);//��ʼ��Ϊ�ߵ�ƽ
		}
		
		while(1)//��ˮ��
		{
			for(i=0;i<4;i++)
			{
				digitalWrite(leds_pin[i],LOW);//LED1���ŵ͵�ƽ���͵�ƽ������
				printf("LED%d is on!\n",i+1);
				sleep(1);//��������1��
				digitalWrite(leds_pin[i],HIGH);//LED1���Ÿߵ�ƽ���ߵ�ƽϨ��
				printf("LED%d is off!\n",i+1);
				sleep(1);//��������1��
			}
		}
}
