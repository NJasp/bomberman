#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <Wire.h>
#include <Arduino.h>
#include <MI0283QT9.h>

MI0283QT9 lcd;
uint8_t joy_x_axis, joy_y_axis, gridgrootte = 20, cirkelgrootte = (gridgrootte / 2) - 1, y = gridgrootte / 2, countX = 1, countY = 1, grid[12][16];
uint16_t x = gridgrootte / 2;

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

	// fill grid
	uint16_t gridCounter;
	uint8_t rowCounter;
	for(gridCounter = 0; gridCounter < 12; gridCounter++){
		for(rowCounter = 0; rowCounter < 16; rowCounter++){
			if(gridCounter == 0 || gridCounter == 11){
				grid[gridCounter][rowCounter] = 1;
			}
			else {
				grid[gridCounter][0] = 1;
				grid[gridCounter][15] = 1;
				break;
			}
		}
	}

	//	draw stuff in grid
	for(gridCounter = 0; gridCounter < 12; gridCounter++){
		for(rowCounter = 0; rowCounter < 16; rowCounter++){
			if(grid[gridCounter][rowCounter] == 1)
				lcd.fillRect(rowCounter*gridgrootte, gridCounter*gridgrootte, gridgrootte, gridgrootte, RGB(0,0,0));

		}
	}

	int b;
	for (gridCounter = 0; gridCounter <= lcd.lcd_width; gridCounter += gridgrootte) { // hier worden de lijnen van de grid getekend met de gedefineerde gridgrootte
		lcd.drawLine(0, gridCounter, lcd.lcd_width, gridCounter, RGB(0, 0, 0));
		lcd.drawLine(gridCounter, 0, gridCounter, lcd.lcd_width, RGB(0, 0, 0));
	}

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
		if (joy_x_axis > 140 /*&& (joy_y_axis <= 145 && joy_y_axis >= 115)*/) {
			countX++; //hier word de teller voor de X coordinaat verhoogt als de joystick naar rechts word gedrukt
		}
		if (joy_x_axis < 114 /*&& (joy_y_axis <= 145 && joy_y_axis >= 115)*/) {
			countX--; //hier word de teller voor de X coordinaat verlaagt als de joystick naar links word gedrukt. komt niet lager als 0
		}
		if (joy_y_axis > 140 /*&& (joy_x_axis <= 145 && joy_x_axis >= 115)*/) {
			countY--; //hier word de teller voor de Y coordinaat verlaagt als de joystick naar beneden word gedrukt
		}
		if (joy_y_axis < 114 /*&& (joy_x_axis <= 145 && joy_x_axis >= 115)*/) {
			countY++; //hier word de teller voor de Y coordinaat verhoogt als de joystick naar boven word gedrukt
		}

		if (countX != 1) {
			if (countX >= 2) { //deze code word uitgevoerd als er met de joystick naar rechts word gedrukt
				_delay_ms(10); // er is een delay nodig anders gaat het poppetje te snel over het scherm
				lcd.fillCircle(x, y, cirkelgrootte, RGB(255, 255, 255));
				lcd.fillCircle(x = x += gridgrootte, y, (gridgrootte / 2) - 1, RGB(255, 0, 0)); //hier word het poppetje daadwerkelijk getekend. elke keer als de joystick naar rechts word gedrukt, word het poppetje een hokje verder opnieuw getekend
				countX = 1; //hier worden de X coordinaat tellers weer gerest voor een volgend commando vanaf de joystick
			}
			else {
				if (countX <= 0 && x > gridgrootte) { //deze code word uitgevoerd als er met de joystick naar links word gedrukt
													  //als het bolletje helemaal naar links is verschoven op het scherm, stopt de uitvoer van deze code.
					_delay_ms(10); // er is een delay nodig anders gaat het poppetje te snel over het scherm
					lcd.fillCircle(x, y, cirkelgrootte, RGB(255, 255, 255));
					lcd.fillCircle(x = x -= gridgrootte, y, cirkelgrootte, RGB(255, 0, 0)); //hier wordt het poppetje daadwerkelijk getekend aan de hand van het formaat van de grid
					countX = 1; //hier worden de X coordinaat tellers weer gerest voor een volgend commando vanaf de joystick
				}
			}
		}
		if (countY != 1) {
			if (countY >= 2) {
				//lcd.fillCircle(x, y = y += 20, 10, RGB(255, 0, 0));	
				_delay_ms(10); // er is een delay nodig anders gaat het poppetje te snel over het scherm
				lcd.fillCircle(x, y, cirkelgrootte, RGB(255, 255, 255));
				lcd.fillCircle(x, y = y += gridgrootte, cirkelgrootte, RGB(255, 0, 0)); //hier wordt het poppetje daadwerkelijk getekend aan de hand van het formaat van de grid
				countY = 1; //hier worden de Y coordinaat tellers weer gerest voor een volgend commando vanaf de joystick
			}
			else {
				if (countY <= 0 && y > gridgrootte) {
					//lcd.fillCircle(x, y = y -= 20, 10, RGB(255, 0, 0));		
					_delay_ms(10); // er is een delay nodig anders gaat het poppetje te snel over het scherm
					lcd.fillCircle(x, y, cirkelgrootte, RGB(255, 255, 255));
					lcd.fillCircle(x, y = y -= gridgrootte, cirkelgrootte, RGB(255, 0, 0)); //hier wordt het poppetje daadwerkelijk getekend aan de hand van het formaat van de grid
					countY = 1; //hier worden de Y coordinaat tellers weer gerest voor een volgend commando vanaf de joystick
				}
			}
		}

		lcd.fillCircle(x, y, (gridgrootte / 2) - 1, RGB(255, 0, 0));

	}
	return 0;
}
