/********************************************************************************* 
  *Copyright(C),MrzhangF1ghter studio
  *FileName:key_event.c
  *Author:MrzhangF1ghter 
  *Version:1.0 
  *Date:2018/5/5 
  *Description:树莓派彩虹IO扩展板按键代码 事件方法实现。
  *Others:Learn more from：https://github.com/MrzhangF1ghter/RainbowCandyBoard
  												 http://www.airspayce.com/mikem/bcm2835/group__gpio.html
  *Function List:
  *History:
  *compile:gcc -o key_event key_event.c -lbcm2835
**********************************************************************************/  
#include <bcm2835.h>
#include <stdio.h>

int keys_pin[4]={6,13,19,26};//定义一个数组来放置按键引脚
int i;
int main()
{
	printf("Key Test Program,bcm2835 event version\n");	
	if (!bcm2835_init())return 1;
	for(i=0;i<4;i++)//循环设置keys_pin数组里的引脚
	{
		bcm2835_gpio_fsel(keys_pin[i], BCM2835_GPIO_FSEL_INPT);//设置为输入模式
		bcm2835_gpio_set_pud(keys_pin[i], BCM2835_GPIO_PUD_UP);//设置为上拉模式
		bcm2835_gpio_len(keys_pin[i]);//使能低电平检测，按键低电平时触发事件
	}
	i=0;
	while (1)
	{	
		i++;//循环检测
		if(bcm2835_gpio_eds(keys_pin[i]))//如果该按键低电平
		{  
			bcm2835_gpio_set_eds(keys_pin[i]);//设置事件状态寄存器为1
			printf("KEY%d EVENT DETECT\n",i+1);//打印检测到事件了
		}
		if(i==3)//循环计数清0以重新计数
			i=-1;
		bcm2835_delay(50);
	}
	bcm2835_close();
	return 0;
}
