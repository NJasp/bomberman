#include "LCD.h"

void init_LCD(MI0283QT9 screen)
{										//INITIALIZE (SETUP)
	screen.begin(8);
	screen.fillScreen(RGB(255, 255, 255));
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

void draw_Walls_Crates(MI0283QT9 screen, uint8_t grid[16][12])
{
	uint8_t row, collumn;
	//	draw stuff in grid
	for (row = 0; row < 12; row++) {
		for (collumn = 0; collumn < 16; collumn++) {
			if (grid[collumn][row] == 1) {
				screen.fillRect(collumn*20, row*20, 20, 20, RGB(0, 0, 0));
			}
			else {
				if (grid[collumn][row] == 2) {
					screen.fillRect(collumn*20, row*20, 20, 20, RGB(222, 184, 135));
				}
			}
		}
	}
}