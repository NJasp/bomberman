#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <Wire.h>
#include <Arduino.h>
#include <MI0283QT9.h>

MI0283QT9 lcd;
int blockArrayX[5000] = {};
int blockArrayY[5000] = {};
int a = 10, b = 10, c = 10, d = 10;
uint8_t joy_x_axis, joy_y_axis;
uint16_t x = 10;
uint8_t y = 10;


static uint8_t nunchuck_buf[6];

int main() {
	init();												//INITIALIZE (SETUP)
	lcd.begin(8);
	lcd.fillScreen(RGB(255, 255, 255));
	lcd.setOrientation(0);
	DDRC |= (1 << PORTC5) | (1 << PORTC4);
	PORTC |= (1 << PORTC4) | (1 << PORTC5);

	Wire.begin();										//INITIALIZE NUNCHUCK                
	Wire.beginTransmission(0x52);
	Wire.write(0x40);
	Wire.write(0x00);
	Wire.endTransmission();

	// draw grid
	uint16_t gridCounter;
	int count;
	for(gridCounter = 0; gridCounter <= lcd.lcd_width; gridCounter+=20){
		lcd.drawLine(0, gridCounter, lcd.lcd_width, gridCounter, RGB(0, 0, 0));
		blockArrayX[count] = gridCounter;
		lcd.drawLine(gridCounter, 0, gridCounter, lcd.lcd_width, RGB(0, 0, 0));
		blockArrayY[count] = gridCounter;
		count++;
	}

	for (;;) {											// MAIN LOOP								
		int i = 0;
		Wire.requestFrom(0x52, 6);						//READ NUNCHUCK
		while (Wire.available()) {
			nunchuck_buf[i] = (Wire.read() ^ 0x17) + 0x17;;
			i++;
		}
		Wire.beginTransmission(0x52);
		Wire.write(0x00);
		Wire.endTransmission();
		joy_x_axis = nunchuck_buf[0];
		joy_y_axis = nunchuck_buf[1];
		if (joy_x_axis > 132 && (joy_y_axis <= 170 && joy_y_axis >= 90)) {
			x = blockArrayX[a];
			a++;
				
		}
		if (joy_x_axis < 122 && (joy_y_axis <= 170 && joy_y_axis >= 90)) {
			x = blockArrayX[b - 1];
			b++;
		}
		if (joy_y_axis > 132 && (joy_x_axis <= 170 && joy_x_axis >= 90)) {
			y = blockArrayY[c-1];
			c++;
		}
		if (joy_y_axis < 122 && (joy_x_axis <= 170 && joy_x_axis >= 90)) {
			y = blockArrayY[c];
			c++;
		}

		lcd.fillCircle(x, y, 10, RGB(255, 0, 0));			//Draw on screen with joystick variables
		//_delay_ms(10);
		lcd.fillCircle(x, y, 10, RGB(255, 255, 255));
	}
	return 0;
}

