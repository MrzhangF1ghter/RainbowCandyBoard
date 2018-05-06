# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# 1-Wire教程 （DS18B20温度传感器 sysfs版本）

## 玩转代码
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
	char path[50] = "/sys/bus/w1/devices/";
	char rom[20];
	char buf[100];
	DIR *dirp;
	struct dirent *direntp;
	int fd =-1;
	char *temp;
	float value;

	system("sudo modprobe w1-gpio");
	system("sudo modprobe w1-therm");
	if((dirp = opendir(path)) == NULL)
	{
		printf("opendir error\n");
		return 1;
	}

	while((direntp = readdir(dirp)) != NULL)
	{
		if(strstr(direntp->d_name,"28-0"))
		{
			strcpy(rom,direntp->d_name);
			printf(" rom: %s\n",rom);
		}
	}
	closedir(dirp);
	
	strcat(path,rom);
	strcat(path,"/w1_slave");
	while(1)
	{
		if((fd = open(path,O_RDONLY)) < 0)
		{
			printf("open error\n");
			return 1;
		}
	
		if(read(fd,buf,sizeof(buf)) < 0)
		{
			printf("read error\n");
			return 1;
		}	
		
		temp = strchr(buf,'t');
		sscanf(temp,"t=%s",temp);
		value = atof(temp)/1000;
		printf(" temp : %3.3f °C\n",value);

		sleep(1);
	}
	return 0;
}

```
## 玩
> 当我们修改了代码后想运行时，必须将其编译成可执行文件，在此我们需要用到gcc工具，树莓派默认已安装好，若无，则百度相关教程安装好<br>
> 此版本提供了Makefile文件，Makefile文件描述了整个工程的编译、链接等规则，用户只需要运行make即可按照程序员所写好的规则编译程序。
> 此Makefile文件内容如下
```C
ds18b20:ds18b20.c
	gcc -Wall ds18b20.c -o ds18b20
clean:
	rm ds18b20
```
> 运行`make`即可编译
> 相当于在终端里手动输入 gcc -o ds18b20 ds18b20.c 
> 若无错误，则将会生成目标文件名的可执行文件，如有错误，请根据编译器提示排错。<br>
> 执行验证,由于是sysfs，请用root权限打开
> `sudo ./目标文件名`
> 例<br>
> `sudo ./ds18b20`
> 按了回车后，终端循环打印当前温度<br>
> 按下`Ctrl+C`结束程序<br>
