/* ds18b20.c
 * you can build this with something like:
 * gcc -Wall ds18b20.c -o ds18b20
 * sudo ./ds18b20
*/
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
		if(strstr(direntp->d_name,"28-00000"))
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
