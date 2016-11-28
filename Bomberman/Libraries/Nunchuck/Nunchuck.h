#ifndef Nunchuck_H_
#define Nunchuck_H_

#include "../Includes/Includes.h"

void init_Nunchuck();
void read_Nunchuck(uint8_t buffer[], uint8_t* x, uint8_t* y);

#endif