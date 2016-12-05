#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "IR.h"
volatile uint8_t clock = 0, timer = 0;
volatile uint16_t IRdata = 0;
volatile uint32_t nTimer = 0;

ISR(TIMER2_COMPA_vect){// timer for receiving/sending
	nTimer++;

	// ms timer
	timer++;
	if(timer == 179){
		clock++;
		timer = 0;
	}

	// send function
	if(isSending_IR()) {
		processSend_IR(nTimer);
	}
}

ISR(INT0_vect){ // receive interrupt
	processRecieve_IR(nTimer, &IRdata);
}

void init_Timer() {
	TCCR2A = 0;
	TCCR2B = 0;
	TIMSK2 = 0;
	TCCR2A = (1 << COM2B0) | (1 << WGM21); 	// toggle OC2B on match
	TCCR2B |= (1 << CS21); 					// 8 prescaler
	TIMSK2 |= (1 << OCIE2A);				// enable compare interrupt|
	OCR2B = 26; 					// value to compare timer against	| 1/((2*26)*(1/16000000)*8) = 37,7kHz
	OCR2A = 26;								// counter
	sei();
}

int main(){
	init_Timer();
	init_IR();
	Serial.begin(9600);
	uint32_t failCounter = 0;
	uint32_t successCounter = 0;
	uint8_t test1 = 0;

	for(;;){
		if(clock>1 && clock<5){
			if(test1){
				Serial.println("\nsent: 0:6:9");
				send_IR(0, 6, 9);
				test1 = !test1;
			}
			else{
				Serial.println("\nsent: 3:127:127");
				send_IR(3, 127, 127);
				test1 = !test1;
			}
			clock = 6;
		}

		if(clock>250 && clock < 256 && dataReady_IR()){
			Serial.print("received:\ntype: ");
			Serial.println(decode_IR(IRdata).type);
			Serial.print("x: ");
			Serial.println(decode_IR(IRdata).xData);
			Serial.print("y: ");
			Serial.println(decode_IR(IRdata).yData);
//				if((decode_IR(IRdata).type == 0 && decode_IR(IRdata).xData == 6 && decode_IR(IRdata).yData == 9 && !test1) ||
//						(decode_IR(IRdata).type == 3 && decode_IR(IRdata).xData == 127 && decode_IR(IRdata).yData == 127 && test1))
//					successCounter++;
//				else
//					failCounter++;
//
//				Serial.print("\nfail: ");
//				Serial.println(failCounter);
//				Serial.print("success: ");
//				Serial.println(successCounter);
			clock = 0;
			IRdata = 0;
		}
	}

	return 0;
}
