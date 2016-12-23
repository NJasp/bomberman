#include "Sound.h"

void sound(uint16_t* speakerCounter, uint16_t* speakerTone)
{
	DDRD = (1 << PORTD4); // speaker port

	if ((*speakerCounter) > (*speakerTone)) {
		PORTD ^= (1 << PORTD4);
		(*speakerCounter) = 0;
	}
	(*speakerCounter)++;

}