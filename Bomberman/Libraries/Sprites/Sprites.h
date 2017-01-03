#ifndef Sprites_H_
#define Sprites_H_

#include "../Includes/Includes.h"

void draw_Sprites(MI0283QT9 lcd, uint8_t grid[16][12]);
void draw_PlayerSprite(MI0283QT9 lcd, uint8_t player1_x, uint8_t player1_y);
void draw_BombSprite(MI0283QT9 lcd, uint8_t player1_x, uint8_t player1_y);
#endif