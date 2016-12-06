#ifndef mSD_shield_H_
#define mSD_shield_H_

#include "../Includes/Includes.h"

void init_SDcart(MI0283QT9 screen);
void draw_Pictures(char *file, int16_t x, int16_t y, MI0283QT9 screen);
#endif
