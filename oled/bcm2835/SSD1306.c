#include <bcm2835.h>
#include <stdio.h>
#include "SSD1306.h"
#define vccstate SSD1306_SWITCHCAPVCC
#define width 128
#define height 64
#define pages 8

#define RST 25 
#define DC  24
char buffer[1024];

void command(char cmd){
    bcm2835_gpio_write(DC,LOW);
    bcm2835_spi_transfer(cmd);
}

void SSD1306_begin()
{
	bcm2835_gpio_fsel(RST,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(DC,BCM2835_GPIO_FSEL_OUTP);

	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);     //The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                  //The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);  //The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                     //The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);     //the default

	bcm2835_gpio_write(RST,HIGH);
	bcm2835_delay(10);
	bcm2835_gpio_write(RST,LOW);
	bcm2835_delay(10);
	bcm2835_gpio_write(RST,HIGH);

	command(SSD1306_DISPLAYOFF);
    command(SSD1306_SETDISPLAYCLOCKDIV);
    command(0x80);                              // the suggested ratio 0x80

    command(SSD1306_SETMULTIPLEX);
    command(0x3F);
    command(SSD1306_SETDISPLAYOFFSET);
    command(0x0);                               // no offset
	command(SSD1306_SETSTARTLINE | 0x0);        // line #0
	command(SSD1306_CHARGEPUMP);
    command((vccstate == SSD1306_EXTERNALVCC) ? 0x10 : 0x14);

    command(SSD1306_MEMORYMODE);
    command(0x00);                              // 0x0 act like ks0108

    command(SSD1306_SEGREMAP | 0x1);
	command(SSD1306_COMSCANDEC);
	command(SSD1306_SETCOMPINS);
    command(0x12);           // TODO - calculate based on _rawHieght ?
	command(SSD1306_SETCONTRAST);
    command((vccstate == SSD1306_EXTERNALVCC) ? 0x9F : 0xCF);
    command(SSD1306_SETPRECHARGE);
    command((vccstate == SSD1306_EXTERNALVCC) ? 0x22 : 0xF1);
    command(SSD1306_SETVCOMDETECT);
    command(0x40);
    command(SSD1306_DISPLAYALLON_RESUME);
    command(SSD1306_NORMALDISPLAY);
    command(SSD1306_DISPLAYON);
}
void SSD1306_clear()
{
	int i;
	for(i = 0;i<sizeof(buffer);i++)
	{
		buffer[i] = 0;
	}
}
void SSD1306_pixel(int x,int y,char color)
{
    if(x > width || y > height)return ;
    if(color)
        buffer[x+(y/8)*width] |= 1<<(y%8);
    else
        buffer[x+(y/8)*width] &= ~(1<<(y%8));
}
void SSD1306_char1616(uint8_t x, uint8_t y, uint8_t chChar)
{
	uint8_t i, j;
	uint8_t chTemp = 0, y0 = y, chMode = 0;

	for (i = 0; i < 32; i ++) {
		chTemp = Font1612[chChar - 0x30][i];
		for (j = 0; j < 8; j ++) {
			chMode = chTemp & 0x80? 1 : 0; 
			SSD1306_pixel(x, y, chMode);
			chTemp <<= 1;
			y ++;
			if ((y - y0) == 16) {
				y = y0;
				x ++;
				break;
			}
		}
	}
}

void SSD1306_char3216(uint8_t x, uint8_t y, uint8_t chChar)
{
	uint8_t i, j;
	uint8_t chTemp = 0, y0 = y, chMode = 0;

	for (i = 0; i < 64; i ++) {
		chTemp = Font3216_Mono[chChar - 0x30][i];
		for (j = 0; j < 8; j ++) {
			chMode = chTemp & 0x80? 1 : 0; 
			SSD1306_pixel(x, y, chMode);
			chTemp <<= 1;
			y ++;
			if ((y - y0) == 32) {
				y = y0;
				x ++;
				break;
			}
		}
	}
}
void SSD1306_char(unsigned char x,unsigned char y,char acsii,char size,char mode)
{
	unsigned char i,j,y0=y;
	char temp;
	unsigned char ch = acsii - ' ';
	for(i = 0;i<size;i++)
	{
		if(size == 12)
		{
			if(mode)temp=Font1206[ch][i];
			else temp = ~Font1206[ch][i];
		}
		else 
		{			
			if(mode)temp=Font1608[ch][i];
			else temp = ~Font1608[ch][i];
		}
		for(j =0;j<8;j++)
		{
			if(temp & 0x80) SSD1306_pixel(x,y,1);
			else SSD1306_pixel(x,y,0);
			temp <<=1;
			y++;
			if((y-y0)==size)
			{
				y = y0;
				x ++;
				break;
			}
		}
	}
}
void SSD1306_string(uint8_t x, uint8_t y, const char *pString, uint8_t Size, uint8_t Mode)
{
    while (*pString != '\0') {       
        if (x > (width - Size / 2)) {
			x = 0;
			y += Size;
			if (y > (height - Size)) {
				y = x = 0;
			}
		}
		
        SSD1306_char(x, y, *pString, Size, Mode);
        x += Size / 2;
        pString ++;
    }
}

void SSD1306_bitmap(unsigned char x,unsigned char y,const unsigned char *pBmp,char chWidth,char chHeight)
{
	unsigned char i,j,byteWidth = (chWidth + 7)/8;
	for(j = 0;j < chHeight;j++){
		for(i = 0;i <chWidth;i ++){
			if(*(pBmp +j*byteWidth+i/8) & (128 >> (i & 7))){
				SSD1306_pixel(x+i,y+j,1);
			}
		}
	}		
}

void SSD1306_display()
{
	command(SSD1306_COLUMNADDR);
	command(0);         //cloumn start address
	command(width -1); //cloumn end address
	command(SSD1306_PAGEADDR);
	command(0);         //page atart address
	command(pages -1); //page end address
	bcm2835_gpio_write(DC,HIGH);
	bcm2835_spi_transfern(buffer,sizeof(buffer));
}
