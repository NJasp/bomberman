/*
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

uint16_t result;

int main() {

	ADMUX = 0x01; 	   										//Input channel 1 (A1)
	ADMUX |= (1 << REFS0);									//Vcc referentiespanning

	ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);				//ADCklok=CPUklok/128
	ADCSRA |= (1 << ADEN);									//ADC inschakelen
	ADCSRA |= (1 << ADATE);									 //Auto trigger enable
	ADCSRB |= ~((1 << ADTS0) | (1 << ADTS1) | (1 << ADTS2)); //Freerunning mode voor LDR
	ADCSRA |= (1 << ADSC);        							 //een enkele AD-conversie

	for (;;) {
		result = ADC; //lees waarde uit (0-1023) en map het naar een waarde van 0-255
					  //Serial.println(result);				//print de gelezen waarde naar de seriele monitor
	}
} 
*/