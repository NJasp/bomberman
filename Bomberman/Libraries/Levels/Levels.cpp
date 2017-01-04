#include "Levels.h"

void init_Level(uint8_t grid[16][12], uint8_t level, uint8_t* player1_x, uint8_t* player1_y, uint8_t* player1_x_old, uint8_t* player1_y_old, uint8_t isPlayer2, uint32_t* nTimer, volatile uint8_t* isSendingIR, uint16_t* seed)
{
	uint8_t j = 1;
	if (level == 0) {
		// only if seed isn't set by IR generate new seed and send it
		if(*seed == 0) {
			*seed = (uint16_t)((*nTimer) >> 18);

			// make sure first 7 bits aren't all 1
			*seed &= (1 << 8);

			// make sure first 3 bits are 1
			*seed |= (1 << 15) | (1 << 14) | (1 << 13);

			// send over seed
            // split seed into two 7 bit values stored in uint8_t vars
			send_IR(isSendingIR, LEVEL, (uint8_t)((*seed) >> 7), (uint8_t)(*seed)&~(1 << 7));
		}

		srand(*seed);
		uint8_t row, collumn, number, counter0 = 0, counter1 = 0, counter2 = 0;
		init_OutsideWalls(grid);
		if(isPlayer2) {
			*player1_x = 10;
			*player1_y = 14;
			*player1_x_old = 10;
			*player1_y_old = 14;
		}
		else {
			*player1_x = 1;
			*player1_y = 1;
			*player1_x_old = 1;
			*player1_y_old = 1;
		}
		for (row = 1; row < 11; row++) {
			for (collumn = 1; collumn < 15; collumn++) {
				number = rand() % 5;
				switch (number) {
				case 0:
					counter0++;
					grid[collumn][row] = 0;
					break;
				case 1:
					counter0++;
					grid[collumn][row] = 0;
					break;
				case 2:
					counter1++;
					grid[collumn][row] = 1;
					break;
				case 3:
					counter2++;
					grid[collumn][row] = 2;
					break;
				case 4:
					counter2++;
					grid[collumn][row] = 2;
					break;
				}
			}
		}
		grid[1][1] = 0;  //grid[collumn][row]
		grid[1][2] = 0;
		grid[2][1] = 0;
		grid[14][9] = 0;
		grid[14][10] = 0;
		grid[13][10] = 0;
	}
	if (level == 1) {
		if(isPlayer2) {
			*player1_x = 14;
			*player1_y = 10;
			*player1_x_old = 14;
			*player1_y_old = 10;
		}
		else {
			*player1_x = 1;
			*player1_y = 1;
			*player1_x_old = 1;
			*player1_y_old = 1;
		}
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
	if (level == 2) {
		if (isPlayer2) {
			*player1_x = 7;
			*player1_y = 10;
			*player1_x_old = 7;
			*player1_y_old = 10;
		}
		else {
			*player1_x = 7;
			*player1_y = 2;
			*player1_x_old = 7;
			*player1_y_old = 2;
		}
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
	if (level == 3) {
		if (isPlayer2) {
			*player1_x = 10;
			*player1_y = 14;
			*player1_x_old = 10;
			*player1_y_old = 14;
		}
		else {
			*player1_x = 1;
			*player1_y = 1;
			*player1_x_old = 1;
			*player1_y_old = 1;
		}
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
	if (level == 4) {
		*player1_x = 2;
		*player1_y = 2;
		*player1_x_old = 2;
		*player1_y_old = 2;
		init_OutsideWalls(grid);
		grid[1][j] = 2;
		grid[2][j] = 2;
		grid[3][j] = 2;
		grid[4][j] = 2;
		grid[5][j] = 2;
		grid[6][j] = 2;
		grid[7][j] = 1;
		grid[8][j] = 1;
		grid[9][j] = 2;
		grid[10][j] = 2;
		grid[11][j] = 2;
		grid[12][j] = 2;
		grid[13][j] = 2;
		grid[14][j] = 2;
		j = 2;
		grid[1][j] = 2;
		grid[2][j] = 0;
		grid[3][j] = 0;
		grid[4][j] = 2;
		grid[5][j] = 2;
		grid[6][j] = 1;
		grid[7][j] = 2;
		grid[8][j] = 2;
		grid[9][j] = 1;
		grid[10][j] = 2;
		grid[11][j] = 2;
		grid[12][j] = 0;
		grid[13][j] = 0;
		grid[14][j] = 2;
		j = 3;
		grid[1][j] = 2;
		grid[2][j] = 0;
		grid[3][j] = 2;
		grid[4][j] = 2;
		grid[5][j] = 1;
		grid[6][j] = 2;
		grid[7][j] = 2;
		grid[8][j] = 2;
		grid[9][j] = 2;
		grid[10][j] = 1;
		grid[11][j] = 2;
		grid[12][j] = 2;
		grid[13][j] = 0;
		grid[14][j] = 2;
		j = 4;
		grid[1][j] = 2;
		grid[2][j] = 2;
		grid[3][j] = 2;
		grid[4][j] = 1;
		grid[5][j] = 2;
		grid[6][j] = 2;
		grid[7][j] = 2;
		grid[8][j] = 2;
		grid[9][j] = 2;
		grid[10][j] = 2;
		grid[11][j] = 1;
		grid[12][j] = 2;
		grid[13][j] = 2;
		grid[14][j] = 2;
		j = 5;
		grid[1][j] = 2;
		grid[2][j] = 2;
		grid[3][j] = 1;
		grid[4][j] = 2;
		grid[5][j] = 2;
		grid[6][j] = 2;
		grid[7][j] = 1;
		grid[8][j] = 1;
		grid[9][j] = 2;
		grid[10][j] = 2;
		grid[11][j] = 2;
		grid[12][j] = 1;
		grid[13][j] = 2;
		grid[14][j] = 2;
		j = 6;
		grid[1][j] = 2;
		grid[2][j] = 2;
		grid[3][j] = 1;
		grid[4][j] = 2;
		grid[5][j] = 2;
		grid[6][j] = 2;
		grid[7][j] = 1;
		grid[8][j] = 1;
		grid[9][j] = 2;
		grid[10][j] = 2;
		grid[11][j] = 2;
		grid[12][j] = 1;
		grid[13][j] = 2;
		grid[14][j] = 2;
		j = 7;
		grid[1][j] = 2;
		grid[2][j] = 2;
		grid[3][j] = 2;
		grid[4][j] = 1;
		grid[5][j] = 2;
		grid[6][j] = 2;
		grid[7][j] = 2;
		grid[8][j] = 2;
		grid[9][j] = 2;
		grid[10][j] = 2;
		grid[11][j] = 1;
		grid[12][j] = 2;
		grid[13][j] = 2;
		grid[14][j] = 2;
		j = 8;
		grid[1][j] = 2;
		grid[2][j] = 0;
		grid[3][j] = 2;
		grid[4][j] = 2;
		grid[5][j] = 1;
		grid[6][j] = 2;
		grid[7][j] = 2;
		grid[8][j] = 2;
		grid[9][j] = 2;
		grid[10][j] = 1;
		grid[11][j] = 2;
		grid[12][j] = 2;
		grid[13][j] = 0;
		grid[14][j] = 2;
		j = 9;
		grid[1][j] = 2;
		grid[2][j] = 0;
		grid[3][j] = 0;
		grid[4][j] = 2;
		grid[5][j] = 2;
		grid[6][j] = 1;
		grid[7][j] = 2;
		grid[8][j] = 2;
		grid[9][j] = 1;
		grid[10][j] = 2;
		grid[11][j] = 2;
		grid[12][j] = 0;
		grid[13][j] = 0;
		grid[14][j] = 2;
		j = 10;
		grid[1][j] = 2;
		grid[2][j] = 2;
		grid[3][j] = 2;
		grid[4][j] = 2;
		grid[5][j] = 2;
		grid[6][j] = 2;
		grid[7][j] = 1;
		grid[8][j] = 1;
		grid[9][j] = 2;
		grid[10][j] = 2;
		grid[11][j] = 2;
		grid[12][j] = 2;
		grid[13][j] = 2;
		grid[14][j] = 2;
	}
	if (level == 5) {
		uint8_t collumn, row;
		if (isPlayer2) {
			*player1_x = 14;
			*player1_y = 10;
			*player1_x_old = 14;
			*player1_y_old = 10;
		}
		else {
			*player1_x = 1;
			*player1_y = 1;
			*player1_x_old = 1;
			*player1_y_old = 1;
		}
		init_OutsideWalls(grid);
		for (row = 1; row < 11; row++) {
			for (collumn = 1; collumn < 15; collumn++) {
					grid[collumn][row] = 0;
			}
		}
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
