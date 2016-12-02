#include "Levels.h"
#include "../MSD_shield/mSD_shield.h"

void init_Testlevel(uint8_t grid[16][12])
{
	init_OutsideWalls(grid);
	grid[7][4] = 2;
	grid[8][5] = 1;
}

void init_Level1(uint8_t grid[16][12])
{
	int j = 1;
	init_OutsideWalls(grid);
	grid[3][j] = 2;
	grid[4][j] = 2;
	grid[5][j] = 2;
	grid[6][j] = 2;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 2;
	grid[10][j] = 2;
	grid[11][j] = 2;
	grid[12][j] = 2;
	grid[13][j] = 2;
	grid[14][j] = 2;
	j = 2;
	grid[2][j] = 1;
	grid[3][j] = 2;
	grid[4][j] = 1;
	grid[5][j] = 2;
	grid[6][j] = 1;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 1;
	grid[10][j] = 2;
	grid[11][j] = 1;
	grid[12][j] = 2;
	grid[13][j] = 1;
	grid[14][j] = 2;
	j = 3;
	grid[1][j] = 2;
	grid[2][j] = 2;
	grid[3][j] = 0;
	grid[4][j] = 2;
	grid[5][j] = 0;
	grid[6][j] = 2;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 2;
	grid[10][j] = 0;
	grid[11][j] = 2;
	grid[12][j] = 0;
	grid[13][j] = 2;
	grid[14][j] = 2;
	j = 4;
	grid[1][j] = 2;
	grid[2][j] = 1;
	grid[3][j] = 2;
	grid[4][j] = 1;
	grid[5][j] = 2;
	grid[6][j] = 1;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 1;
	grid[10][j] = 2;
	grid[11][j] = 1;
	grid[12][j] = 2;
	grid[13][j] = 1;
	grid[14][j] = 2;
	j = 5;
	grid[1][j] = 2;
	grid[2][j] = 2;
	grid[3][j] = 2;
	grid[4][j] = 2;
	grid[5][j] = 2;
	grid[6][j] = 2;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 2;
	grid[10][j] = 2;
	grid[11][j] = 2;
	grid[12][j] = 2;
	grid[13][j] = 2;
	grid[14][j] = 2;
	j = 6;
	grid[1][j] = 2;
	grid[2][j] = 2;
	grid[3][j] = 2;
	grid[4][j] = 2;
	grid[5][j] = 2;
	grid[6][j] = 2;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 2;
	grid[10][j] = 2;
	grid[11][j] = 2;
	grid[12][j] = 2;
	grid[13][j] = 2;
	grid[14][j] = 2;
	j = 7;
	grid[1][j] = 2;
	grid[2][j] = 1;
	grid[3][j] = 2;
	grid[4][j] = 1;
	grid[5][j] = 2;
	grid[6][j] = 1;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 1;
	grid[10][j] = 2;
	grid[11][j] = 1;
	grid[12][j] = 2;
	grid[13][j] = 1;
	grid[14][j] = 2;
	j = 8;
	grid[1][j] = 2;
	grid[2][j] = 2;
	grid[3][j] = 0;
	grid[4][j] = 2;
	grid[5][j] = 0;
	grid[6][j] = 2;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 2;
	grid[10][j] = 0;
	grid[11][j] = 2;
	grid[12][j] = 0;
	grid[13][j] = 2;
	grid[14][j] = 2;
	j = 9;
	grid[1][j] = 2;
	grid[2][j] = 1;
	grid[3][j] = 2;
	grid[4][j] = 1;
	grid[5][j] = 2;
	grid[6][j] = 1;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 1;
	grid[10][j] = 2;
	grid[11][j] = 1;
	grid[12][j] = 2;
	grid[13][j] = 1;
	grid[14][j] = 0;
	j = 10;
	grid[1][j] = 2;
	grid[2][j] = 2;
	grid[3][j] = 2;
	grid[4][j] = 2;
	grid[5][j] = 2;
	grid[6][j] = 2;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 2;
	grid[10][j] = 2;
	grid[11][j] = 2;
	grid[12][j] = 2;
	grid[13][j] = 0;
	grid[14][j] = 0;
}

void init_Level2(uint8_t grid[16][12])
{
	int j = 1;
	init_OutsideWalls(grid);
	grid[3][j] = 2;
	grid[4][j] = 2;
	grid[5][j] = 2;
	grid[6][j] = 2;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 2;
	grid[10][j] = 2;
	grid[11][j] = 2;
	grid[12][j] = 2;
	grid[13][j] = 2;
	grid[14][j] = 2;
	j = 2;
	grid[2][j] = 1;
	grid[3][j] = 2;
	grid[4][j] = 1;
	grid[5][j] = 2;
	grid[6][j] = 1;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 1;
	grid[10][j] = 2;
	grid[11][j] = 1;
	grid[12][j] = 2;
	grid[13][j] = 1;
	grid[14][j] = 2;
	j = 3;
	grid[1][j] = 2;
	grid[2][j] = 2;
	grid[3][j] = 0;
	grid[4][j] = 2;
	grid[5][j] = 0;
	grid[6][j] = 2;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 2;
	grid[10][j] = 0;
	grid[11][j] = 2;
	grid[12][j] = 0;
	grid[13][j] = 2;
	grid[14][j] = 2;
	j = 4;
	grid[1][j] = 2;
	grid[2][j] = 1;
	grid[3][j] = 2;
	grid[4][j] = 1;
	grid[5][j] = 2;
	grid[6][j] = 1;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 1;
	grid[10][j] = 2;
	grid[11][j] = 1;
	grid[12][j] = 2;
	grid[13][j] = 1;
	grid[14][j] = 2;
	j = 5;
	grid[1][j] = 2;
	grid[2][j] = 2;
	grid[3][j] = 2;
	grid[4][j] = 2;
	grid[5][j] = 2;
	grid[6][j] = 2;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 2;
	grid[10][j] = 2;
	grid[11][j] = 2;
	grid[12][j] = 2;
	grid[13][j] = 2;
	grid[14][j] = 2;
	j = 6;
	grid[1][j] = 2;
	grid[2][j] = 2;
	grid[3][j] = 2;
	grid[4][j] = 2;
	grid[5][j] = 2;
	grid[6][j] = 2;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 2;
	grid[10][j] = 2;
	grid[11][j] = 2;
	grid[12][j] = 2;
	grid[13][j] = 2;
	grid[14][j] = 2;
	j = 7;
	grid[1][j] = 2;
	grid[2][j] = 1;
	grid[3][j] = 2;
	grid[4][j] = 1;
	grid[5][j] = 2;
	grid[6][j] = 1;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 1;
	grid[10][j] = 2;
	grid[11][j] = 1;
	grid[12][j] = 2;
	grid[13][j] = 1;
	grid[14][j] = 2;
	j = 8;
	grid[1][j] = 2;
	grid[2][j] = 2;
	grid[3][j] = 0;
	grid[4][j] = 2;
	grid[5][j] = 0;
	grid[6][j] = 2;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 2;
	grid[10][j] = 0;
	grid[11][j] = 2;
	grid[12][j] = 0;
	grid[13][j] = 2;
	grid[14][j] = 2;
	j = 9;
	grid[1][j] = 2;
	grid[2][j] = 1;
	grid[3][j] = 2;
	grid[4][j] = 1;
	grid[5][j] = 2;
	grid[6][j] = 1;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 1;
	grid[10][j] = 2;
	grid[11][j] = 1;
	grid[12][j] = 2;
	grid[13][j] = 1;
	grid[14][j] = 0;
	j = 10;
	grid[1][j] = 2;
	grid[2][j] = 2;
	grid[3][j] = 2;
	grid[4][j] = 2;
	grid[5][j] = 2;
	grid[6][j] = 2;
	grid[7][j] = 2;
	grid[8][j] = 2;
	grid[9][j] = 2;
	grid[10][j] = 2;
	grid[11][j] = 2;
	grid[12][j] = 2;
	grid[13][j] = 0;
	grid[14][j] = 0;
}

void init_OutsideWalls(uint8_t grid[16][12])
{
	uint8_t collumn, row;
	for (row = 0; row < 12; row++) {
		for (collumn = 0; collumn < 16; collumn++) {
			if (row == 0 || row == 11) {
				grid[collumn][row] = 1;
			}
			else {
				grid[0][row] = 1;
				grid[15][row] = 1;
			}
		}
	}
}

void draw_Walls_Crates(MI0283QT9 screen, uint8_t grid[16][12],char *wall_Type, char *crate_Type)
{
	uint8_t row, collumn;
	//	draw stuff in grid
	for (row = 0; row < 12; row++) {
		for (collumn = 0; collumn < 16; collumn++) {
			if (grid[collumn][row] == 1) {
				//screen.fillRect(collumn * 20, row * 20, 20, 20, RGB(0, 0, 0));
				init_Pictures(wall_Type, collumn * 20, row * 20, screen);
			}
			else {
				if (grid[collumn][row] == 2) {
					//screen.fillRect(collumn * 20, row * 20, 20, 20, RGB(222, 184, 135));
					init_Pictures("crate.bmp", collumn * 20, row * 20, screen);
				}
			}
		}
	}
}