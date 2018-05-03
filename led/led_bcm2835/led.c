/* blink.c
 * you can build this with something like:
 * gcc -Wall blink.c -o blink -lbcm2835
 * sudo ./blink
 * author:MrzhangF1ghter 
 * Last Edit time:2018-5-1
 * 此为RainbowBoard LED例程 使用BCM2835库
 * 彩虹板上led灯物理连接如下
   灯   | GPIO | wPi |排针号|
   LED1 BCM17->pin0	 11    
   LED2 BCM27->pin2	 13
   LED3 BCM22->pin3	 15
   LED4 BCM5 ->pin21 29
*/

#include <bcm2835.h>
#include <stdio.h>
#define PIN 26
int main(int argc, char **argv)
{
	int leds_pin[4]={17,27,22,5};//定义一个存放led对应gpio引脚号的整形数组
	int i;//定义一个用于循环计数变量
	printf("Welcome to IODevelopBoard!\n");//打印欢迎信息
	printf("LEDS test,wiringPi version\n");//打印欢迎信息
    if (!bcm2835_init())return 1;
	for(i=0;i<4;i++)
    	bcm2835_gpio_fsel(leds_pin[i], BCM2835_GPIO_FSEL_OUTP);//配置引脚

    while (1)
    {
		for(i=0;i<4;i++)
		{
			bcm2835_gpio_write(leds_pin[i], LOW);
			bcm2835_delay(500);
        	bcm2835_gpio_write(leds_pin[i], HIGH);
       	 	bcm2835_delay(500);
		}
    }
    bcm2835_close();
    return 0;
}
