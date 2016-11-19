#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdarg.h>
#include "ir.h"

void IR_init() {
	DDRD &= ~(1 << PORTD2);		// input INT0 pin (pin 2)
	PORTD |= (1 << PORTD2);		// pullup INT0 pin
	EIMSK |= (1 << INT0);		// enable INT0
	EICRA |= (1 << ISC00);		// any change generates interrupt INT0

	DDRB |= (1 << PORTB3);		// output OC2A pin (pin 11)
	TCCR2A = (1 << COM2A0); 	// toggle OC2A on match
	TCCR2B |= (1 << CS21); 		// 8 prescaler						|
	OCR2A = 53; 				// value to compare timer against	| 1/(53*(1/16000000)*8) = 37,7kHz

	sei();						// enable global interrupts
}

void IR_toggle() {
	DDRB ^= (1 << PORTB3);
}

uint32_t IR_decode(uint32_t data) {
	// decode
	return data;
}

uint32_t IR_encode(uint8_t data, ...){
	uint32_t encoded;
	// encode
	return data;
}

void IR_send(uint8_t type, uint8_t xPos, uint8_t yPos) {
	uint32_t data = IR_encode(type, xPos, yPos);
	// send
}

void IR_test() {
	DDRB |= (1 << PORTB4); // testled
	IR_init();

	for(;;){
		 _delay_ms(100);
		IR_toggle();
	}
}
