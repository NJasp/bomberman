#include "Libraries/Levels/Levels.h"
#include "Libraries/LCD/LCD.h"
#include "Libraries/Nunchuck/Nunchuck.h"
#include "Libraries/DebugTools/DebugTools.h"
#include "Libraries/Player/Player.h"
#include "Libraries/Bomb/Bomb.h"

MI0283QT9 lcd;					//LCD variabele
uint8_t joy_x_axis, joy_y_axis;	//Nunchuck Data
static uint8_t nunchuck_buf[6];	//Nunchuck Buffer
uint8_t grid[16][12];		//Griddata
uint8_t collumnCounter;		//collumnCounter
uint8_t rowCounter;			//rowCounter
uint8_t player1_x = 1, player1_y = 1;		//player locations
uint8_t player1_xCounter = 0, player1_yCounter = 0;		//Player movement speed
uint8_t player1_x_old = 1, player1_y_old = 1;		//Old locations of the player;
uint8_t player1_x_bombdrop = 0, player1_y_bombdrop = 0;		//Location of the dropped bomb;
uint8_t antiholdCounter = 0;				// 1 when the player holds the 'Z' button, so the game doesn't place too many bombs
uint8_t interruptCounter = 0;				//used to count seconds in the interrupt
uint8_t livebombs = 0;

uint8_t bombradius = 1;
uint8_t player1_x_speed = 20, player1_y_speed = 20; //Higher is slower
uint8_t max_bombs = 1;

void init_Timer();

int main() {
	init();
	init_Testlevel(grid);
	init_LCD(lcd);
	init_Nunchuck();
	init_Timer();
	//draw_Grid(lcd);
	//view_Griddata(grid);
	draw_Walls_Crates(lcd, grid);
	for (;;) {	// MAIN LOOP									
		read_Nunchuck(nunchuck_buf, &joy_x_axis, &joy_y_axis);
		calculate_Movement(&player1_x, &player1_y, joy_x_axis, joy_y_axis, &player1_xCounter, &player1_yCounter, player1_x_speed, player1_y_speed, grid);
		check_Bomb(player1_x, player1_y, &player1_x_bombdrop, &player1_y_bombdrop, max_bombs, &livebombs, &antiholdCounter, nunchuck_buf, grid);
		draw_Player(player1_x, player1_y, &player1_x_old, &player1_y_old, lcd);
		draw_Bomb(player1_x, player1_y, &player1_x_bombdrop, &player1_y_bombdrop, lcd);
		draw_Explosion(lcd, bombradius, grid, &livebombs);
		clear_Explosion(lcd, bombradius, grid);
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
	if (interruptCounter >= 30) {
		for (rowCounter = 0; rowCounter < 12; rowCounter++) {
			for (collumnCounter = 0; collumnCounter < 16; collumnCounter++) {
				if ((grid[collumnCounter][rowCounter] > 3 && grid[collumnCounter][rowCounter] < 7) || (grid[collumnCounter][rowCounter] > 7 && grid[collumnCounter][rowCounter] < 10)) {
					grid[collumnCounter][rowCounter]--;
				}
			}
		}
		interruptCounter = 0;
	}
	else {
		interruptCounter++;
	}
}





