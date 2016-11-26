#ifndef LCD_H_
#define LCD_H_

#include "../Includes/Includes.h"

void init_LCD(MI0283QT9 screen);
void draw_Grid(MI0283QT9 screen);
void draw_OutsideWalls(MI0283QT9 screen, uint8_t grid[16][12]);

#endif