#include "Libraries/Levels/Levels.h"
#include "Libraries/LCD/LCD.h"
#include "Libraries/Nunchuck/Nunchuck.h"
#include "Libraries/DebugTools/DebugTools.h"
#include "Libraries/Player/Player.h"
#include "Libraries/Bomb/Bomb.h"

MI0283QT9 lcd;					//LCD variablen
uint8_t joy_x_axis, joy_y_axis;	//Nunchuck Data
static uint8_t nunchuck_buf[6];	//Nunchuck Buffer
uint8_t gridgrootte = 20;	//Size of gridsquares
uint8_t grid[16][12];		//Griddata
uint8_t collumnCounter;		//collumnCounter
uint8_t rowCounter;			//rowCounter
uint8_t player1_x = 1, player1_y = 1;		//player locations
uint8_t cirkelgrootte = (gridgrootte / 2) - 1;	//Size of playercircle
uint8_t player1_xCounter = 0, player1_yCounter = 0;		//Player movement speed
uint8_t player1_x_old = 1, player1_y_old = 1;		//Old locations of the player;
uint8_t player1_x_bombdrop = 0, player1_y_bombdrop = 0;		//Location of the dropped bomb;
uint8_t antiholdCounter = 0;				// 1 when the player holds the 'Z' button, so the game doesn't place too many bombs
uint8_t activeBombs[16][12];
uint16_t interruptCounter = 0;

void draw_Player();
void draw_Bomb();
void calculate_Movement();
void check_Bomb();

int main() {
	init();
	init_Level1(grid);
	init_LCD(lcd);
	init_Nunchuck();
	init_Timer();
	draw_Grid(lcd);
	draw_OutsideWalls(lcd, grid);
	for (;;) {	// MAIN LOOP									
		read_Nunchuck(nunchuck_buf, &joy_x_axis, &joy_y_axis);
		calculate_Movement();
		check_Bomb();
		draw_Player();
		draw_Bomb();
	}
	return 0;
}

void init_Timer() {
	TIMSK2 |= (1 << TOIE2);
	TCNT2 = 0;										//SET TIMER 2 AAN (Prescaling 1/1024)
	TCCR2B |= (1 << CS20) | (1 << CS22) | (1 << CS21);
	sei();
}

ISR(TIMER2_OVF_vect) {		//prescaler 1/1024 = 60 count voor ongeveer 1 seconde
	if (interruptCounter >= 60) {
		for (rowCounter = 0; rowCounter < 12; rowCounter++) {
			for (collumnCounter = 0; collumnCounter < 16; collumnCounter++) {
				if (activeBombs[collumnCounter][rowCounter] > 1) {
					activeBombs[collumnCounter][rowCounter]--;
				}
				else if (activeBombs[collumnCounter][rowCounter] == 1) {
					grid[collumnCounter][rowCounter] = 0;
				}
			}
		}
		interruptCounter = 0;
	}
	else {
		interruptCounter++;
	}
}

void calculate_Movement()
{
	if (joy_x_axis > 140) {
		if (player1_xCounter == 10) {
			if (!(grid[player1_x + 1][player1_y])) {
				player1_x++;	//hier word de teller voor de X coordinaat verhoogt als de joystick naar rechts word gedrukt
				player1_xCounter = 0;
			}
			else {
				player1_x = player1_x_old;
			}
		}
		else {
			player1_xCounter++;
		}
	}
	if (joy_x_axis < 114) {
		if (player1_xCounter == 10) {
			if (!(grid[player1_x - 1][player1_y])) {
				player1_x--; //hier word de teller voor de X coordinaat verlaagt als de joystick naar links word gedrukt. komt niet lager als 0
				player1_xCounter = 0;
			}
			else {
				player1_x = player1_x_old;
			}
		}
		else {
			player1_xCounter++;
		}
	}
	if (joy_y_axis > 140) {
		if (player1_yCounter == 10) {
			if (!(grid[player1_x][player1_y - 1])) {
				player1_y--;	//hier word de teller voor de Y coordinaat verlaagt als de joystick naar beneden word gedrukt
				player1_yCounter = 0;
			}
			else {
				player1_y = player1_y_old;
			}
		}
		else {
			player1_yCounter++;
		}
	}
	if (joy_y_axis < 114) {
		if (player1_yCounter == 10) {
			if (!(grid[player1_x][player1_y + 1])) {
				player1_y++;	//hier word de teller voor de Y coordinaat verhoogt als de joystick naar boven word gedrukt
				player1_yCounter = 0;
			}
			else {
				player1_y = player1_y_old;
			}
		}
		else {
			player1_yCounter++;
		}
	}
}

void check_Bomb()
{
	if (!((nunchuck_buf[5] >> 0) & 1)) {
		if (antiholdCounter != 1) {
			grid[player1_x][player1_y] = 2;
			activeBombs[player1_x][player1_y] = 5;
			antiholdCounter = 1;
			player1_x_bombdrop = player1_x;
			player1_y_bombdrop = player1_y;
		}	
	}
	else {
		antiholdCounter = 0;
	}
}

void draw_Player()
{
	if(player1_y_old != player1_y || player1_x_old != player1_x)
			lcd.fillCircle((player1_x_old*gridgrootte) + (gridgrootte / 2), (player1_y_old*gridgrootte) + (gridgrootte / 2), cirkelgrootte, RGB(255, 255, 255));
			lcd.fillCircle((player1_x*gridgrootte) + (gridgrootte / 2), (player1_y*gridgrootte) + (gridgrootte / 2), cirkelgrootte, RGB(255, 0, 0));
			player1_x_old = player1_x;
			player1_y_old = player1_y;
}

void draw_Bomb()
{
	if (((player1_x_bombdrop) != 0 && (player1_y_bombdrop != 0)) && ((player1_x != player1_x_bombdrop) || (player1_y != player1_y_bombdrop))) {
		lcd.fillRect(((player1_x_bombdrop*gridgrootte) + 4), ((player1_y_bombdrop*gridgrootte) + 4), 14, 14, RGB(180, 0, 0));
		player1_x_bombdrop = 0;
		player1_y_bombdrop = 0;
	}
}


