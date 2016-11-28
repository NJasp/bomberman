/*
       ==============================================
                        implementaton:
       ===================----=======================
                   ===== interrupts =====
ISR(TIMER2_COMPA_vect){// 10 nano second timer
	nTimer++;

	// send function
	if(IR_isSending()) {
		IR_processSend(nTimer);
	}

}

ISR(INT0_vect){ // receive interrupt
	IR_processRecieve(nTimer, &IRdata);
}

               ===== sending/handling data =====
IR_init();								   // initialize timers/config

IR_send(type, xData, yData);			   // send data

data_store myData = IR_decode(data);	   // store received data in struct
										   // data is now accessible through myData.type, myData.xData, myData.yData
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "ir.h"
volatile uint8_t isOn = 0, isSending = 0, sendSpace = 0;
volatile uint16_t timeDelta = 0;
volatile uint32_t lastTime = 0, nextSend = 0;
volatile uint8_t dataCount = 0, msgCount = 0, spaceCounter = 0;
volatile uint16_t msgData;

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


	TIMSK2 |= (1 << TOIE2) | (1 << OCIE2A);		// enable overflow interrupt
	OCR2A = 2;					// nanosecond counter
	IR_off();

	sei();						// enable global interrupts
}

void IR_toggle() {
	isOn ^= 1;
	// just use wire for test reasons
	PORTB ^= (1 << PORTB5);

	DDRD ^= (1 << PORTD3);
}

void IR_off() {
	isOn = 0;
	// just use wire for test reasons
	PORTB &= ~(1 << PORTB5);

	DDRD &= ~(1 << PORTD3);
}

void IR_on() {
	isOn = 1;
	// just use wire for test reasons
	PORTB |= (1 << PORTB5);

	DDRD |= (1 << PORTD3);
}

uint8_t IR_isOn(){
	return isOn;
}

uint8_t IR_isSending(){
	return isSending;
}

data_store IR_decode(uint16_t data) {
	data_store returnData = {0,0,0};

	// fill first 2 bits to get number back
	returnData.type |= (data&1) | (((data >> 1)&1) << 1);

	// fill data variables
	uint8_t i;
	for(i=0; i<7; i++){// 7 bits used to fit all in 16 bit var
		returnData.xData |= (((data >> i+2)&1) << i);
		returnData.yData |= (((data >> i+9)&1) << i);
	}
	return returnData;
}

uint16_t IR_encode(uint8_t type, uint8_t xData, uint8_t yData){
	uint16_t encoded = 0;

	// set type with first 2 bits only
	encoded |= (type&1) | (((type >> 1)&1) << 1);

	// put other data after it
	uint8_t i;
	for(i=0; i<7; i++){// 7 bits used to fit all in 16 bit var
		encoded |= (((xData >> i)&1) << i+2);
		encoded |= (((yData >> i)&1) << i+9);
	}

	return encoded;
}

void IR_processRecieve(uint32_t currentTime, uint16_t *data) {
	timeDelta = currentTime - lastTime;
	lastTime = currentTime;

	if (timeDelta > 200) 				   // begin new transmission
		dataCount = 0;

	if(timeDelta > ZERO_DELAY-20 && timeDelta < ONE_DELAY+20) {
		if (timeDelta > ONE_DELAY-20 && timeDelta < ONE_DELAY+20) 	 	   // recieved 1
			*data |= (1 << dataCount);
		else if (timeDelta > ZERO_DELAY-20 && timeDelta < ZERO_DELAY+20)   // recieved 0
			*data &= ~(1 << dataCount);
		dataCount++;
	}

}

void IR_processSend(uint32_t currentTime) {
	if(sendSpace) {  // send space | do nothing one cycle while IR is off
		if(spaceCounter == SPACE_DELAY){
			sendSpace = 0;
			nextSend = 0;
			spaceCounter = 0;
		}
		spaceCounter++;
	}
	else {	       // send bit
		// send 1|0
		if(currentTime == nextSend && IR_isOn()) {
			IR_off();
			sendSpace = 1;
		}

		if(nextSend == 0) {// set delay based on 1|0
			if(((msgData >> msgCount)&1))
				nextSend = currentTime + ONE_DELAY;
			else
				nextSend = currentTime + ZERO_DELAY;

			IR_on();
			msgCount++;
		}
	}

	if(msgCount == 17) {// end sending
		IR_off();
		msgCount = 0;
		isSending = 0;
		sendSpace = 0;
		nextSend = 0;
	}

}
// TODO: add receive/send buffer somehow
void IR_send(uint8_t type, uint8_t xData, uint8_t yData) {
	msgData = IR_encode(type, xData, yData);
	isSending = 1;
}
