#ifndef Bomb_H_
#define Bomb_H_

#include "../Includes/Includes.h"

void draw_Explosion(MI0283QT9 screen, uint8_t bombradius, uint8_t grid[16][12], uint8_t* livebombs, uint8_t* score);
void clear_Explosion(MI0283QT9 screen, uint8_t bombradius, uint8_t grid[16][12], uint8_t player1_x, uint8_t player1_y);
void check_Bomb(uint8_t collumn, uint8_t row, uint8_t* collumn_bombdrop, uint8_t* row_bombdrop, uint8_t max_bombs, uint8_t* livebombs, uint8_t* antiholdCounter, uint8_t nunchuck_buf[], uint8_t grid[16][12], uint8_t* sendBomb);
void draw_Bomb(uint8_t player1_x, uint8_t player1_y, uint8_t* player1_x_bombdrop, uint8_t* player1_y_bombdrop, MI0283QT9 screen, uint8_t grid[16][12]);
void sound();
#endif

