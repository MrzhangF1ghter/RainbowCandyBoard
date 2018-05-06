# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# LED教程 （BCM2835 C库版本）

## 玩转代码
> ### 在我们的彩虹扩展板上 4盏LED分别对应着一下GPIO引脚
> 灯   | GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |LED1|BCM17|pin0 | 11 |    
> |LED2|BCM27|pin2 |13  |
> |LED3|BCM22|pin3 |15  |
> |LED4|BCM5 |pin21|29  |

### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoard.pdf)<br>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/led/schematic/LED.png" width=50% height=50%/><br>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/led/schematic/led_pin.png" width=50% height=50%/><br>
> 我们采用的是跳帽来连接IO口，你可以在彩虹板上看到有一排彩虹色的跳帽，找到LED1、LED2、LED3、LED4，那就是与IO连接的端口，具体端口号请看原理图。
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。

首先先用gedit、puma、vim等文本编辑工具打开该文件夹下的led.c,如下，我们可以看看注释进行理解。
```C
#include <bcm2835.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	int leds_pin[4]={17,27,22,5};//定义一个存放led对应gpio引脚号的整形数组
	int i;//定义一个用于循环计数变量
	printf("Welcome to IODevelopBoard!\n");//打印欢迎信息
	printf("LEDS test,wiringPi version\n");//打印欢迎信息
	if (!bcm2835_init())return -1;//若初始化失败，则返回-1失败码
	for(i=0;i<4;i++)
	{
	    bcm2835_gpio_fsel(leds_pin[i], BCM2835_GPIO_FSEL_OUTP);//利用循环和数组配置引脚
	}
	while (1)
	{
		for(i=0;i<4;i++)
		{
			bcm2835_gpio_write(leds_pin[i], LOW);//低电平点亮
			bcm2835_delay(500);//延时500ms
	    bcm2835_gpio_write(leds_pin[i], HIGH);//高电平熄灭
	    bcm2835_delay(500);
		}
	}
	bcm2835_close();
	return 0;
}
```
## 玩
> 当我们修改了代码后想运行时，必须将其编译成可执行文件，在此我们需要用到gcc工具，树莓派默认已安装好，若无，则百度相关教程安装好<br>
> 此版本提供了Makefile文件，Makefile文件描述了整个工程的编译、链接等规则，用户只需要运行make即可按照程序员所写好的规则编译程序。
> 此Makefile文件内容如下
```C
led:led.c
	gcc -Wall led.c -o led -lbcm2835
clean:
	rm led
```
> 你也可以手动输入`gcc -o led led.c -lbcm2835`编译,`-l`代表链接库 后面跟库名
> 若无错误，则将会生成目标文件名的可执行文件，如有错误，请根据编译器提示排错。<br>
> 执行验证
> `./目标文件名`
> 例<br>
> `./led`
> 按了回车后，你将会发现彩虹板上的LED以流水的形式闪烁<br>
> 按下`Ctrl+C`结束程序<br>
## 扩展
> 用户可以扩展使用自己的的LED进行亮灭，只需把对应跳帽拔掉，接上排线即可。请注意使用同一个电源（共地）
> <img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/led/schematic/led_jumper.png" width=50% height=50%/><br>
