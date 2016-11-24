#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <Wire.h>
#include <Arduino.h>
#include <MI0283QT9.h>

MI0283QT9 lcd;					//LCD variable
uint8_t joy_x_axis, joy_y_axis;	//Nunchuck Data
static uint8_t nunchuck_buf[6];	//Nunchuck Buffer
uint8_t gridgrootte = 20;	//Size of gridsquares
uint8_t grid[16][12];		//Griddata
uint8_t collumnCounter;		//collumnCounter
uint8_t rowCounter;			//rowCounter
uint8_t player1_x = 1, player1_y = 1;		//player locations
uint8_t cirkelgrootte = (gridgrootte / 2) - 1;	//Size of playercircle
uint8_t player1_x_Speed = 50, player1_y_Speed = 50, player1_xCounter = 0, player1_yCounter = 0;		//Player movement speed
uint8_t player1_x_old = 1, player1_y_old = 1;		//Old locations of the player;

void init_Hardware();
void init_OutsideWalls();
void draw_OutsideWalls();
void draw_Grid();
void view_Griddata();
void read_Nunchuck();
void calculate_Movement();
void draw_player();

int main() {
	init_Hardware();
	draw_Grid();
	init_OutsideWalls();
	view_Griddata();
	draw_OutsideWalls();
	for (;;) {	// MAIN LOOP									
		read_Nunchuck();
		calculate_Movement();
		draw_player();
	}
	return 0;
}

void init_Hardware()
{
	init();												//INITIALIZE (SETUP)
	lcd.begin(8);
	lcd.fillScreen(RGB(255, 255, 255));
	PORTC |= (1 << PORTC4) | (1 << PORTC5);

	Wire.begin();										//INITIALIZE NUNCHUCK                
	Wire.beginTransmission(0x52);
	Wire.write(0x40);
	Wire.write(0x00);
	Wire.endTransmission();
}

void init_OutsideWalls()
{
	for (rowCounter = 0; rowCounter < 12; rowCounter++) {
		for (collumnCounter = 0; collumnCounter < 16; collumnCounter++) {
			if (rowCounter == 0 || rowCounter == 11) {
				grid[collumnCounter][rowCounter] = 1;
			}
			else {
				grid[0][rowCounter] = 1;
				grid[15][rowCounter] = 1;
			}
		}
	}
}

void draw_OutsideWalls()
{
	//	draw stuff in grid
	for (rowCounter = 0; rowCounter < 12; rowCounter++) {
		for (collumnCounter = 0; collumnCounter < 16; collumnCounter++) {
			if (grid[collumnCounter][rowCounter] == 1)
				lcd.fillRect(collumnCounter*gridgrootte, rowCounter*gridgrootte, gridgrootte, gridgrootte, RGB(0, 0, 0));
		}
	}
}

void draw_Grid()
{
	int i;
	for (i = 0; i <= lcd.lcd_width; i += gridgrootte) {
		lcd.drawLine(i, 0, i, lcd.lcd_height, RGB(0, 0, 0));
	}
	for (i = 0; i <= lcd.lcd_height; i += gridgrootte) {
		lcd.drawLine(0, i, lcd.lcd_width, i, RGB(0, 0, 0));
	}
}

void view_Griddata()	//print the grid to serial
{
	Serial.begin(9600);
	int i = 0;
	for (rowCounter = 0; rowCounter < 12; rowCounter++) {
		for (collumnCounter = 0; collumnCounter < 16; collumnCounter++) {
			if (i < 15) {
				Serial.print(grid[collumnCounter][rowCounter]);
				i++;
			}
			else {
				Serial.println(grid[collumnCounter][rowCounter]);
				i = 0;
			}

		}
	}
}

void read_Nunchuck()
{
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
}

void calculate_Movement()
{
	if (joy_x_axis > 140) {
		if (player1_xCounter == player1_x_Speed) {
			player1_x++;	//hier word de teller voor de X coordinaat verhoogt als de joystick naar rechts word gedrukt
			player1_xCounter = 0;
		}
		else {
			player1_xCounter++;
		}
	}
	if (joy_x_axis < 114) {
		if (player1_xCounter == player1_x_Speed) {
			player1_x--; //hier word de teller voor de X coordinaat verlaagt als de joystick naar links word gedrukt. komt niet lager als 0
			player1_xCounter = 0;
		}
		else {
			player1_xCounter++;
		}
	}
	if (joy_y_axis > 140) {
		if (player1_yCounter == player1_y_Speed) {
			player1_y--;	//hier word de teller voor de Y coordinaat verlaagt als de joystick naar beneden word gedrukt
			player1_yCounter = 0;
		}
		else {
			player1_yCounter++;
		}
	}
	if (joy_y_axis < 114) {
		if (player1_yCounter == player1_y_Speed) {
			player1_y++;	//hier word de teller voor de Y coordinaat verhoogt als de joystick naar boven word gedrukt
			player1_yCounter = 0;
		}
		else {
			player1_yCounter++;
		}
	}
}

void draw_player()
{
	if(player1_y_old != player1_y || player1_x_old != player1_x)
		lcd.fillCircle((player1_x_old*gridgrootte) + (gridgrootte / 2), (player1_y_old*gridgrootte) + (gridgrootte / 2), cirkelgrootte, RGB(255, 255, 255));

	lcd.fillCircle((player1_x*gridgrootte) + (gridgrootte / 2), (player1_y*gridgrootte) + (gridgrootte / 2), cirkelgrootte, RGB(255, 0, 0));
	player1_x_old = player1_x;
	player1_y_old = player1_y;
}
