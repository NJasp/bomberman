#include "../Includes/Includes.h"
#include "Leds.h"

void set_Leds(uint8_t leds) {
	uint8_t pins;
	// select given amount of leds to turn on
	switch(leds){
		case 0:
			pins = 0;
			break;
		case 1:
			pins = (1 << 1);
			break;
		case 2:
			pins = (1 << 1) | (1 << 2);
			break;
		case 3:
			pins = (1 << 1) | (1 << 2) | (1 << 3);
			break;
	}

	// turn on selected leds
	Wire.beginTransmission(56);
	Wire.write(pins);
	Wire.endTransmission();
}
