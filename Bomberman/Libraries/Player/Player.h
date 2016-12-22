#ifndef Player_H_
#define Player_H_

#include "../Includes/Includes.h"

void init_Player(uint8_t player1_x, uint8_t player1_y, MI0283QT9 screen);
void draw_Player(uint8_t player1_x, uint8_t player1_y, uint8_t* player1_x_old, uint8_t* player1_y_old, MI0283QT9 screen);
void calculate_Movement(uint8_t* player1_x, uint8_t* player1_y, uint8_t joy_x_axis, uint8_t joy_y_axis, uint8_t* player1_xCounter, uint8_t* player1_yCounter, uint8_t player1_x_speed, uint8_t player1_y_speed, uint8_t grid[16][12]);

#endif
