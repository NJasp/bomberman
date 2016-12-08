#include "Levels.h"
#include "../MSD_shield/mSD_shield.h"

void init_Level(uint8_t grid[16][12], char* level, uint8_t* player1_x, uint8_t* player1_y, uint8_t* player1_x_old, uint8_t* player1_y_old)
{
	if (level == "test") {
		*player1_x = 1;
		*player1_y = 1;
		*player1_x_old = 1;
		*player1_y_old = 1;
		int j = 1;
		init_OutsideWalls(grid);
		grid[3][j] = 0;
		grid[4][j] = 0;
		grid[5][j] = 0;
		grid[6][j] = 0;
		grid[7][j] = 0;
		grid[8][j] = 0;
		grid[9][j] = 0;
		grid[10][j] = 0;
		grid[11][j] = 0;
		grid[12][j] = 0;
		grid[13][j] = 0;
		grid[14][j] = 0;
		j = 2;
		grid[2][j] = 0;
		grid[3][j] = 0;
		grid[4][j] = 0;
		grid[5][j] = 0;
		grid[6][j] = 0;
		grid[7][j] = 0;
		grid[8][j] = 0;
		grid[9][j] = 0;
		grid[10][j] = 0;
		grid[11][j] = 0;
		grid[12][j] = 0;
		grid[13][j] = 0;
		grid[14][j] = 0;
		j = 3;
		grid[1][j] = 0;
		grid[2][j] = 0;
		grid[3][j] = 0;
		grid[4][j] = 0;
		grid[5][j] = 0;
		grid[6][j] = 0;
		grid[7][j] = 0;
		grid[8][j] = 0;
		grid[9][j] = 0;
		grid[10][j] = 0;
		grid[11][j] = 0;
		grid[12][j] = 0;
		grid[13][j] = 0;
		grid[14][j] = 0;
		j = 4;
		grid[1][j] = 0;
		grid[2][j] = 0;
		grid[3][j] = 0;
		grid[4][j] = 0;
		grid[5][j] = 0;
		grid[6][j] = 0;
		grid[7][j] = 0;
		grid[8][j] = 0;
		grid[9][j] = 0;
		grid[10][j] = 0;
		grid[11][j] = 0;
		grid[12][j] = 0;
		grid[13][j] = 0;
		grid[14][j] = 0;
		j = 5;
		grid[1][j] = 0;
		grid[2][j] = 0;
		grid[3][j] = 0;
		grid[4][j] = 0;
		grid[5][j] = 0;
		grid[6][j] = 2;
		grid[7][j] = 1;
		grid[8][j] = 1;
		grid[9][j] = 2;
		grid[10][j] = 0;
		grid[11][j] = 0;
		grid[12][j] = 0;
		grid[13][j] = 0;
		grid[14][j] = 0;
		j = 6;
		grid[1][j] = 0;
		grid[2][j] = 0;
		grid[3][j] = 0;
		grid[4][j] = 0;
		grid[5][j] = 0;
		grid[6][j] = 2;
		grid[7][j] = 1;
		grid[8][j] = 1;
		grid[9][j] = 2;
		grid[10][j] = 0;
		grid[11][j] = 0;
		grid[12][j] = 0;
		grid[13][j] = 0;
		grid[14][j] = 0;
		j = 7;
		grid[1][j] = 0;
		grid[2][j] = 0;
		grid[3][j] = 0;
		grid[4][j] = 0;
		grid[5][j] = 0;
		grid[6][j] = 0;
		grid[7][j] = 0;
		grid[8][j] = 0;
		grid[9][j] = 0;
		grid[10][j] = 0;
		grid[11][j] = 0;
		grid[12][j] = 0;
		grid[13][j] = 0;
		grid[14][j] = 0;
		j = 8;
		grid[1][j] = 0;
		grid[2][j] = 0;
		grid[3][j] = 0;
		grid[4][j] = 0;
		grid[5][j] = 0;
		grid[6][j] = 0;
		grid[7][j] = 0;
		grid[8][j] = 0;
		grid[9][j] = 0;
		grid[10][j] = 0;
		grid[11][j] = 0;
		grid[12][j] = 0;
		grid[13][j] = 0;
		grid[14][j] = 0;
		j = 9;
		grid[1][j] = 0;
		grid[2][j] = 0;
		grid[3][j] = 0;
		grid[4][j] = 0;
		grid[5][j] = 0;
		grid[6][j] = 0;
		grid[7][j] = 0;
		grid[8][j] = 0;
		grid[9][j] = 0;
		grid[10][j] = 0;
		grid[11][j] = 0;
		grid[12][j] = 0;
		grid[13][j] = 0;
		grid[14][j] = 0;
		j = 10;
		grid[1][j] = 0;
		grid[2][j] = 0;
		grid[3][j] = 0;
		grid[4][j] = 0;
		grid[5][j] = 0;
		grid[6][j] = 0;
		grid[7][j] = 0;
		grid[8][j] = 0;
		grid[9][j] = 0;
		grid[10][j] = 0;
		grid[11][j] = 0;
		grid[12][j] = 0;
		grid[13][j] = 0;
		grid[14][j] = 0;
	}
	if (level == "level-1") {
		*player1_x = 1;
		*player1_y = 1;
		*player1_x_old = 1;
		*player1_y_old = 1;
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
	if (level == "level-2") {
		*player1_x = 7;
		*player1_y = 2;
		*player1_x_old = 7;
		*player1_y_old = 2;
		int j = 1;
		init_OutsideWalls(grid);
		grid[1][j] = 2;
		grid[2][j] = 2;
		grid[3][j] = 2;
		grid[4][j] = 2;
		grid[5][j] = 2;
		grid[6][j] = 2;
		grid[7][j] = 0;
		grid[8][j] = 0;
		grid[9][j] = 2;
		grid[10][j] = 2;
		grid[11][j] = 2;
		grid[12][j] = 2;
		grid[13][j] = 2;
		grid[14][j] = 2;
		j = 2;
		grid[1][j] = 2;
		grid[2][j] = 1;
		grid[3][j] = 2;
		grid[4][j] = 1;
		grid[5][j] = 2;
		grid[6][j] = 1;
		grid[7][j] = 0;
		grid[8][j] = 0;
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
		grid[7][j] = 0;
		grid[8][j] = 0;
		grid[9][j] = 1;
		grid[10][j] = 2;
		grid[11][j] = 1;
		grid[12][j] = 2;
		grid[13][j] = 1;
		grid[14][j] = 2;
		j = 10;
		grid[1][j] = 2;
		grid[2][j] = 2;
		grid[3][j] = 2;
		grid[4][j] = 2;
		grid[5][j] = 2;
		grid[6][j] = 2;
		grid[7][j] = 0;
		grid[8][j] = 0;
		grid[9][j] = 2;
		grid[10][j] = 2;
		grid[11][j] = 2;
		grid[12][j] = 2;
		grid[13][j] = 2;
		grid[14][j] = 2;
	}
	if (level == "level-3") {
		*player1_x = 1;
		*player1_y = 1;
		*player1_x_old = 1;
		*player1_y_old = 1;
		int j = 1;
		init_OutsideWalls(grid);
		grid[1][j] = 0;
		grid[2][j] = 0;
		grid[3][j] = 1;
		grid[4][j] = 1;
		grid[5][j] = 1;
		grid[6][j] = 1;
		grid[7][j] = 2;
		grid[8][j] = 2;
		grid[9][j] = 2;
		grid[10][j] = 2;
		grid[11][j] = 1;
		grid[12][j] = 2;
		grid[13][j] = 2;
		grid[14][j] = 2;
		j = 2;
		grid[1][j] = 0;
		grid[2][j] = 1;
		grid[3][j] = 1;
		grid[4][j] = 1;
		grid[5][j] = 1;
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
		grid[2][j] = 1;
		grid[3][j] = 2;
		grid[4][j] = 2;
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
		j = 6;
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
		grid[2][j] = 1;
		grid[3][j] = 2;
		grid[4][j] = 1;
		grid[5][j] = 2;
		grid[6][j] = 1;
		grid[7][j] = 2;
		grid[8][j] = 2;
		grid[9][j] = 1;
		grid[10][j] = 2;
		grid[11][j] = 2;
		grid[12][j] = 2;
		grid[13][j] = 1;
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
		grid[10][j] = 1;
		grid[11][j] = 1;
		grid[12][j] = 1;
		grid[13][j] = 1;
		grid[14][j] = 0;
		j = 10;
		grid[1][j] = 2;
		grid[2][j] = 2;
		grid[3][j] = 2;
		grid[4][j] = 1;
		grid[5][j] = 2;
		grid[6][j] = 2;
		grid[7][j] = 2;
		grid[8][j] = 2;
		grid[9][j] = 1;
		grid[10][j] = 1;
		grid[11][j] = 1;
		grid[12][j] = 1;
		grid[13][j] = 0;
		grid[14][j] = 0;
	}
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
				screen.fillRect(collumn * 20, row * 20, 20, 20, RGB(0, 0, 0));
				//draw_Pictures(wall_Type, collumn * 20, row * 20, screen);
			}
			else {
				if (grid[collumn][row] == 2) {
					screen.fillRect(collumn * 20, row * 20, 20, 20, RGB(222, 184, 135));
					//draw_Pictures(crate_Type, collumn * 20, row * 20, screen);
				}
			}
		}
	}
}