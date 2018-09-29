# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# 按键教程 （BCM2835 C库版本）

## 玩转代码
> ### 在我们的彩虹扩展板上 4个按键分别对应着一下GPIO引脚
> |按键 | GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |KEY1|BCM6 |pin22| 34  |    
> |KEY2|BCM13|pin23| 36  |
> |KEY3|BCM19|pin24| 38  |
> |KEY4|BCM26|pin21| 40  |

### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoard_Rev2.0.pdf)<br>
<img src="https://img.alicdn.com/imgextra/i4/1887229091/O1CN012H1j60vRNTnaLYi_!!1887229091.png" width=50% height=50%/><br>
<img src="https://img.alicdn.com/imgextra/i4/1887229091/O1CN012H1j62lVcPG2HmM_!!1887229091.png" width=50% height=50%/><br>
> 我们采用的是跳帽来连接IO口，你可以在彩虹板上看到有一排彩虹色的跳帽，找到KEY1、KEY2、KEY3、KEY4，那就是与IO连接的端口，具体端口号请看原理图。
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。

### 事件版本 key_event.c
首先先用gedit、pluma、vim等文本编辑工具打开该文件夹下的key_event.c,如下，我们可以看看注释进行理解。
```C
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
```
### 扫描引脚版本 key_scan.c
首先先用gedit、pluma、vim等文本编辑工具打开该文件夹下的key_event.c,如下，我们可以看看注释进行理解。
```C
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
```
## 玩
> 当我们修改了代码后想运行时，必须将其编译成可执行文件，在此我们需要用到gcc工具，树莓派默认已安装好，若无，则百度相关教程安装好<br>
> 你也可以手动输入`gcc -o key_event key_event.c -lbcm2835`编译,`-l`代表链接库 后面跟库名
> `gcc -o key_scan key_scan.c -lbcm2835`
> 若无错误，则将会生成目标文件名的可执行文件，如有错误，请根据编译器提示排错。<br>
> 执行验证
> `./目标文件名`
> 例<br>
> `./led`
> 按了回车后，按下按键将会打印对应键值<br>
> 按下`Ctrl+C`结束程序<br>
