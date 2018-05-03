# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# 蜂鸣器教程 （wiringPi版本）
## 1.首先先下载源码，源码下载步骤如下
> 1.1 首先我们要安装git工具，若无则在终端中输入:<br>
> `sudo apt-get install git-core`<br>
> 如果在过程中出现错误，尝试更新软件源,然后再重试：<br>
> `sudo apt-get update`<br>
> 1.2 定位到你想下载源代码文件夹的位置,比如我想放到用户目录下
> `cd ~\` ~代表当前用户的home目录<br>
> 1.3 通过 git 在线获得我提供的最新源代码，输入命令：<br>
> `git clone git:github.com/MrzhangF1ghter/RainbowCandyBoard.git`<br>
> 等待完成done
> 1.4 进入源码库所在的文件夹，该文件夹在前面无操作的话，就在你的家目录下<br>
> `cd ~/RainbowCandyBoard/LED/led_wiringPi/`<br>
> 执行`ls`指令，你将会看到有两个文件，一个是绿色的led_wiringPi可执行文件，一个是led_wiringPi.c<br>
> 你可以输入`./led_wiringPi`,若wiringPi库安装无误的话，你将会看到彩虹扩展板上的4盏灯在轮流闪动，也就是流水灯效果<br>
> 1.6 若需要更新彩虹板的源码库，输入以下命令：<br>
> `cd ~`<br>(cd到你之前放源码的地方)
> `git pull origin`<br>

## 2.安装wiringPi库
> ### 下面是安装wiringPi的教程，若安装好了则跳过。
> 2.1 首先我们要安装git工具，若无则在终端中输入:<br>
> `sudo apt-get install git-core`<br>
> 如果在过程中出现错误，尝试更新软件源,然后再重试：<br>
> `sudo apt-get update`<br>
> 2.2 接着通过 git 在线获得wiringPi的源代码，输入命令：<br>
> `git clone git://git.drogon.net/wiringPi`<br>
> 等待完成done
> 2.3 进入wiringPi库所在的文件夹，该文件夹在前面无操作的话，就在你的家目录下<br>
> `cd ~/wiringPi`<br>
> 2.4 执行`./build`，该命令将会自动编译和安装wiringPi库<br>
> 2.5 wiringPi包括一套gpio命令，使用gpio命令可以控制树莓派上的各种接口，通过以下指令可以测试wiringPi是否安装成功。<br>
> `gpio -v`<br>
> `gpio readall`<br>
> 2.6 若需要更新wiringPi库，输入以下命令：<br>
> `cd ~/wiringPi`<br>
> `git pull origin`<br>

> 到此，wiringPi库安装完成<br>
## 3.玩转代码
> ### 在我们的彩虹扩展板上 蜂鸣器通过三极管驱动,三极管受引脚控制，实现小电流(引脚)控制大电流(外设)
> 蜂鸣器| GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |BUZZER|BCM12|pin26|32|
### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/%E5%8E%9F%E7%90%86%E5%9B%BE/RainbowCandyBoard.pdf)
![image](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/BUZZER/%E5%8E%9F%E7%90%86%E5%9B%BE/jumper.png)
> 我们采用的是跳帽来连接IO口，你可以在彩虹板上看到有一排彩虹色的跳帽，找到LED1、LED2、LED3、LED4，那就是与IO连接的端口，具体端口号请看原理图。
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。

首先先用gedit、puma、vim等文本编辑工具打开该文件夹下的led_wiringPi.c,如下，我们可以看看注释进行理解。
```C
#include<stdio.h>
#include<unistd.h>
#include<wiringPi.h>//wiringPi路径
int main()
{
  int leds_pin[4]={0,2,3,21};//定义一个存放led对应gpio引脚号的整形数组
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
## 4.玩
> 当我们修改了代码后想运行时，必须将其编译成可执行文件，在此我们需要用到gcc工具，树莓派默认已安装好，若无，则百度相关教程安装好<br>
> 编译指令如下 `gcc -o 目标文件名 源文件名` -o的意思为输出可执行文件<br>
> 例:`gcc -o myled led_wiringPi.c` <br>
> 若无错误，则将会生成目标文件名的可执行文件，如有错误，请检查错误，排错。<br>
> 执行验证
> `./目标文件名`
>例:`./myled`
>按了回车后，你将会发现彩虹板上的LED随着你的要求而亮灭<br>
