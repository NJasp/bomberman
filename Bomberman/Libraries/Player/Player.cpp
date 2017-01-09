#include "Player.h"
#include "../Sprites/Sprites.h"

void init_Player(uint8_t player1_x, uint8_t player1_y, MI0283QT9 screen) // Print player on screen, after that draw_Player, but that only works if player movement is detected.
{
	draw_PlayerSprite(screen, player1_x, player1_y); 
}

void draw_Player(uint8_t player1_x, uint8_t player1_y, uint8_t* player1_x_old, uint8_t* player1_y_old, MI0283QT9 screen) // Print player when movement is detected. Remove old position sprite.
{
	if ((*player1_y_old) != player1_y || (*player1_x_old) != player1_x) {
		screen.fillRect((*player1_x_old) * 20, ((*player1_y_old) * 20), 20, 20, Background);	// Remove old player position sprite.
		draw_PlayerSprite(screen, player1_x, player1_y);										// Print sprite on the new player position.
		(*player1_x_old) = player1_x;															// Makes the current X coordinate the old X coordinate.
		(*player1_y_old) = player1_y;															// Makes the current Y coordinate the old Y coordinate.
	}
}


void calculate_Movement(uint8_t* player1_x, uint8_t* player1_y, uint8_t joy_x_axis, uint8_t joy_y_axis, uint8_t* player1_xCounter, uint8_t* player1_yCounter, uint8_t player1_x_speed, uint8_t player1_y_speed, uint8_t grid[16][12])
{
	
	if (joy_x_axis > 140) { // Check if the joystick is moved to the right.
		if ((*player1_xCounter) == player1_x_speed) {
			if (grid[(*player1_x) + 1][(*player1_y)] == 0 || grid[(*player1_x) + 1][(*player1_y)] == 3 || ((grid[(*player1_x) + 1][(*player1_y)] > 6) && (grid[(*player1_x) + 1][(*player1_y)] < 10))) {
				(*player1_x)++;	// Increases the counter for X coordinate when the joystick is moved to the right.
				(*player1_xCounter) = 0;
			} 
		}
		else {
			(*player1_xCounter)++;
		}
	}
	if (joy_x_axis < 114) { // Check if the joystick is moved to the left.
		if ((*player1_xCounter) == player1_x_speed) {
			if (grid[(*player1_x) - 1][(*player1_y)] == 0 || grid[(*player1_x) - 1][(*player1_y)] == 3 || ((grid[(*player1_x) - 1][(*player1_y)] > 6) && (grid[(*player1_x) - 1][(*player1_y)] < 10))) {
				(*player1_x)--; // Decreases the counter for X coordinate when the joystick is moved to the left. Will not get below 0.
				(*player1_xCounter) = 0; 
			}
		}
		else {
			(*player1_xCounter)++;
		}
	}
	if (joy_y_axis > 140) { // Check if the joystick is moved downwards.
		if ((*player1_yCounter) == player1_y_speed) {
			if (grid[(*player1_x)][(*player1_y) - 1] == 0 || grid[(*player1_x)][(*player1_y) - 1] == 3 || ((grid[(*player1_x)][(*player1_y) - 1] > 6) && (grid[(*player1_x)][(*player1_y) - 1] < 10))) {
				(*player1_y)--;	// Decreases the counter for Y coordinate when the joystick is moved downwards.
				(*player1_yCounter) = 0; 
			}
		}
		else {
			(*player1_yCounter)++;
		}
	}
	if (joy_y_axis < 114) { // Check if the joystick is moved upwards.
		if ((*player1_yCounter) == player1_y_speed) {
			if (grid[(*player1_x)][(*player1_y) + 1] == 0 || grid[(*player1_x)][(*player1_y) + 1] == 3 || ((grid[(*player1_x)][(*player1_y) + 1] > 6) && (grid[(*player1_x)][(*player1_y) + 1] < 10))) {
				(*player1_y)++;	// Increases the counter for Y coordinate when the joystick is moved upwards.
				(*player1_yCounter) = 0; 
			}
		}
		else {
			(*player1_yCounter)++;
		}
	}
}
