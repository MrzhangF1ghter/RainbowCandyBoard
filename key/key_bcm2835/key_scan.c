/********************************************************************************* 
  *Copyright(C),MrzhangF1ghter studio
  *FileName:key_scan.c
  *Author:MrzhangF1ghter 
  *Version:1.0 
  *Date:2018/5/5 
  *Description:树莓派彩虹IO扩展板按键代码 扫描方法实现。
  *Others:Learn more from：https://github.com/MrzhangF1ghter/RainbowCandyBoard
  												 http://www.airspayce.com/mikem/bcm2835/group__gpio.html
  *Function List:
  *History:
  *compile:gcc -o key_scan key_scan.c -lbcm2835
  彩虹板上按键物理连接如下
   按键 |GPIO| wPi |排针号|
   KEY1 BCM6 	pin22	34    
   KEY2 BCM13 pin23	36
   KEY3 BCM19 pin24	38
   KEY4 BCM26 pin25 40
**********************************************************************************/  
#include <bcm2835.h>
#include <stdio.h>

int keys_pin[4]={6,13,19,26};//定义一个存放led对应gpio引脚号的整形数组
int i;
int main()
{
	printf("Key Test Program,bcm2835 version\n");	
	if (!bcm2835_init())return 1;
	for(i=0;i<4;i++)//循环设置keys_pin数组里的引脚
	{
		bcm2835_gpio_fsel(keys_pin[i], BCM2835_GPIO_FSEL_INPT);//设置为输入模式
		bcm2835_gpio_set_pud(keys_pin[i], BCM2835_GPIO_PUD_UP);//设置为上拉模式
	}
	i=0;
	while (1)
	{
		i++;
		if(bcm2835_gpio_lev(keys_pin[i]) == 0)//检测到此引脚为低电平时
		{  
			printf ("KEY%d PRESS\n",i+1) ;
    		while(bcm2835_gpio_lev(keys_pin[i]) == 0)//等待按键松开 消抖
				bcm2835_delay(100);
		}
		bcm2835_delay(10);//延时10ms
		if(i==3)//循环计数清0以重新计数
			i=-1;
	}
	bcm2835_close();
	return 0;
}
