#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <Wire.h>
#include <MI0283QT9.h>

MI0283QT9 lcd;
uint8_t joy_x_axis, joy_y_axis;
uint16_t x = 160;
uint8_t y = 120;


static uint8_t nunchuck_buf[6];

int main() {											//INITIALIZE (SETUP)
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
	for(gridCounter = 0; gridCounter <= lcd.lcd_width; gridCounter+=15){
		lcd.drawLine(0, gridCounter, lcd.lcd_width, gridCounter, RGB(0, 255, 0));
		lcd.drawLine(gridCounter, 0, gridCounter, lcd.lcd_width, RGB(0,255,0));
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
		if (joy_x_axis > 132) {
			x++;
		}
		if (joy_x_axis < 122) {
			x--;
		}
		if (joy_y_axis > 132) {
			y--;
		}
		if (joy_y_axis < 122) {
			y++;
		}

		lcd.fillCircle(x, y, 5, RGB(255, 0, 0));			//Draw on screen with joystick variables
		lcd.fillCircle(x, y, 5, RGB(255, 255, 255));
	}
	return 0;
}

