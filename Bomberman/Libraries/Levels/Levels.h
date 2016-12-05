#ifndef Levels_H_
#define Levels_H_

#include "../Includes/Includes.h"

void init_Testlevel(uint8_t grid[16][12]);
void init_Level(uint8_t grid[16][12], char* level);
void init_OutsideWalls(uint8_t grid[16][12]);
void draw_Walls_Crates(MI0283QT9 screen, uint8_t grid[16][12], char *wall_Type, char *crate_Type);

#endif
