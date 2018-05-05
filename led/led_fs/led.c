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
		int leds_pin[2]={17,27};//定义一个存放led对应gpio引脚号的整形数组
		int i;
		for(i=0;i<2;i++)
		{
			GPIOExport(leds_pin[i]);//暴露引脚列表里的gpio
    	GPIODirection(leds_pin[i], OUT);//设置引脚为输出模式
		}
		while(1)
		{
			for(i=0;i<2;i++)
			{
				 GPIOWrite(leds_pin[i],LOW);
				 usleep(200 * 1000);
				 GPIOWrite(leds_pin[i],HIGH);
				 usleep(200 * 1000);
			}	
		}
		for(i=0;i<2;i++)
		{
			GPIOUnexport(leds_pin[i]);//隐藏引脚列表里的gpio
		}
    return(0);
}

