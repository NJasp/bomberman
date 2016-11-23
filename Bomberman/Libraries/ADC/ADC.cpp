#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

//uint8_t teller = 0;
uint16_t result;

int main() {
	/*init();
	Serial.begin(9600);
	DDRB = (1 << PORTB3);			//PORTB3 als output (digital pwm pin 11)
	PORTC = (1 << PORTC1);			//Internal Pull-Up voor LDR
	TIMSK2 |= (1 << TOIE2);			//timer 2 overflow interrupt enable
	TCNT2 = 0;
	TCCR2A = (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);	//zet fast-pwm aan
	TCCR2B = (1 << CS22) | (1 << CS20) | (1 << CS21);		//prescaler 1/1024
	sei();		*/											//zet timer aan

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

/*ISR(TIMER2_OVF_vect) {		//Wanneer timer2 overflowed....
teller++;					//1 bij teller optellen
if (teller >= 6)			//als teller bij 6 is (1/10e seconde)...
{
OCR2A = result;			//Schrijf de huidige waarde van de LDR naar het compare register (waardoor de PWM verandert en zo ook de LED feller of minder fel brandt)
teller = 0;				//Reset de teller
}
}*/