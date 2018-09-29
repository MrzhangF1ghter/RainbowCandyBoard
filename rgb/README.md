# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# RGB LED教程 （wiringPi版本）

## 玩转代码
> ### 在我们的彩虹扩展板上 RGB LED分别对应着一下GPIO引脚
> RGB灯通过色光原理，用红绿蓝三盏LED灯混出不同颜色，通过控制三盏灯的亮度实现调色。    

> 灯   | GPIO | wPi |排针号|
> |----|-----|-----|-----|
> | 红 |BCM20|pin27| 26  |    
> | 绿 |BCM16|pin28| 28  |
> | 蓝 |BCM21|pin29| 30  |

### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoard_Rev2.0.pdf)<br>
<img src="https://img.alicdn.com/imgextra/i4/1887229091/O1CN012H1j61zGyAhDQDa_!!1887229091.png" width=50% height=50%/><br>
<img src="https://img.alicdn.com/imgextra/i1/1887229091/O1CN012H1j60vjdf4CkUc_!!1887229091.png" width=50% height=50%/><br>
> 我们采用的是跳帽来连接IO口，你可以在彩虹板上看到有一排彩虹色的跳帽，找到G-、R-、B-，那就是与IO连接的端口，具体端口号请看原理图。
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。

首先先用gedit、puma、vim等文本编辑工具打开该文件夹下的led_wiringPi.c,如下，我们可以看看注释进行理解。
```C
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

#define uchar unsigned char

#define LedPinRed    27
#define LedPinGreen  28
#define LedPinBlue   29

void ledInit(void)
{
	softPwmCreate(LedPinRed,  0, 100);
	softPwmCreate(LedPinGreen,0, 100);
	softPwmCreate(LedPinBlue, 0, 100);
}

void ledColorSet(uchar r_val, uchar g_val, uchar b_val)
{
	softPwmWrite(LedPinRed,   r_val);
	softPwmWrite(LedPinGreen, g_val);
	softPwmWrite(LedPinBlue,  b_val);
}

int main(void)
{
	int i;

	if(wiringPiSetup() == -1){      //when initialize wiring failed,print message to screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	ledInit();

	while(1){
		ledColorSet(0xff,0x00,0x00);   //red	
		delay(500);
		ledColorSet(0x00,0xff,0x00);   //green
		delay(500);
		ledColorSet(0x00,0x00,0xff);   //blue
		delay(500);

		ledColorSet(0xff,0xff,0x00);   //yellow
		delay(500);
		ledColorSet(0xff,0x00,0xff);   //pick
		delay(500);
		ledColorSet(0xc0,0xff,0x3e);
		delay(500);

		ledColorSet(0x94,0x00,0xd3);
		delay(500);
		ledColorSet(0x76,0xee,0x00);
		delay(500);
		ledColorSet(0x00,0xc5,0xcd);	
		delay(500);

	}

	return 0;
}
```
## 玩
> 当我们修改了代码后想运行时，必须将其编译成可执行文件，在此我们需要用到gcc工具，树莓派默认已安装好，若无，则百度相关教程安装好<br>
> 编译指令如下 `gcc -o 目标文件名 源文件名` -o的意思为输出可执行文件<br>
> 例:`gcc -o rgb rgb.c -lwiringPi -lpthread -pthread` <br> 需要用到多线程，所以需要连接相关库
> 若无错误，则将会生成目标文件名的可执行文件，如有错误，请根据编译器提示排错。<br>
> 执行验证
> `./目标文件名`
> 例<br>
> `./rgb`
> 按了回车后，你将会发现彩虹板上的RGB以不同颜色轮流显示<br>
> 按下`Ctrl+C`结束程序<br>
