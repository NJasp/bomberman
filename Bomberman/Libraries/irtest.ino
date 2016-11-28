#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "IR.h"
volatile uint8_t timer = 0, clock = 0;
volatile uint16_t IRdata = 0;
volatile uint32_t nTimer = 0;
volatile uint8_t debugCounter = 0;

ISR(TIMER2_OVF_vect) {
	timer++;
	if(timer == 8){ // Close enough to work as ms counter, 7.8 precise
		clock++;
		timer = 0;
	}
}

ISR(TIMER2_COMPA_vect){// 10 nano second timer
	nTimer++;

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
	TCCR2A = (1 << COM2B0); 	// toggle OC2A on match
	TCCR2B |= (1 << CS21); 		// 8 prescaler
	TIMSK2 |= (1 << TOIE2) | (1 << OCIE2A);		// enable overflow interrupt|
	OCR2B = 53; 				// value to compare timer against	| 1/(53*(1/16000000)*8) = 37,7kHz
	OCR2A = 2;								// nanosecond counter
	TCNT2 = 0;										//SET TIMER 2 AAN (Prescaling 1/1024)
	sei();
}

int main(){
	init();
	init_Timer();
	init_IR();
	Serial.begin(9600);

	for(;;){
		send_IR(1,13,10);
		Serial.print("type: ");
		Serial.println(decode_IR(IRdata).type);
		Serial.print("x: ");
		Serial.println(decode_IR(IRdata).xData);
		Serial.print("y: ");
		Serial.println(decode_IR(IRdata).yData);
		_delay_ms(1000);
		/*
		timeDelta = 0;
		isSending = 1;
		_delay_ms(1000);
		Serial.println(" bits received\n===== received =====");
		Serial.print("type: ");
		Serial.println(IR_decode(data).type);
		Serial.print("x: ");
		Serial.println(IR_decode(data).xData);
		Serial.print("y: ");
		Serial.println(IR_decode(data).yData);
		*/
		/*
		Serial.print(debugCounter);
		Serial.print("sending: ");
		Serial.println(isSending);
		dataCount = 0;
		IR_send(3,120,120);
		_delay_ms(1000);
		Serial.println(" bits received\n===== received =====");
		Serial.print("type: ");
		Serial.println(IR_decode(data).type);
		Serial.print("x: ");
		Serial.println(IR_decode(data).xData);
		Serial.print("y: ");
		Serial.println(IR_decode(data).yData);
		*/
	}
	return 0;
}
