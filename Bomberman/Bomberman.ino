#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <Wire.h>
#include <Arduino.h>
#include <MI0283QT9.h>

//comment 2

MI0283QT9 lcd;
int joy_x_axis, joy_y_axis;
uint8_t teller = 0;
volatile uint8_t seconden = 0;



static uint8_t nunchuck_buf[6];

int main() {

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
		lcd.drawLine(0, joy_y_axis, 320, joy_y_axis, RGB(0, 0, 0));
		lcd.drawLine(joy_x_axis, 0, joy_x_axis, 240, RGB(0, 0, 0));
		lcd.drawText(5, 230, "Time: ", RGB(0, 0, 0), RGB(255, 255, 255), 1);
		lcd.drawInteger(50, 230, seconden, DEC, RGB(0, 0, 0), RGB(255, 255, 255), 1);
		delay(25);
		lcd.fillCircle(joy_x_axis, joy_y_axis, 5, RGB(255, 255, 255));
		lcd.drawLine(0, joy_y_axis, 320, joy_y_axis, RGB(255, 255, 255));
		lcd.drawLine(joy_x_axis, 0, joy_x_axis, 240, RGB(255, 255, 255));
	}
	return 0;
}

