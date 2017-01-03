#include "Potmeter.h"

void init_Potmeter() {
	
	DDRC = 0x00;
	PORTC |= (1 << PORTC3);
	ADMUX = 0x03; 	   										//Input channel 1 (A1)
	ADMUX |= (1 << REFS0);									//Vcc referentiespanning

	ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	//ADCklok=CPUklok/128
	ADCSRA |= (1 << ADEN);									//ADC inschakelen
	ADCSRA |= (1 << ADATE);									 //Auto trigger enable
	ADCSRB |= ~((1 << ADTS0) | (1 << ADTS1) | (1 << ADTS2)); //Freerunning mode voor LDR
	ADCSRA |= (1 << ADSC);									//een enkele AD-conversie

}

void set_Brightness(MI0283QT9 screen, uint8_t channel) {
	uint8_t result = (ADCW + 1) / 11;
	screen.led(result);

}