#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "IR.h"
volatile uint8_t clock = 0, timer = 0;
volatile uint16_t IRdata = 0;
volatile uint32_t nTimer = 0;
volatile uint8_t debugCounter = 0;

ISR(TIMER2_OVF_vect) {
	/*
	timer++;
	if(timer == 8){ // Close enough to work as ms counter, 7.8 precise
		clock++;
		timer = 0;
	}
	*/
}

ISR(TIMER2_COMPA_vect){// 10 nano second timer
	nTimer++;
	timer++;
	if(timer == 190){// ms timer
		clock++;
		timer = 0;
	}

	// send function
	if(isSending_IR()) {
		processSend_IR(nTimer);
	}

}

ISR(INT0_vect){ // receive interrupt
	// DEBUG
//	Serial.print("timer: ");
//	Serial.println(nTimer);
//	Serial.print("debug: ");
//	Serial.println(debugCounter);
//	debugCounter++;
//	_delay_ms(1);

	processRecieve_IR(nTimer, &IRdata);
}

void init_Timer() {
	TCCR2A = 0;
	TCCR2B = 0;
	TIMSK2 = 0;
	TCCR2A = (1 << COM2B0) | (1 << WGM21); 	// toggle OC2B on match
	TCCR2B |= (1 << CS21); 		// 8 prescaler
	TIMSK2 |= (1 << TOIE2) | (1 << OCIE2A);		// enable overflow interrupt|
	OCR2B = 26; 				// value to compare timer against	| 1/(53*(1/16000000)*8) = 37,7kHz
	OCR2A = 26;								// nanosecond counter
	TCNT2 = 0;										//SET TIMER 2 AAN (Prescaling 1/1024)
	sei();
}

int main(){
	init_Timer();
	init_IR();
	Serial.begin(9600);
	uint8_t failCounter = 0;
	uint8_t successCounter = 0;
	uint8_t lol = 0;

	for(;;){
		if(clock>1 && clock<5){
			if(lol){
				Serial.println("\nsent: 0:6:9");
				send_IR(0, 6, 9);
				lol = !lol;
			}
			else{
				Serial.println("\nsent: 3:13:37");
				send_IR(3, 13, 37);
				lol = !lol;
			}
			clock = 6;
		}

		if(clock>250 && clock < 256){
				Serial.print("received:\ntype: ");
				Serial.println(decode_IR(IRdata).type);
				Serial.print("x: ");
				Serial.println(decode_IR(IRdata).xData);
				Serial.print("y: ");
				Serial.println(decode_IR(IRdata).yData);
				if((decode_IR(IRdata).type == 0 && decode_IR(IRdata).xData == 6 && decode_IR(IRdata).yData == 9 ) ||
						(decode_IR(IRdata).type == 3 && decode_IR(IRdata).xData == 13 && decode_IR(IRdata).yData == 37))
					successCounter++;
				else
					failCounter++;

				Serial.print("\nfail: ");
				Serial.println(failCounter);
				Serial.print("success: ");
				Serial.println(successCounter);
				clock = 0;
		}
	}

	return 0;
}
