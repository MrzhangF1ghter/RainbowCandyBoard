# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# LED教程 （wiringPi版本）
# 此代码为Rev2.0LED 例程
## 玩转代码
> ### 在我们的彩虹扩展板上 4盏LED分别对应着一下GPIO引脚（Rev2.0）
> 灯   | GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |LED1|BCM23|pin4 |16   |    
> |LED2|BCM27|pin2 |13   |
> |LED3|BCM22|pin3 |15   |
> |LED4|BCM5 |pin21|29   |

### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoardRev2.0.pdf)<br>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/led_BoardRev2.0/schematic/LED.png" width=50% height=50%/><br>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/led_BoardRev2.0/schematic/led_pin.png" width=50% height=50%/><br>
> 我们采用的是跳帽来连接IO口，你可以在彩虹板上看到有一排彩虹色的跳帽，找到LED1、LED2、LED3、LED4，那就是与IO连接的端口，具体端口号请看原理图。
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。

首先先用gedit、pluma、vim等文本编辑工具打开该文件夹下的led_wiringPi.c,如下，我们可以看看注释进行理解。
```C
#include<stdio.h>
#include<unistd.h>
#include<wiringPi.h>//wiringPi路径
int main()
{
  int leds_pin[4]={4,2,3,21};//定义一个存放led对应gpio引脚号的整形数组
  int i;//定义一个用于循环计数变量
  printf("Welcome to IODevelopBoard!\n");//打印欢迎信息
  printf("LEDS test,wiringPi version\n");//打印欢迎信息
  wiringPiSetup();//wiringPi库初始化
  /*用循环一条语句设置完所有LED引脚为OUTPUT模式，
    函数原型digitalWrite (int pin, int value)*/
  for(i=0;i<4;i++)
  {
    pinMode(leds_pin[i],OUTPUT);//设置led_pin[i]引脚为输出模式
    digitalWrite(leds_pin[i],HIGH);//初始化为高电平
  }
  while(1)//流水灯
  {
    for(i=0;i<4;i++)
    {
      digitalWrite(leds_pin[i],LOW);//LED1引脚低电平（低电平点亮）
      printf("LED%d is on!\n",i+1);
      sleep(1);//程序休眠1秒
      digitalWrite(leds_pin[i],HIGH);//LED1引脚高电平（高电平熄灭）
      printf("LED%d is off!\n",i+1);
      sleep(1);//程序休眠1秒
    }
  }
}
```
## 玩
> 当我们修改了代码后想运行时，必须将其编译成可执行文件，在此我们需要用到gcc工具，树莓派默认已安装好，若无，则百度相关教程安装好<br>
> 编译指令如下 `gcc -o 目标文件名 源文件名` -o的意思为输出可执行文件<br>
> 例:`gcc -o myled led_wiringPi.c -lwiringPi` <br>
> 若无错误，则将会生成目标文件名的可执行文件，如有错误，请根据编译器提示排错。<br>
> 执行验证
> `./目标文件名`
> 例<br>
> `./led`
> 按了回车后，你将会发现彩虹板上的LED以流水的形式闪烁<br>
> 按下`Ctrl+C`结束程序<br>
## 扩展
> 用户可以扩展使用自己的的LED进行亮灭，只需把对应跳帽拔掉，接上排线即可。请注意使用同一个电源（共地）
> <img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/led_BoardRev2.0/schematic/led_jumper.png" width=50% height=50%/><br>
