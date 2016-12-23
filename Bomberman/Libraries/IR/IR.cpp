/*
==============================================
implementaton:
===================----=======================
===== interrupts =====
ISR(TIMER2_COMPA_vect){// timer for receiving/sending

tTimer++;
if(tTimer == 10){
nTimer++;
// send function
if(isSendingIR) {
processSend_IR(nTimer, &isSendingIR);
}
tTimer = 0;
}

// ms timer
timer++;
if(timer == 179){
clock++;
timer = 0;
}

}

ISR(INT0_vect){ // receive interrupt
processRecieve_IR(nTimer, &IRdata);
}
***ms timer optional/but probably useful

===== sending/handling data =====
uint8_t isSendingIR = 0; 					// local value for keeping track of sending or not
init_IR();								   // initialize timers/config

send_IR(&isSendingIR, type, xData, yData);			   // send data

data_store myData = decode_IR(data);	   // store received data in struct
// data is now accessible through myData.type, myData.xData, myData.yData
*/

#include "../Includes/Includes.h"
#include "IR.h"
volatile uint8_t isOn = 0, isSending = 0, sendSpace = 0, dataReady = 0;
volatile uint16_t timeDelta = 0;
volatile uint32_t lastTime = 0, nextSend = 0;
volatile uint16_t dataCount = 0, msgCount = 0, spaceCounter = 0;
volatile uint16_t msgData;

void init_IR() {
	DDRD &= ~(1 << PORTD2);		// input INT0 pin (pin 2)
	PORTD |= (1 << PORTD2);		// pullup INT0 pin
	EIMSK |= (1 << INT0);		// enable INT0
	EICRA |= (1 << ISC00);		// any change generates interrupt INT0

								// wire for test reasons
								//DDRB |= (1 << PORTB5);

	DDRD |= (1 << PORTD3);		// output OC2B pin (pin 3)

								// send random junk
	uint8_t i;
	for (i = 0; i < 255; ++i) {
		DDRD |= (1 << PORTD3);
		DDRD &= ~(1 << PORTD3);
	}
}

uint8_t dataReady_IR() {
	return dataReady;
}

data_store decode_IR(uint16_t data) {
	data_store returnData = { 0,0,0 };

	// fill first 2 bits to get number back
	returnData.type |= (data & 1) | (((data >> 1) & 1) << 1);

	// fill data variables
	uint8_t i;
	for (i = 0; i<7; i++) {// 7 bits used to fit all in 16 bit var
		returnData.xData |= (((data >> i + 2) & 1) << i);
		returnData.yData |= (((data >> i + 9) & 1) << i);
	}
	return returnData;
}

uint16_t encode_IR(uint8_t type, uint8_t xData, uint8_t yData) {
	uint16_t encoded = 0;

	// set type with first 2 bits only
	encoded |= (type & 1) | (((type >> 1) & 1) << 1);

	// put other data after it
	uint8_t i;
	for (i = 0; i<7; i++) {// 7 bits used to fit all in 16 bit var
		encoded |= (((xData >> i) & 1) << i + 2);
		encoded |= (((yData >> i) & 1) << i + 9);
	}

	return encoded;
}

void processRecieve_IR(uint32_t currentTime, volatile uint16_t *data, volatile uint8_t* interruptCounter) {
	if (currentTime >= lastTime)
		timeDelta = currentTime - lastTime;
	else // failsafe for timer overflow, if it ever happens
		timeDelta = 4294967295 + currentTime - lastTime;

	lastTime = currentTime;

	if (timeDelta > 200) {
		dataCount = 0;
		dataReady = 0;
	}

	if (timeDelta > ZERO_DELAY - DELAY_OFFSET && timeDelta < ONE_DELAY + DELAY_OFFSET) {
		if (dataReady)
			dataReady = 0;

		if (timeDelta > ONE_DELAY - DELAY_OFFSET && timeDelta < ONE_DELAY + DELAY_OFFSET) 	 	   // recieved 1
			*data |= (1 << dataCount);
		else if (timeDelta > ZERO_DELAY - DELAY_OFFSET && timeDelta < ZERO_DELAY + DELAY_OFFSET)   // recieved 0
			*data &= ~(1 << dataCount);

		if (dataCount <= 15){
			dataReady = 1;
			*interruptCounter = 50;
		}

		dataCount++;
	}

}

void processSend_IR(uint32_t currentTime, volatile uint8_t *isSending) {
	if (sendSpace) {  // send space | do nothing one cycle while IR is off
		if (spaceCounter == SPACE_DELAY) {
			sendSpace = 0;
			nextSend = 0;
			spaceCounter = 0;
		}
		spaceCounter++;
	}
	else {	       // send bit
				   // send 1|0
		if (currentTime == nextSend && isOn) {
			// turn IR off
			isOn = 0;
			DDRD &= ~(1 << PORTD3);
			sendSpace = 1;
		}

		if (nextSend == 0) {// set delay based on 1|0
			if (((msgData >> msgCount) & 1))
				nextSend = currentTime + ONE_DELAY;
			else
				nextSend = currentTime + ZERO_DELAY;

			// turn IR on
			isOn = 1;
			DDRD |= (1 << PORTD3);
			msgCount++;
		}
	}

	if (msgCount == 17) {// end sending
						 // turn IR on
		isOn = 0;
		DDRD &= ~(1 << PORTD3);
		msgCount = 0;
		*isSending = 0;
		sendSpace = 0;
		nextSend = 0;
	}

}

void send_IR(volatile uint8_t *isSending, uint8_t type, uint8_t xData, uint8_t yData) {
	msgData = encode_IR(type, xData, yData);
	*isSending = 1;
}

uint8_t processMenuData_IR(uint8_t* stage, uint8_t* level, volatile uint16_t* IRdata, uint8_t* isPressed) {
	data_store menuData = decode_IR(*IRdata);

	if(menuData.type == LEVEL) {
		if(menuData.xData == 127) { // normal level
			*isPressed = 0;
			*level = menuData.yData;
			*stage = 2;
			return 1;
		}
		else { // TODO: random level
			*level = 5;
			*stage = 2;
			return 1;
		}
	}
	return 0;
}
