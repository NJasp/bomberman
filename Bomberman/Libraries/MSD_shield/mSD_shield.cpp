#include "mSD_shield.h"

void init_SDcart(MI0283QT9 screen)
{
	int x;

	screen.begin();
	screen.fillScreen(Background);

	x = screen.drawText(5, 5, "Init SD-Card...", RGB(0, 0, 0), Background, 1);
	if (!SD.begin(4)) //cs-pin=4
	{
		screen.drawText(x, 5, "failed", RGB(0, 0, 0), Background, 1);
		while (1);
	}
}

void draw_Pictures(char *file, int16_t x, int16_t y, MI0283QT9 screen)
{
	int i;
		
	File myFile;
	uint8_t buf[40]; //read buf (min. size = sizeof(BMP_DIPHeader))
	BMP_Header *bmp_hd;
	BMP_DIPHeader *bmp_dip;
	int16_t width, height, w, h;
	uint8_t pad, result = 0;

	//open file
	myFile = SD.open(file);

	if (myFile)
	{
		result = 1;
		//BMP Header
		myFile.read(&buf, sizeof(BMP_Header));
		bmp_hd = (BMP_Header*)&buf[0];
		if ((bmp_hd->magic[0] == 'B') && (bmp_hd->magic[1] == 'M') && (bmp_hd->offset == 54))
		{
			result = 2;
			//BMP DIP-Header
			myFile.read(&buf, sizeof(BMP_DIPHeader));
			bmp_dip = (BMP_DIPHeader*)&buf[0];
			if ((bmp_dip->size == sizeof(BMP_DIPHeader)) && (bmp_dip->bitspp == 24) && (bmp_dip->compress == 0))
			{
				result = 3;
				//BMP Data (1. pixel = bottom left)
				width = bmp_dip->width;
				height = bmp_dip->height;
				pad = width % 4; //padding (line is multiply of 4)
				if ((x + width) <= screen.getWidth() && (y + height) <= screen.getHeight())
				{
					result = 4;
					screen.setArea(x, y, x + width - 1, y + height - 1);
					for (h = (y + height - 1); h >= y; h--) //for every line
					{
						for (w = x; w < (x + width); w++) //for every pixel in line
						{
							myFile.read(&buf, 3);
							screen.drawPixel(w, h, RGB(buf[2], buf[1], buf[0]));
						}
						if (pad)
						{
							myFile.read(&buf, pad);
						}
					}
				}
				else
				{
					screen.drawText(x, y, "Pic out of screen!", RGB(0, 0, 0), Background, 1);
				}
			}
		}

		myFile.close();
	}
}