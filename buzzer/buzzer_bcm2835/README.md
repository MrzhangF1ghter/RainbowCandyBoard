# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# BUZZER蜂鸣器教程 （BCM2835 C库版本）

## 玩转代码
> ### 在我们的彩虹扩展板上 4盏LED分别对应着一下GPIO引脚
> 蜂鸣器| GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |BUZZER|BCM12|pin26 | 32 |    
### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoard_Rev2.0.pdf)<br>
<img src="https://img.alicdn.com/imgextra/i3/1887229091/O1CN012H1j61P1uXoqRDB_!!1887229091.png" width=50% height=50%/><br>
<img src="https://img.alicdn.com/imgextra/i1/1887229091/O1CN012H1j609kV1GOzTL_!!1887229091.png" width=50% height=50%/><br>
> 我们采用的是跳帽来连接IO口，你可以在彩虹板上看到有一排彩虹色的跳帽，找到BUZZER，那就是蜂鸣器与IO连接的端口，具体端口号请看原理图。
> 蜂鸣器处于大电流外设，需要用三极管驱动，该驱动电路为高电平导通。
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。

首先先用gedit、puma、vim等文本编辑工具打开该文件夹下的buzzer.c,如下，我们可以看看注释进行理解。
```C
#include <bcm2835.h>
#include <stdio.h>
#define BUZZER_PIN 12//宏定义蜂鸣器引脚
int main()
{
	printf("Welcome to IODevelopBoard!\n");//打印欢迎信息
	printf("BUZZER test,wiringPi version\n");//打印欢迎信息
	if (!bcm2835_init())return -1;//若初始化失败，则返回-1失败码
	bcm2835_gpio_fsel(BUZZER_PIN, BCM2835_GPIO_FSEL_OUTP);//利用循环和数组配置引脚
	while (1)
	{
			bcm2835_gpio_write(BUZZER_PIN, HIGH);//高电平鸣叫
			bcm2835_delay(100);//延时500ms
	    bcm2835_gpio_write(BUZZER_PIN, LOW);//低电平关闭
	   	bcm2835_delay(500);
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
buzzer:buzzer.c
	gcc -Wall buzzer.c -o buzzer -lbcm2835
clean:
	rm buzzer
```
> 相当于手动输入 `gcc -o buzzer buzzer.c -lbcm2835`
> 若无错误，则将会生成目标文件名的可执行文件，如有错误，请根据编译器提示排错。<br>
> 执行验证
> `./目标文件名`
> 例<br>
> `./buzzer`
> 按了回车后，你将会听到蜂鸣器间歇鸣叫<br>
> 按下`Ctrl+C`结束程序<br>
