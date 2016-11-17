#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <Wire.h>
#include <Arduino.h>
#include <MI0283QT9.h>

MI0283QT9 lcd;
int joy_x_axis, joy_y_axis;

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

		joy_x_axis = map(joy_x_axis, 28, 231, 0, 320);					//re-map the values to screen height and width
		joy_y_axis = map(joy_y_axis, 33, 228, 240, 0);

		lcd.fillCircle(joy_x_axis, joy_y_axis, 5, RGB(255, 0, 0));			//Draw on screen with joystick variables
		lcd.fillCircle(joy_x_axis, joy_y_axis, 5, RGB(255, 255, 255));
	}
	return 0;
}

