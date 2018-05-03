/* key.c
 * you can build this like: 
 * gcc -Wall key.c -o key -lbcm2835
 * sudo ./key
*/
#include <bcm2835.h>
#include <stdio.h>

char KEY = 20;
unsigned char i;
int main(int argc, char **argv)
{
	if (!bcm2835_init())return 1;
	bcm2835_gpio_fsel(KEY, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(KEY, BCM2835_GPIO_PUD_UP);
	printf("Key Test Program!!!!\n");	
	while (1)
	{
		if(bcm2835_gpio_lev(KEY) == 0)
		{  
			printf ("KEY PRESS\n") ;
    		while(bcm2835_gpio_lev(KEY) == 0)
				bcm2835_delay(100);
		}
		bcm2835_delay(100);
	}
	bcm2835_close();
	return 0;
}
