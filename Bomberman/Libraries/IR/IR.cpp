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
		if(isSending_IR()) {
			processSend_IR(nTimer);
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
init_IR();								   // initialize timers/config

send_IR(type, xData, yData);			   // send data

data_store myData = decode_IR(data);	   // store received data in struct
										   // data is now accessible through myData.type, myData.xData, myData.yData
*/

#include "Includes.h"
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
	isOn=0;
	isSending=0;
	sendSpace=0;
	dataReady=0;

	// send random junk
	uint8_t i;
	for (i = 0; i < 255; ++i) {
		on_IR();
		off_IR();
	}
}

void toggle_IR() {
	// wire for test reasons
	//PORTB ^= (1 << PORTB5);
	isOn ^= 1;
	DDRD ^= (1 << PORTD3);
}

void off_IR() {
	// wire for test reasons
	//PORTB &= ~(1 << PORTB5);
	isOn = 0;
	DDRD &= ~(1 << PORTD3);
}

void on_IR() {
	// wire for test reasons
	//PORTB |= (1 << PORTB5);
	isOn = 1;
	DDRD |= (1 << PORTD3);
}

uint8_t isOn_IR(){
	return isOn;
}

uint8_t isSending_IR(){
	return isSending;
}

uint8_t dataReady_IR() {
	return dataReady;
}

data_store decode_IR(uint16_t data) {
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

uint16_t encode_IR(uint8_t type, uint8_t xData, uint8_t yData){
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

void processRecieve_IR(uint32_t currentTime, uint16_t *data) {
	if(currentTime >= lastTime)
		timeDelta = currentTime - lastTime;
	else // failsafe for timer overflow, if it ever happens
		timeDelta = 4294967295+currentTime - lastTime;

	lastTime = currentTime;

	if (timeDelta > 200){
		dataCount = 0;
		dataReady = 0;
	}

	if(timeDelta > ZERO_DELAY-DELAY_OFFSET && timeDelta < ONE_DELAY+DELAY_OFFSET) {
		if(dataReady)
			dataReady = 0;

		if (timeDelta > ONE_DELAY-DELAY_OFFSET && timeDelta < ONE_DELAY+DELAY_OFFSET) 	 	   // recieved 1
			*data |= (1 << dataCount);
		else if (timeDelta > ZERO_DELAY-DELAY_OFFSET && timeDelta < ZERO_DELAY+DELAY_OFFSET)   // recieved 0
			*data &= ~(1 << dataCount);

		if(dataCount<=15)
			dataReady=1;

		dataCount++;
	}

}

void processSend_IR(uint32_t currentTime) {
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
		if(currentTime == nextSend && isOn_IR()) {
			off_IR();
			sendSpace = 1;
		}

		if(nextSend == 0) {// set delay based on 1|0
			if(((msgData >> msgCount)&1))
				nextSend = currentTime + ONE_DELAY;
			else
				nextSend = currentTime + ZERO_DELAY;

			on_IR();
			msgCount++;
		}
	}

	if(msgCount == 17) {// end sending
		off_IR();
		msgCount = 0;
		isSending = 0;
		sendSpace = 0;
		nextSend = 0;
	}

}
// TODO: add receive/send buffer somehow
void send_IR(uint8_t type, uint8_t xData, uint8_t yData) {
	msgData = encode_IR(type, xData, yData);
	isSending = 1;
}
