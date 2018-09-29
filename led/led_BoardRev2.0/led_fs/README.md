# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# LED教程 （fs 文件操作版本）
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
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoard_Rev2.0.pdf)<br>
<img src="https://img.alicdn.com/imgextra/i1/1887229091/O1CN012H1j61jqMiwQ6zQ_!!1887229091.png" width=50% height=50%/><br>
<img src="https://img.alicdn.com/imgextra/i2/1887229091/O1CN012H1j61VWcYfRF8n_!!1887229091.png" width=50% height=50%/><br>
<br>
> 我们采用的是跳帽来连接IO口，你可以在彩虹板上看到有一排彩虹色的跳帽，找到LED1、LED2、LED3、LED4，那就是与IO连接的端口，具体端口号请看原理图。
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。


首先先用gedit、pluma、vim等文本编辑工具打开该文件夹下的led.c,如下，我们可以看看注释进行理解。
> 在Linux下，每个设备可以看做一个文件，比如LED我们可以看成一个文件，使用文件操作方法write(),read()，在内核中相关驱动将会将应用层的读写方法指向驱动中的读写方法，从而实现操作LED，对于用户来说，无需关心内核驱动如何实现，只需编写应用层软件即可。
```C
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1

#define BUFFER_MAX      3
#define DIRECTION_MAX   48

static int GPIOExport(int pin)
{
    char buffer[BUFFER_MAX];
    int len;
    int fd;
		/*访问/sys/class/gpio目录，向export文件写入GPIO编号，
		使得该GPIO的操作接口从内核空间暴露到用户空间*/
    fd = open("/sys/class/gpio/export", O_WRONLY);//暴露gpio操作接口
    if (fd < 0) {
        fprintf(stderr, "Failed to open export for writing!\n");
        return(-1);
    }
		
    len = snprintf(buffer, BUFFER_MAX, "%d", pin);
    //把传进来的pin也就是引脚号写入export文件
    write(fd, buffer, len);
    //文件操作完成需要关闭文件
    close(fd);
    return(0);
}

static int GPIOUnexport(int pin)//隐藏gpio接口
{
    char buffer[BUFFER_MAX];
    int len;
    int fd;

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Failed to open unexport for writing!\n");
        return(-1);
    }

    len = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd, buffer, len);

    close(fd);
    return(0);
}

static int GPIODirection(int pin, int dir)//配置gpio方向
{
    static const char dir_str[]  = "in\0out";
    char path[DIRECTION_MAX];
    int fd;

    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "failed to open gpio direction for writing!\n");
        return(-1);
    }

    if (write(fd, &dir_str[dir == IN ? 0 : 3], dir == IN ? 2 : 3) < 0) {
        fprintf(stderr, "failed to set direction!\n");
        return(-1);
    }

    close(fd);
    return(0);
}

static int GPIORead(int pin)//读取gpio值
{
    char path[DIRECTION_MAX];
    char value_str[3];
    int fd;

    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "failed to open gpio value for reading!\n");
        return(-1);
    }

    if (read(fd, value_str, 3) < 0) {
        fprintf(stderr, "failed to read value!\n");
        return(-1);
    }

    close(fd);
    return(atoi(value_str));
}

static int GPIOWrite(int pin, int value)//写值到特定gpio
{
    static const char s_values_str[] = "01";
    char path[DIRECTION_MAX];
    int fd;

    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "failed to open gpio value for writing!\n");
        return(-1);
    }

    if (write(fd, &s_values_str[value == LOW ? 0 : 1], 1) < 0) {
        fprintf(stderr, "failed to write value!\n");
        return(-1);
    }

    close(fd);
    return(0);
}

int main(int argc, char *argv[])
{ 
		int leds_pin[4]={23,27,22,5};//定义一个存放led对应gpio引脚号的整形数组
		int i;
		for(i=0;i<4;i++)
		{
			GPIOExport(leds_pin[i]);//暴露引脚列表里的gpio
    	GPIODirection(leds_pin[i], OUT);//设置引脚为输出模式
		}
		while(1)
		{
			for(i=0;i<4;i++)
			{
				 GPIOWrite(leds_pin[i],LOW);
				 usleep(200 * 1000);
				 GPIOWrite(leds_pin[i],HIGH);
				 usleep(200 * 1000);
			}	
		}
		for(i=0;i<4;i++)
		{
			GPIOUnexport(leds_pin[i]);//隐藏引脚列表里的gpio
		}
    return(0);
}
```
## 玩
> 当我们修改了代码后想运行时，必须将其编译成可执行文件，在此我们需要用到gcc工具，树莓派默认已安装好，若无，则百度相关教程安装好<br>
> 此版本提供了Makefile文件，Makefile文件描述了整个工程的编译、链接等规则，用户只需要运行make即可按照程序员所写好的规则编译程序。
> 此Makefile文件内容如下
```C
led:led.c
	gcc led.c -o led 
clean:
	rm led
```
> 运行`make`即可编译
> 相当于在终端里手动输入 `gcc -o led led.c` 编译
> 若无错误，则将会生成目标文件名的可执行文件，如有错误，请根据编译器提示排错。<br>
> 执行验证,由于是sysfs，请用root权限打开
> `sudo ./目标文件名`
> 例<br>
> `./led`
> 按了回车后，你将会发现彩虹板上的LED1和LED2在快速闪烁<br>
> 按下`Ctrl+C`结束程序<br>
## 扩展
> 用户可以扩展使用自己的的LED进行亮灭，只需把对应跳帽拔掉，接上排线即可。请注意使用同一个电源（共地）
> <img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/led_BoardRev2.0/schematic/led_jumper.png" width=50% height=50%/><br>
