#include "Nunchuck.h"

void init_Nunchuck()
{
	PORTC |= (1 << PORTC4) | (1 << PORTC5);

	Wire.begin();										//INITIALIZE NUNCHUCK                
	Wire.beginTransmission(0x52);
	Wire.write(0x40);
	Wire.write(0x00);
	Wire.endTransmission();
}

void read_Nunchuck(uint8_t buffer[], uint8_t* x, uint8_t* y, uint8_t* isPressed)
{
	int i = 0;
	Wire.requestFrom(0x52, 6);						//READ NUNCHUCKK
	while (Wire.available()) {
		buffer[i] = (Wire.read() ^ 0x17) + 0x17;;
		i++;
	}
	Wire.beginTransmission(0x52);
	Wire.write(0x00);
	Wire.endTransmission();
	*x = buffer[0];
	*y = buffer[1];
	if (!((buffer[5] >> 0) & 1)) {
		(*isPressed) = 1;
	}
	else {
		(*isPressed) = 0;
	}
}

