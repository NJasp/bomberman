#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <Wire.h>
#include <Arduino.h>
#include <MI0283QT9.h>

MI0283QT9 lcd;
uint8_t joy_x_axis, joy_y_axis;
uint16_t x = 10;
uint8_t y = 10, countX = 1, countY = 1;


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

	for (;;) {		
		// MAIN LOOP								
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
		if (joy_x_axis > 140 && (joy_y_axis <= 145 && joy_y_axis >= 115)) {
			countX++;
		}
		if (joy_x_axis < 114 && (joy_y_axis <= 145 && joy_y_axis >= 115)) {
			countX--;
		}
		if (joy_y_axis > 140 && (joy_x_axis <= 145 && joy_x_axis >= 115)) {
			countY--;
		}
		if (joy_y_axis < 114 && (joy_x_axis <= 145 && joy_x_axis >= 115)) {
			countY++;
		}

		for (gridCounter = 0; gridCounter <= lcd.lcd_width; gridCounter += 20) {
			lcd.drawLine(0, gridCounter, lcd.lcd_width, gridCounter, RGB(0, 0, 0));
			lcd.drawLine(gridCounter, 0, gridCounter, lcd.lcd_width, RGB(0, 0, 0));
		}

		if (countX != 1) {
			if (countX >= 2) {
				//lcd.fillCircle(x = x += 20, y, 10, RGB(255, 0, 0));
				_delay_ms(10);//Draw on screen with joystick variables
				lcd.fillCircle(x = x += 20, y, 10, RGB(255, 255, 255));
				countX = 1;
				countY = 1;
			}
			else {
				if (countX <= 0 && x > 20) {
					//lcd.fillCircle(x = x -= 20, y, 10, RGB(255, 0, 0));
					_delay_ms(10);//Draw on screen with joystick variables
					lcd.fillCircle(x = x -= 20, y, 10, RGB(255, 255, 255));
					countX = 1;
					countY = 1;
				}
			}
		}
		if (countY != 1) {
			if (countY >= 2) {
				//lcd.fillCircle(x, y = y += 20, 10, RGB(255, 0, 0));	
				_delay_ms(10);//Draw on screen with joystick variables
				lcd.fillCircle(x, y = y += 20, 10, RGB(255, 255, 255));
				countX = 1;
				countY = 1;
			}
			else {
				if (countY <= 0 && y > 20) {
					//lcd.fillCircle(x, y = y -= 20, 10, RGB(255, 0, 0));		
					_delay_ms(10);//Draw on screen with joystick variables
					lcd.fillCircle(x, y = y -= 20, 10, RGB(255, 255, 255));
					countX = 1;
					countY = 1;
				}
			}
		}

		lcd.fillCircle(x, y, 10, RGB(255, 0, 0));
		_delay_ms(10);
		lcd.fillCircle(x, y, 10, RGB(255, 255, 255));


	}
	return 0;
}

