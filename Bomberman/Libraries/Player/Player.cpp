#include "Player.h"
#include "../Sprites/Sprites.h"
#include "../Hit/checkHit.h"
#include "../DebugTools/DebugTools.h"

void init_Player(uint8_t player1_x, uint8_t player1_y, MI0283QT9 screen)
{
	//screen.fillRect(player1_x * 20, player1_y * 20, 20, 20, RGB(255,0,0));
	draw_PlayerSprite(screen, player1_x, player1_y);
}

void draw_Player(uint8_t player1_x, uint8_t player1_y, uint8_t* player1_x_old, uint8_t* player1_y_old, MI0283QT9 screen)
{
	if ((*player1_y_old) != player1_y || (*player1_x_old) != player1_x) {
		screen.fillRect((*player1_x_old) * 20, ((*player1_y_old) * 20), 20, 20, Background);
		//screen.fillRect(player1_x * 20, player1_y * 20, 20, 20, RGB(0, 255, 0));
		draw_PlayerSprite(screen, player1_x, player1_y);
		(*player1_x_old) = player1_x;
		(*player1_y_old) = player1_y;
	}
}

void draw_Player2(uint8_t player2_x, uint8_t player2_y, uint8_t player2_x_old, uint8_t player2_y_old, MI0283QT9 screen){
	// draw other player position if new
	if (player2_x != player2_x_old || player2_y != player2_y_old) {
		screen.fillRect(player2_x_old * 20, player2_y_old * 20, 20, 20, Background);

		// draw the bomb again when drawing over it
//					if (player2_x_old == player2_x_bombdrop && player2_y_old == player2_y_bombdrop && !grid[player2_x_bombdrop][player2_y_bombdrop]) {
//						draw_BombSprite(lcd, player2_x_bombdrop, player1_y_bombdrop);
//					}

		screen.fillRect(player2_x * 20, player2_y * 20, 20, 20, RGB(0, 0, 255));
	}
}


void calculate_Movement(uint8_t* player1_x, uint8_t* player1_y, uint8_t joy_x_axis, uint8_t joy_y_axis, uint8_t* player1_xCounter, uint8_t* player1_yCounter, uint8_t player1_x_speed, uint8_t player1_y_speed, uint8_t grid[16][12])
{
	
	if (joy_x_axis > 140) {
		if ((*player1_xCounter) == player1_x_speed) {
			if (grid[(*player1_x) + 1][(*player1_y)] == 0 || grid[(*player1_x) + 1][(*player1_y)] == 3 || ((grid[(*player1_x) + 1][(*player1_y)] > 6) && (grid[(*player1_x) + 1][(*player1_y)] < 10))) {
				if ((grid[(*player1_x) + 1][(*player1_y)] > 6) && (grid[(*player1_x) + 1][(*player1_y)] < 10)) {
					//checkPlayerHit((*player1_x) + 1, (*player1_y), hit, grid, LivesCounter);
				}
				(*player1_x)++;	//hier word de teller voor de X coordinaat verhoogt als de joystick naar rechts word gedrukt
				(*player1_xCounter) = 0;
			}
		}
		else {
			(*player1_xCounter)++;
		}
	}
	if (joy_x_axis < 114) {
		if ((*player1_xCounter) == player1_x_speed) {
			if (grid[(*player1_x) - 1][(*player1_y)] == 0 || grid[(*player1_x) - 1][(*player1_y)] == 3 || ((grid[(*player1_x) - 1][(*player1_y)] > 6) && (grid[(*player1_x) - 1][(*player1_y)] < 10))) {
				if ((grid[(*player1_x) - 1][(*player1_y)] > 6) && (grid[(*player1_x) - 1][(*player1_y)] < 10)) {
					//checkPlayerHit((*player1_x) - 1, (*player1_y), hit, grid, LivesCounter);
				}
				(*player1_x)--; //hier word de teller voor de X coordinaat verlaagt als de joystick naar links word gedrukt. komt niet lager als 0
				(*player1_xCounter) = 0;
			}
		}
		else {
			(*player1_xCounter)++;
		}
	}
	if (joy_y_axis > 140) {
		if ((*player1_yCounter) == player1_y_speed) {
			if (grid[(*player1_x)][(*player1_y) - 1] == 0 || grid[(*player1_x)][(*player1_y) - 1] == 3 || ((grid[(*player1_x)][(*player1_y) - 1] > 6) && (grid[(*player1_x)][(*player1_y) - 1] < 10))) {
				if ((grid[(*player1_x)][(*player1_y) - 1] > 6) && (grid[(*player1_x)][(*player1_y) - 1] < 10)) {
					//checkPlayerHit((*player1_x), (*player1_y)-1, hit, grid, LivesCounter);
				}
				(*player1_y)--;	//hier word de teller voor de Y coordinaat verlaagt als de joystick naar beneden word gedrukt
				(*player1_yCounter) = 0;
			}
		}
		else {
			(*player1_yCounter)++;
		}
	}
	if (joy_y_axis < 114) {
		if ((*player1_yCounter) == player1_y_speed) {
			if (grid[(*player1_x)][(*player1_y) + 1] == 0 || grid[(*player1_x)][(*player1_y) + 1] == 3 || ((grid[(*player1_x)][(*player1_y) + 1] > 6) && (grid[(*player1_x)][(*player1_y) + 1] < 10))) {
				if ((grid[(*player1_x)][(*player1_y) + 1] > 6) && (grid[(*player1_x)][(*player1_y) + 1] < 10)) {
					//checkPlayerHit((*player1_x), (*player1_y) + 1, hit, grid, LivesCounter);
				}
				(*player1_y)++;	//hier word de teller voor de Y coordinaat verhoogt als de joystick naar boven word gedrukt
				(*player1_yCounter) = 0;
			}
		}
		else {
			(*player1_yCounter)++;
		}
	}
}
