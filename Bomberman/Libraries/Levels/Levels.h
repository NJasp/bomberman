#ifndef Levels_H_
#define Levels_H_

#include "../Includes/Includes.h"

void init_Level(uint8_t grid[16][12], uint8_t level, uint8_t* player_x, uint8_t* player_y, uint8_t* player1_x_old, uint8_t* player1_y_old, uint8_t isPlayer2);
void init_OutsideWalls(uint8_t grid[16][12]);

#endif
