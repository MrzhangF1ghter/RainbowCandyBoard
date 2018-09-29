# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# BUZZER蜂鸣器教程 （wiringPi版本）

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
首先先用gedit、pluma、vim等文本编辑工具打开该文件夹下的buzzer.c,如下，我们可以看看注释进行理解。
```C
#include<stdio.h>
#include<unistd.h>
#include<wiringPi.h>//wiringPi路径
#define BUZZER_PIN 26
int main()
{
	int i;//定义一个用于循环计数变量
	printf("Welcome to IODevelopBoard!\n");//打印欢迎信息
	printf("BUZZER test,wiringPi version\n");//打印欢迎信息
	wiringPiSetup();//wiringPi库初始化
	pinMode(BUZZER_PIN,OUTPUT);//设置BUZZER_PIN引脚为输出模式
	digitalWrite(BUZZER_PIN,HIGH);//初始化为高电平
	while(1)//隔一秒响一次
	{
		digitalWrite(BUZZER_PIN,HIGH);//蜂鸣器引脚低电平（高电平响）
		printf("BUZZER is on!\n");
		sleep(1);//程序休眠1秒
		digitalWrite(BUZZER_PIN,LOW);//蜂鸣器引脚高电平（低电平关闭）
		printf("BUZZER is off!\n");
		sleep(1);//程序休眠1秒
	}
}
```
## 4.玩
> 当我们修改了代码后想运行时，必须将其编译成可执行文件，在此我们需要用到gcc工具，树莓派默认已安装好，若无，则百度相关教程安装好<br>
> 编译指令如下 `gcc -o 目标文件名 源文件名` -o的意思为输出可执行文件<br>
> 例:`gcc -o buzzer buzzer.c` <br>
> 若无错误，则将会生成目标文件名的可执行文件，如有错误，请检查错误，排错。<br>
> 执行验证
> `./目标文件名`
>例:`./buzzer`
>按了回车后，你将会听到蜂鸣器间歇鸣叫<br>
