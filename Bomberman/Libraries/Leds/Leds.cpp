#include "../Includes/Includes.h"
#include "Leds.h"

void set_Leds(uint8_t leds) {
	uint8_t pins;
	// select given amount of leds to turn on
	switch(leds){
		case 0:
			pins = 0xff;
			break;
		case 1:
			pins = 0b11111101;
			break;
		case 2:
			pins = 0b11111001;
			break;
		case 3:
			pins = 0b11110001;
			break;
	}

	// turn on selected leds
	Wire.beginTransmission(56);
	Wire.write(pins);
	Wire.endTransmission();
}
