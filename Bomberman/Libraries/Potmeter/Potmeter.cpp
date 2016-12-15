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

	//DDRC = 0x00;
	//PORTC = 0xFF;
	//ADMUX = 0x03; 	   										//Input channel 1 (A1)
	//ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));    //Prescaler at 128 so we have an 125Khz clock source
	//ADMUX |= (1 << REFS0);
	//ADCSRA |= (1 << ADEN);                //Power up the ADC
	//ADCSRA |= (1 << ADSC);                //Start converting
}

void set_Brightness(MI0283QT9 screen, uint8_t channel) {
	//ADMUX &= 0xF0; //clear the older channel that was read
	//ADMUX |= channel; //defines the new channel to be read
	//ADCSRA |= (1 << ADSC);//Start converting
	//while (ADCSRA & (1 << ADSC)); //wait until the conversion is done
	uint8_t result = (ADCW + 1) / 11;
	//Serial.println(result);
	screen.led(result);

}