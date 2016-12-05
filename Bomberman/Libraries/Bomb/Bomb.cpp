#include "Bomb.h"
#include "string.h"
#include "../MSD_shield/mSD_shield.h"

void draw_Explosion(MI0283QT9 screen, uint8_t bombradius, uint8_t grid[16][12], uint8_t* livebombs, uint8_t* score, uint8_t* killedPlayer, uint8_t player1_x, uint8_t player1_y)
{
	uint8_t row, collumn, icollumn, irow;
	for (row = 0; row < 12; row++) {
		for (collumn = 0; collumn < 16; collumn++) {
			if (grid[collumn][row] == 3) {
				if (grid[collumn][row] == grid[player1_x][player1_y]) {
					grid[collumn][row] = 6;
				}
				else {
					grid[collumn][row] = 9;
					//screen.fillRect(((collumn * 20) + 4), ((row * 20) + 4), 14, 14, RGB(255, 127, 0));
					init_Pictures("ex.bmp", (collumn * 20), (row * 20), screen);
					icollumn = collumn;
					irow = row;
					for (collumn; collumn < (icollumn + bombradius); collumn++) {
						if ((grid[player1_x][player1_y] == 7 || grid[player1_x][player1_y] == 8 || grid[player1_x][player1_y] == 9) && ((collumn == player1_x) && (row == player1_y))) {
							(*killedPlayer) == 1;
						}
						if ((grid[collumn + 1][row] == 0) || (grid[collumn + 1][row] == 7) || (grid[collumn + 1][row] == 8) || (grid[collumn + 1][row] == 9)) {
							grid[collumn + 1][row] = 9;
							//screen.fillRect((((collumn + 1) * 20) + 4), ((row * 20) + 4), 14, 14, RGB(255, 127, 0));
							init_Pictures("ex.bmp", ((collumn + 1) * 20), (row * 20), screen);
							//test
						}
						else if (grid[collumn + 1][row] == 2) {
							grid[collumn + 1][row] = 9;
							//screen.fillRect((((collumn + 1) * 20) + 4), ((row * 20) + 4), 14, 14, RGB(255, 127, 0));
							init_Pictures("ex.bmp", ((collumn + 1) * 20), (row * 20), screen);
							(*score)++;
							break;
						}
						else if (grid[collumn + 1][row] == 1) {
							break;
						}
					}
					for (collumn; collumn > (icollumn - bombradius); collumn--) {
						if ((grid[player1_x][player1_y] == 7 || grid[player1_x][player1_y] == 8 || grid[player1_x][player1_y] == 9) && ((player1_x = collumn) && (player1_y = row))) {
							(*killedPlayer) == 1;
						}
						if ((grid[collumn - 1][row] == 0) || (grid[collumn - 1][row] == 7) || (grid[collumn - 1][row] == 8) || (grid[collumn - 1][row] == 9)) {
							grid[collumn - 1][row] = 9;
							//screen.fillRect((((collumn - 1) * 20) + 4), ((row * 20) + 4), 14, 14, RGB(255, 127, 0));
							init_Pictures("ex.bmp", ((collumn - 1) * 20), (row * 20), screen);
						}
						else if (grid[collumn - 1][row] == 2) {
							grid[collumn - 1][row] = 9;
							//screen.fillRect((((collumn - 1) * 20) + 4), ((row * 20) + 4), 14, 14, RGB(255, 127, 0));
							init_Pictures("ex.bmp", ((collumn - 1) * 20), (row * 20), screen);
							(*score)++;
							break;
						}
						else if (grid[collumn - 1][row] == 1) {
							break;
						}
					}
					collumn = icollumn;
					row = irow;
					for (row; row < (irow + bombradius); row++) {
						if ((grid[player1_x][player1_y] == 7 || grid[player1_x][player1_y] == 8 || grid[player1_x][player1_y] == 9) && ((player1_x = collumn) && (player1_y = row))) {
							(*killedPlayer) = 1;
						}
						if ((grid[collumn][row + 1] == 0) || (grid[collumn][row + 1] == 7) || (grid[collumn][row + 1] == 8) || (grid[collumn][row + 1] == 9)) {
							grid[collumn][row + 1] = 9;
							//screen.fillRect(((collumn * 20) + 4), (((row + 1) * 20) + 4), 14, 14, RGB(255, 127, 0));
							init_Pictures("ex.bmp", (collumn * 20), ((row + 1) * 20), screen);
						}
						else if (grid[collumn][row + 1] == 2) {
							grid[collumn][row + 1] = 9;
							//screen.fillRect(((collumn * 20) + 4), (((row + 1) * 20) + 4), 14, 14, RGB(255, 127, 0));
							init_Pictures("ex.bmp", (collumn * 20), ((row + 1) * 20), screen);
							(*score)++;
							break;
						}
						else if (grid[collumn][row + 1] == 1) {
							break;
						}
					}
					for (row; row > (irow - bombradius); row--) {
						if ((grid[player1_x][player1_y] == 7 || grid[player1_x][player1_y] == 8 || grid[player1_x][player1_y] == 9) && ((player1_x = collumn) && (player1_y = row))) {
							(*killedPlayer) = 1;
						}
						if ((grid[collumn][row - 1] == 0) || (grid[collumn][row - 1] == 7) || (grid[collumn][row - 1] == 8) || (grid[collumn][row - 1] == 9)) {
							grid[collumn][row - 1] = 9;
							//screen.fillRect(((collumn * 20) + 4), (((row - 1) * 20) + 4), 14, 14, RGB(255, 127, 0));
							init_Pictures("ex.bmp", (collumn * 20), ((row - 1) * 20), screen);
						}
						else if (grid[collumn][row - 1] == 2) {
							grid[collumn][row - 1] = 9;
							//screen.fillRect(((collumn * 20) + 4), (((row - 1) * 20) + 4), 14, 14, RGB(255, 127, 0));
							init_Pictures("ex.bmp", (collumn * 20), ((row - 1) * 20), screen);
							(*score)++;
							break;
						}
						else if (grid[collumn][row - 1] == 1) {
							break;
						}
					}
					(*livebombs)--;
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

void check_Bomb(uint8_t player1_x, uint8_t player1_y, uint8_t* player1_x_bombdrop, uint8_t* player1_y_bombdrop, uint8_t max_bombs, uint8_t* livebombs, uint8_t* antiholdCounter, uint8_t nunchuck_buf[], uint8_t grid[16][12])
{
	if ((!((nunchuck_buf[5] >> 0) & 1)) && (max_bombs != (*livebombs))) {
		if ((*antiholdCounter) != 1) {
			grid[player1_x][player1_y] = 6;
			(*antiholdCounter) = 1;
			(*player1_x_bombdrop) = player1_x;
			(*player1_y_bombdrop) = player1_y;
			(*livebombs)++;
		}
	}
	else {
		(*antiholdCounter) = 0;
	}
}

void draw_Bomb(uint8_t player1_x, uint8_t player1_y, uint8_t* player1_x_bombdrop, uint8_t* player1_y_bombdrop, MI0283QT9 screen)
{
	if ((((*player1_x_bombdrop) != 0) && ((*player1_y_bombdrop) != 0)) && ((player1_x != (*player1_x_bombdrop)) || (player1_y != (*player1_y_bombdrop)))) {
		//screen.fillRect((((*player1_x_bombdrop) * 20) + 4), (((*player1_y_bombdrop) * 20) + 4), 14, 14, RGB(180, 0, 0));
		init_Pictures("bom.bmp", ((*player1_x_bombdrop) * 20), ((*player1_y_bombdrop) * 20), screen);
		(*player1_x_bombdrop) = 0;
		(*player1_y_bombdrop) = 0;
	}
}

