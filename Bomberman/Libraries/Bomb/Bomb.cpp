#include "Bomb.h"
#include "string.h"
#include "../Hit/checkHit.h"
#include "../Sprites/Sprites.h"

void draw_Explosion(MI0283QT9 screen, uint8_t bombradius, uint8_t grid[16][12], uint8_t* livebombs, uint8_t* score, uint8_t player1_x, uint8_t player1_y, uint8_t* player1_x_bombdrop, uint8_t* player1_y_bombdrop)
{
	uint8_t row, collumn, icollumn, irow;
	for (row = 0; row < 12; row++) {
		for (collumn = 0; collumn < 16; collumn++) {
			if (grid[collumn][row] == 3) {
				if ((player1_x == (*player1_x_bombdrop)) && (player1_y == (*player1_y_bombdrop))) {
					(*player1_x_bombdrop) = 0;
					(*player1_y_bombdrop) = 0;
				}
				grid[collumn][row] = 9;
				screen.fillRect(((collumn * 20) + 4), ((row * 20) + 4), 14, 14, RGB(255, 127, 0));
				icollumn = collumn;
				irow = row;
				for (collumn; collumn < (icollumn + bombradius); collumn++) {
					//checkPlayerHit(player1_x, player1_y, hit, grid);
					if ((grid[collumn + 1][row] == 0) || (grid[collumn + 1][row] == 7) || (grid[collumn + 1][row] == 8) || (grid[collumn + 1][row] == 9)) {
						grid[collumn + 1][row] = 9;
						screen.fillRect((((collumn + 1) * 20) + 4), ((row * 20) + 4), 14, 14, RGB(255, 127, 0));
					}
					else if (grid[collumn + 1][row] == 2) {
						grid[collumn + 1][row] = 9;
						screen.fillRect((((collumn + 1) * 20) + 4), ((row * 20) + 4), 14, 14, RGB(255, 127, 0));
						(*score)++;
						break;
					}
					else if (grid[collumn + 1][row] == 1) {
						break;
					}
				}
				for (collumn; collumn > (icollumn - bombradius); collumn--) {
					//checkPlayerHit(player1_x, player1_y, hit, grid);
					if ((grid[collumn - 1][row] == 0) || (grid[collumn - 1][row] == 7) || (grid[collumn - 1][row] == 8) || (grid[collumn - 1][row] == 9)) {
						grid[collumn - 1][row] = 9;
						screen.fillRect((((collumn - 1) * 20) + 4), ((row * 20) + 4), 14, 14, RGB(255, 127, 0));
					}
					else if (grid[collumn - 1][row] == 2) {
						grid[collumn - 1][row] = 9;
						screen.fillRect((((collumn - 1) * 20) + 4), ((row * 20) + 4), 14, 14, RGB(255, 127, 0));
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
					//checkPlayerHit(player1_x, player1_y, hit, grid);
					if ((grid[collumn][row + 1] == 0) || (grid[collumn][row + 1] == 7) || (grid[collumn][row + 1] == 8) || (grid[collumn][row + 1] == 9)) {
						grid[collumn][row + 1] = 9;
						screen.fillRect(((collumn * 20) + 4), (((row + 1) * 20) + 4), 14, 14, RGB(255, 127, 0));
					}
					else if (grid[collumn][row + 1] == 2) {
						grid[collumn][row + 1] = 9;
						screen.fillRect(((collumn * 20) + 4), (((row + 1) * 20) + 4), 14, 14, RGB(255, 127, 0));
						(*score)++;
						break;
					}
					else if (grid[collumn][row + 1] == 1) {
						break;
					}
				}
				for (row; row > (irow - bombradius); row--) {
					//checkPlayerHit(player1_x, player1_y, hit, grid);
					if ((grid[collumn][row - 1] == 0) || (grid[collumn][row - 1] == 7) || (grid[collumn][row - 1] == 8) || (grid[collumn][row - 1] == 9)) {
						grid[collumn][row - 1] = 9;
						screen.fillRect(((collumn * 20) + 4), (((row - 1) * 20) + 4), 14, 14, RGB(255, 127, 0));
					}
					else if (grid[collumn][row - 1] == 2) {
						grid[collumn][row - 1] = 9;
						screen.fillRect(((collumn * 20) + 4), (((row - 1) * 20) + 4), 14, 14, RGB(255, 127, 0));
						(*score)++;
						break;
					}
					else if (grid[collumn][row - 1] == 1) {
						break;
					}
				}
			}
			//checkPlayerHit(player1_x, player1_y, hit, grid, LivesCounter);
		}

	}
}

void clear_Explosion(MI0283QT9 screen, uint8_t bombradius, uint8_t grid[16][12], uint8_t player1_x, uint8_t player1_y, uint8_t* livebombs)
{
	uint8_t row, collumn, icollumn, irow;
	for (row = 0; row < 12; row++) {
		for (collumn = 0; collumn < 16; collumn++) {
			if (grid[collumn][row] == 7) {
				(*livebombs) = 0;
				if (grid[player1_x][player1_y] == 7) {
					screen.fillRect(collumn * 20, row * 20, 20, 20, Background);
					draw_PlayerSprite(screen, player1_x, player1_y);
					grid[collumn][row] = 0;
				}
				else {
					grid[collumn][row] = 0;
					screen.fillRect(collumn * 20, row * 20, 20, 20, Background);
				}
			}
		}
	}
}

void check_Bomb(uint8_t collumn, uint8_t row, uint8_t* collumn_bombdrop, uint8_t* row_bombdrop, uint8_t max_bombs, uint8_t* livebombs, uint8_t* antiholdCounter, uint8_t nunchuck_buf[], uint8_t grid[16][12], uint8_t* sendBomb)
{
	if ((!((nunchuck_buf[5] >> 0) & 1)) && (max_bombs > (*livebombs))) {
		if ((*antiholdCounter) != 1) {
			grid[collumn][row] = 6;
			(*antiholdCounter) = 1;
			(*collumn_bombdrop) = collumn;
			(*row_bombdrop) = row;
			(*livebombs) = 1;
			// send over position of new bomb
			*sendBomb = 1;
		}
	}
	else {
		(*antiholdCounter) = 0;
	}
}

void draw_Bomb(uint8_t collumn, uint8_t row, uint8_t* collumn_bombdrop, uint8_t* row_bombdrop, MI0283QT9 screen, uint8_t grid[16][12])
{
	if ((((*collumn_bombdrop) != 0) && ((*row_bombdrop) != 0)) && ((collumn != (*collumn_bombdrop)) || (row != (*row_bombdrop)))) {
		//screen.fillRect((((*collumn_bombdrop) * 20) + 4), (((*row_bombdrop) * 20) + 4), 14, 14, RGB(180, 0, 0));
		draw_BombSprite(screen, (*collumn_bombdrop), (*row_bombdrop));
		if (((collumn == (*collumn_bombdrop)) || (row == (*row_bombdrop)))) {
			(*collumn_bombdrop) = 0;
			(*row_bombdrop) = 0;
		}
	}
}