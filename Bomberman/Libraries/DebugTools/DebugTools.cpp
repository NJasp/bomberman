#include "DebugTools.h"

void view_Griddata(uint8_t grid[16][12])	//print the grid to serial
{
	Serial.begin(9600);
	uint8_t i = 0, row, collumn;
	for (row = 0; row < 12; row++) {
		for (collumn = 0; collumn < 16; collumn++) {
			if (i < 15) {
				Serial.print(grid[collumn][row]);
				i++;
			}
			else {
				Serial.println(grid[collumn][row]);
				i = 0;
			}
			Serial.flush();

		}
	}
}