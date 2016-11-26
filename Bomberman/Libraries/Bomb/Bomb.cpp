#include "Bomb.h"

void draw_Explosion(MI0283QT9 screen, uint8_t bombradius, uint8_t grid[16][12])
{
	uint8_t row, collumn, icollumn, irow;
	for (row = 0; row < 12; row++) {
		for (collumn = 0; collumn < 16; collumn++) {
			if (grid[collumn][row] == 3) {
				grid[collumn][row] = 9;
				screen.fillRect(((collumn * 20) + 4), ((row * 20) + 4), 14, 14, RGB(255, 127, 0));
				icollumn = collumn;
				irow = row;
				for (collumn; collumn < (icollumn + bombradius); collumn++) {
					if ((grid[collumn + 1][row] == 0) || (grid[collumn + 1][row] == 2) || (grid[collumn + 1][row] == 7) || (grid[collumn + 1][row] == 8) || (grid[collumn + 1][row] == 9)) {
						grid[collumn + 1][row] = 9;
						screen.fillRect((((collumn + 1) * 20) + 4), ((row * 20) + 4), 14, 14, RGB(255, 127, 0));
					}
				}
				for (collumn; collumn > (icollumn - bombradius); collumn--) {
					if ((grid[collumn - 1][row] == 0) || (grid[collumn - 1][row] == 2) || (grid[collumn - 1][row] == 7) || (grid[collumn - 1][row] == 8) || (grid[collumn - 1][row] == 9)) {
						grid[collumn - 1][row] = 9;
						screen.fillRect((((collumn - 1) * 20) + 4), ((row * 20) + 4), 14, 14, RGB(255, 127, 0));
					}
				}
				collumn = icollumn;
				row = irow;
				for (row; row < (irow + bombradius); row++) {
					if ((grid[collumn][row + 1] == 0) || (grid[collumn][row + 1] == 2) || (grid[collumn][row + 1] == 7) || (grid[collumn][row + 1] == 8) || (grid[collumn][row + 1] == 9)) {
						grid[collumn][row + 1] = 9;
						screen.fillRect(((collumn * 20) + 4), (((row + 1) * 20) + 4), 14, 14, RGB(255, 127, 0));
					}
				}
				for (row; row > (irow - bombradius); row--) {
					if ((grid[collumn][row - 1] == 0) || (grid[collumn][row - 1] == 2) || (grid[collumn][row - 1] == 7) || (grid[collumn][row - 1] == 8) || (grid[collumn][row - 1] == 9)) {
						grid[collumn][row - 1] = 9;
						screen.fillRect(((collumn * 20) + 4), (((row - 1) * 20) + 4), 14, 14, RGB(255, 127, 0));
					}
				}
			}
		}
	}
}

void clear_Explosion(MI0283QT9 screen, uint8_t bombradius, uint8_t grid[16][12])
{
	uint8_t row, collumn, icollumn, irow;
	for (row = 0; row < 12; row++) {
		for (collumn = 0; collumn < 16; collumn++) {
			if (grid[collumn][row] == 7) {
				grid[collumn][row] = 0;
				screen.fillRect(collumn * 20, row * 20, 20, 20, RGB(255, 255, 255));
			}
		}
	}
}
