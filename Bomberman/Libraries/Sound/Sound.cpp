#include "Sound.h"


void sound()
{
	uint16_t speakerCounter = 0;
	if ((speakerCounter) > 500) {
		PORTD ^= (1 << PORTD4);
		(speakerCounter) = 0;
	}
	(speakerCounter)++;

}