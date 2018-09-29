# MrzhangF1ghterStudio 彩虹扩展板系列
# 温控风扇教程 （wiringPi版本）
## 玩转代码
> ### 在我们的彩虹扩展板上 我们的风扇接到了树莓派唯一的一个原生PWM引脚，这样的好处是，我们不用软件模拟pwm，而是用硬件pwm，不耗费宝贵cpu资源
> 风扇| GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |FAN1|BCM18|pin1 |12   |

### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoardRev2.0.pdf)  
<img src="https://img.alicdn.com/imgextra/i2/1887229091/O1CN012H1j5v3ekuvLJA2_!!1887229091.png" width=50% height=50%/><br>  

> 如果你收到的是2p引脚的风扇，请按能看到金属触点一面朝上，靠左插入。  
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/fan/schematic/socket.png" width=50% height=50%/><br>  
> 请将风扇底部的散热垫保护膜撕开，然后将风扇对准CPU中心贴上去即可  请清洁后进行，
> 我们的风扇具有两个控制模式，一个是全速模式，一个是程序温控模式，可以通过跳帽选择，默认跳帽为程控模式，若需全速模式，则将跳帽接到FAN_CTL的右边两个排针  
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/fan/schematic/fan_ctl.png" width=50% height=50%/><br>  
> 当我们想接自己io的时候，可以将FAN_SPEED跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。

首先先用gedit、pluma、vim等文本编辑工具打开该文件夹下的fan.c,如下，我们可以看看注释进行理解。
```C
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <wiringPi.h>
#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define MAX_SIZE 32
#define FAN 1//原生PWM引脚 GPIO18,wiringPi引脚为1

int main(void)

{

	int fd;
	double temp = 0;
	char buf[MAX_SIZE];
	int speed;//速度值
	int min_speed=10;//最小速度值
	int temp_thre=40;//启动风扇的阈值
	int speed_step=100;//步进值
	if(wiringPiSetup()==-1)
	{
		printf("wiringPi gpio setup error\n");
		return -1;
	}
	pinMode(FAN,PWM_OUTPUT);//配置为PWM输出
	while(1)//循环检测
	{
		//open
		fd = open(TEMP_PATH,O_RDONLY);//打开文件
		if(fd<0)
		{

			printf("failed to open /sys/class/thermal/thermal_zone0/temp\n");
			return -1;

		}

		//read

		if(read(fd,buf,MAX_SIZE)<0)

		{

			printf("failed to read temp\n");
			return -1;

		}

		temp = atoi(buf)/1000.0;//将读到的温度值转化为浮点数;
		printf("cpu temp :%.2f\n",temp);
		if(temp<=temp_thre)//如果CPU温度小于启动阈值
		{
			pwmWrite(FAN,0);//风扇转速为0
		}
		else if(temp>temp_thre) //如果CPU温度大于启动阈值
		{
			pwmWrite(FAN,1023);//全速运转10ms启动防卡转
			usleep(10);
			speed = min_speed+(temp-temp_thre)*speed_step;//速度=最小速度+温度差*速度步进值
			if(speed>1023)//防止pwm溢出
				speed=1023;
			pwmWrite(FAN,speed);//设置pwm值
		}
		printf("speed:%d\n",speed);
		close(fd);//关闭文件
		sleep(5);//睡眠5s
	}

}
```
## 玩
> 当我们修改了代码后想运行时，必须将其编译成可执行文件，在此我们需要用到gcc工具，树莓派默认已安装好，若无，则百度相关教程安装好<br>
> 编译指令如下 `gcc -o 目标文件名 源文件名` -o的意思为输出可执行文件<br>
> 例:`gcc -o myled fan.c -lwiringPi` <br>
> 若无错误，则将会生成目标文件名的可执行文件，如有错误，请根据编译器提示排错。<br>
> 执行验证
> `./目标文件名`
> 例<br>
> `sudo ./fan &`
> 按了回车后，风扇将根据CPU温度而调整转速
> 按下`Ctrl+C`结束程序<br>
