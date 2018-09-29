# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# 按键教程 （wiringPi版本）

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

首先先用gedit、pluma、vim等文本编辑工具打开该文件夹下的key.c,如下，我们可以看看注释进行理解。
```C
#include<stdio.h>
#include<unistd.h>
#include<wiringPi.h>//wiringPi路径
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
						delay(100);
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
```
## 玩
> 当我们修改了代码后想运行时，必须将其编译成可执行文件，在此我们需要用到gcc工具，树莓派默认已安装好，若无，则百度相关教程安装好<br>
> 编译指令如下 `gcc -o 目标文件名 源文件名` -o的意思为输出可执行文件<br>
> 例:`gcc -o key key.c -lwiringPi` <br>
> 若无错误，则将会生成目标文件名的可执行文件，如有错误，请根据编译器提示排错。<br>
> 执行验证
> `./目标文件名`
> 例<br>
> `./key`
> 按了回车后，按下按键将会打印键值，LED灯会亮灭<br>
> 按下`Ctrl+C`结束程序<br>
