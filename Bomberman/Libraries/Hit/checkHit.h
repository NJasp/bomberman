#ifndef checkHit_H_
#define checkHit_H_

#include "../Includes/Includes.h"

void checkPlayerHit(uint8_t player1_x, uint8_t player1_y, uint8_t *hit, uint8_t grid[16][12], uint8_t* LivesCounter);
void updateLives(uint8_t* hit, uint8_t* lives, MI0283QT9 lcd, uint8_t* score, uint8_t* stage, uint8_t grid[16][12]);
void resetVariables(uint8_t* score, uint8_t* stage, uint8_t* lives, uint8_t grid[16][12]);

#endif