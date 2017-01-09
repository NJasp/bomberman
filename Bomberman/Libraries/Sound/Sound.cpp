#include "Sound.h"

uint16_t speakerCounter = 0;

void sound()
{
	if ((speakerCounter) > 100){
		PORTD ^= (1 << PORTD4);
		(speakerCounter) = 0;
	}
	speakerCounter++;

}