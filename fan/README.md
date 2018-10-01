# MrzhangF1ghterStudio 彩虹扩展板系列
# 温控风扇教程 （wiringPi版本）
## 玩转代码（温控）
> ### 在我们的彩虹扩展板上 我们的风扇接到了树莓派唯一的一个原生PWM引脚，这样的好处是，我们不用软件模拟pwm，而是用硬件pwm，不耗费宝贵cpu资源
> 风扇| GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |FAN1|BCM18|pin1 |12   |

### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoardRev2.0.pdf)  
<img src="https://img.alicdn.com/imgextra/i2/1887229091/O1CN012H1j5v3ekuvLJA2_!!1887229091.png" width=50% height=50%/><br>  

> 如果你收到的是2p引脚的风扇，请按能看到金属触点一面朝上，靠左插入。  
<img src="https://img.alicdn.com/imgextra/i2/1887229091/O1CN012H1j61jbzlF53r5_!!1887229091.png" width=50% height=50%/><br>  
> 请将风扇底部的散热垫保护膜撕开，然后将风扇对准CPU中心贴上去即可  请清洁后进行，
> 我们的风扇具有两个控制模式，一个是全速模式，一个是程序温控模式，可以通过跳帽选择，默认跳帽为程控模式，若需全速模式，则将跳帽接到FAN_CTL的右边两个排针  
<img src="https://img.alicdn.com/imgextra/i3/1887229091/O1CN012H1j5zNNX1UdwQM_!!1887229091.png" width=50% height=50%/><br>  
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
### 玩
> 当我们修改了代码后想运行时，必须将其编译成可执行文件，在此我们需要用到gcc工具，树莓派默认已安装好，若无，则百度相关教程安装好<br>
> 编译指令如下 `gcc -o 目标文件名 源文件名` -o的意思为输出可执行文件<br>
> 例:`gcc -o fan_ctl fan_ctl.c -lwiringPi` <br>
> 若无错误，则将会生成目标文件名的可执行文件，如有错误，请根据编译器提示排错。<br>
> 执行验证
> `./目标文件名`
> 例<br>
> `sudo ./fan_ctl &` 由于pwm需要用到超级用户权限，请用root权限运行
> 按了回车后，风扇将根据CPU温度而调整转速
> 按下`Ctrl+C`结束程序<br>
### 玩·超频
> 在风扇的力压下，不超频正常情况下能在40度左右盘旋，风扇以非常低的速度运转，在满负荷1.4Ghz情况下，温度不超过55度。相比不加风扇满负荷在70多度而言，降温接近20度！
> 不带温控风扇空闲状态：
> <img src="https://img.alicdn.com/imgextra/i4/1887229091/O1CN012H1j64F7FBAqcAS_!!1887229091.png" width=50% height=50%/><br>  
> 不带温控风扇满负荷状态：
> <img src="https://img.alicdn.com/imgextra/i4/1887229091/O1CN012H1j63af5lwbOhg_!!1887229091.png" width=50% height=50%/><br>  
> 温控风扇下空闲状态:
> <img src="https://img.alicdn.com/imgextra/i2/1887229091/O1CN012H1j61P9hNaXkm0_!!1887229091.png" width=50% height=50%/><br>  
温控风扇下满负荷状态:
> <img src="https://img.alicdn.com/imgextra/i2/1887229091/O1CN012H1j5v3ektd8yDb_!!1887229091.png" width=50% height=50%/><br> 
#### 超频
> 树莓派超频需谨慎！每个板子的素质有所不同，请自行调整
> 我们采用sysbench来进行跑分测试，请先`apt-get install sysbench`安装工具
> 运行`sysbench --test=cpu --cpu-max-prime=20000 --num-threads=4 run`进行性能测试
> 此时我们可以通过查询/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq文件获得当前CPU频率
> `sudo cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq`
> 其实也可以执行fan_ctl就可以查看当前评论了，在代码中我也将当前频率打出来了
> 我的3B+在默认评率下跑分在 103左右(在)
> <img src="https://img.alicdn.com/imgextra/i2/1887229091/O1CN012H1j62NUdLcHAD4_!!1887229091.png" width=50% height=50%/><br>

> 我们通过修改/boot/config.txt文件即可超频，树莓派3B+最高可以超到1.6Ghz，树莓派3B最高可以超到1.4Ghz再高也上不去了。其中术语如下,超频方案参数在文末。
```
arm_freq=CPU频率
gpu_freq=GPU频率
core_freq=核心频率
sdram_freq=内存频率
sdram_schmoo=0x02000020
over_voltage=CPU电压步进值
sdram_over_voltage=内存电压步进值
```
> 在1.6Ghz最高频率下，跑分跑到了93秒左右的成绩（越短越好）,提升约10秒的时间，在温控风扇的力压下，仍不超过60度
> <img src="https://img.alicdn.com/imgextra/i2/1887229091/O1CN012H1j5zNO4FWrZXH_!!1887229091.png" width=50% height=50%/><br> 
> 我们在config.txt的末尾添加我们的超频参数，重启即可生效，下面是提供的超频方案，请按需选择(树莓派3B+)树莓派3B最高频率不要超过1450，其他相同
> 1.45Ghz带GPU超频方案
```
arm_freq=1500
gpu_freq=500
core_freq=500
sdram_freq=500
sdram_schmoo=0x02000020
over_voltage=2
sdram_over_voltage=2
```
> 1.5Ghz不带GPU超频方案
```
arm_freq=1500
over_voltage=6
```
> 1.5Ghz带GPU超频方案
```
arm_freq=1500
gpu_freq=500
core_freq=500
sdram_freq=500
sdram_schmoo=0x02000020
over_voltage=6
sdram_over_voltage=2
```
> 1.57Ghz带GPU超频方案
```
arm_freq=1575
gpu_freq=500
core_freq=500
sdram_freq=500
sdram_schmoo=0x02000020
over_voltage=6
sdram_over_voltage=2
```
> 1.6Ghz带GPU超频方案
```
arm_freq=1600
gpu_freq=500
core_freq=500
sdram_freq=500
sdram_schmoo=0x02000020
over_voltage=6
sdram_over_voltage=2
```
### 开机启动
> 开机启动很简单 只需要编辑rc.local文件,在exit 0之前添加执行程序路径即可 `/home/pi/RainbowCandyBoard/Fan/wiringPi/fan_ctl` //若程序不是可执行权限，请chmod 777 fan_ctl

