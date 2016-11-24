#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <ir.h>
volatile uint8_t timer = 0, clock = 0;
volatile uint8_t recTimer;
volatile uint16_t data = 0, timeDelta;
volatile uint8_t dataCount = 0;

ISR(TIMER2_OVF_vect) {
	timer++;
	if(timer == 8){ // Close enough to work as ms counter, 7.8 precise
		clock++;
		timer = 0;
	}
}

ISR(INT0_vect){
	//Serial.println(PINB&(1 << PINB3) ? 1:0);

	if(recTimer > clock)
		timeDelta = 256+clock - recTimer;
	else
		timeDelta = clock - recTimer;

	//if (timeDelta > 20) 				   // begin new transmission
	//	dataCount = 0;

	if(timeDelta > 3 && timeDelta < 14) {
		Serial.print(dataCount);
		//Serial.println(" == interrupt ===");

		if (timeDelta > 7 && timeDelta < 12) 	   // recieved 1
			data |= (1 << dataCount);
		else if (timeDelta < 8 && timeDelta > 3)   // recieved 0
			data &= ~(1 << dataCount);
		dataCount++;
	}



	recTimer = clock;

}

int main(){
	Serial.begin(9600);
	IR_init();
	uint16_t testData = IR_encode(3,122,122);
	Serial.print("test: ");
	Serial.println(IR_decode(testData).type);
	Serial.println(IR_decode(testData).xData);
	Serial.println(IR_decode(testData).yData);

	for(;;){
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
	}
	return 0;
}
