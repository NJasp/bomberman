#include "Player.h"

void init_Player(uint8_t player1_x, uint8_t player1_y, MI0283QT9 screen)
{
	screen.fillCircle((player1_x * 20) + 10, (player1_y * 20) + 10, 9, RGB(255, 0, 0));
}

void draw_Player(uint8_t player1_x, uint8_t player1_y, uint8_t* player1_x_old, uint8_t* player1_y_old, data_store player2, MI0283QT9 screen)
{
	if ((*player1_y_old) != player1_y || (*player1_x_old) != player1_x) {
		screen.fillCircle(((*player1_x_old) * 20) + 10, ((*player1_y_old) * 20) + 10, 9, RGB(255, 255, 255));
		screen.fillCircle((player1_x * 20) + 10, (player1_y * 20) + 10, 9, RGB(255, 0, 0));
		(*player1_x_old) = player1_x;
		(*player1_y_old) = player1_y;
		//send_IR(PLAYER, player1_x, player1_y);
	}
	/*if (player2.type == PLAYER) {
		screen.fillCircle((player2.xData * 20) + 10, (player2.yData * 20) + 10, 9, RGB(0, 0, 255));
	}*/
}

void calculate_Movement(uint8_t* player1_x, uint8_t* player1_y, uint8_t joy_x_axis, uint8_t joy_y_axis, uint8_t* player1_xCounter, uint8_t* player1_yCounter, uint8_t player1_x_speed, uint8_t player1_y_speed, uint8_t grid[16][12])
{
	if (joy_x_axis > 140) {
		if ((*player1_xCounter) == player1_x_speed) {
			if (grid[(*player1_x) + 1][(*player1_y)] == 0 || grid[(*player1_x) + 1][(*player1_y)] == 3 || ((grid[(*player1_x) + 1][(*player1_y)] > 6) && (grid[(*player1_x) + 1][(*player1_y)] < 10))) {
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
				(*player1_y)++;	//hier word de teller voor de Y coordinaat verhoogt als de joystick naar boven word gedrukt
				(*player1_yCounter) = 0;
			}
		}
		else {
			(*player1_yCounter)++;
		}
	}
}