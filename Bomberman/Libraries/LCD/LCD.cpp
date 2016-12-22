#include "LCD.h"

void init_LCD(MI0283QT9 screen)
{										//INITIALIZE (SETUP)
	screen.begin(4);
	screen.fillScreen(Background);
}

void draw_Grid(MI0283QT9 screen)
{
	int i;
	for (i = 0; i <= screen.lcd_width; i += 20) {
		screen.drawLine(i, 0, i, screen.lcd_height, RGB(0, 0, 0));
	}
	for (i = 0; i <= screen.lcd_height; i += 20) {
		screen.drawLine(0, i, screen.lcd_width, i, RGB(0, 0, 0));
	}
}