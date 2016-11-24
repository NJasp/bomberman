/*
       ==============================================
                        implementaton:
       ===================----=======================
                   ===== interrupts =====
ISR(TIMER2_OVF_vect) {
	timer++;
	if(timer == 8){ // close enough to work as ms counter, 7.8 precise
		clock++;
		timer = 0;
	}
}

ISR(INT0_vect){
	if(recTimer > clock)
		timeDelta = 256+clock - recTimer;
	else
		timeDelta = clock - recTimer;

	if(timeDelta > 3 && timeDelta < 8) 	   // recieved 1
		data |= (1 << dataCount);
	else if (timeDelta < 3) 			   // recieved 0
		data &= ~(1 << dataCount);
	else 						   		   // end transmission
		dataCount = -1;

	dataCount++;
	recTimer = clock;
}

               ===== sending/handling data =====
IR_init();								   // initialize timers/config

IR_send(type, xData, yData);			   // send data

data_store myData = IR_decode(data);	   // store received data in struct
										   // data is now accessible through myData.type myData.xData myData.yData
*/
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "ir.h"



void IR_init() {
	DDRD &= ~(1 << PORTD2);		// input INT0 pin (pin 2)
	PORTD |= (1 << PORTD2);		// pullup INT0 pin
	EIMSK |= (1 << INT0);		// enable INT0
	EICRA |= (1 << ISC00);		// any change generates interrupt INT0

	// just use wire for test reasons
	DDRB |= (1 << PORTB5);

	DDRD |= (1 << PORTD3);		// output OC2A pin (pin 11)
	TCCR2A = (1 << COM2B0); 	// toggle OC2A on match
	TCCR2B |= (1 << CS21); 		// 8 prescaler						|
	OCR2B = 53; 				// value to compare timer against	| 1/(53*(1/16000000)*8) = 37,7kHz
	TIMSK2 |= (1 << TOIE2);		// enable overflow interrupt

	sei();						// enable global interrupts
}

void IR_toggle() {
	// just use wire for test reasons
	PORTB ^= (1 << PORTB5);

	DDRD ^= (1 << PORTD3);
}

void IR_off() {
	// just use wire for test reasons
	PORTB &= ~(1 << PORTB5);

	DDRD &= ~(1 << PORTD3);
}

void IR_on() {
	// just use wire for test reasons
	PORTB |= (1 << PORTB5);

	DDRD |= (1 << PORTD3);
}

data_store IR_decode(uint16_t data) {
	data_store returnData = {0,0,0};

	// fill first three bytes to get number back
	returnData.type |= ((data&(1 << 0) ? 1:0) << 0)
			| ((data&(1 << 1) ? 1:0) << 1);

	// fill data variables
	uint8_t i;
	for(i=0; i<7; i++){// 7 bits used to fit all in 16 bit var
		returnData.xData |= ((data&(1 << i+2) ? 1:0) << i);
		returnData.yData |= ((data&(1 << i+9) ? 1:0) << i);
	}
	return returnData;
}

uint16_t IR_encode(uint8_t type, uint8_t xData, uint8_t yData){
	uint16_t encoded = 0;

	// set type with first 2 bits only
	encoded |= ((type&(1 << 0) ? 1:0) << 0)
			| ((type&(1 << 1) ? 1:0) << 1);

	// put other data after it
	uint8_t i;
	for(i=0; i<7; i++){// 7 bits used to fit all in 16 bit var
		encoded |= ((xData&(1 << i) ? 1:0) << i+2);
		encoded |= ((yData&(1 << i) ? 1:0) << i+9);
	}

	return encoded;
}

// TODO: add receive/send buffer somehow
void IR_send(uint8_t type, uint8_t xData, uint8_t yData) {
	uint16_t data = IR_encode(type, xData, yData);

	uint8_t i;

	// make sure led is off
	IR_off();
	for(i=0;i<16;i++) {
		IR_on();
		if(data&(1 << i) ? 1:0){
			_delay_ms(10);
		}
		else {
			_delay_ms(5);
		}

		// space
		IR_off();
		_delay_ms(1);
	}
	IR_off();
}
