#include "Libraries/Levels/Levels.h"
#include "Libraries/LCD/LCD.h"
#include "Libraries/Nunchuck/Nunchuck.h"
#include "Libraries/DebugTools/DebugTools.h"
#include "Libraries/Player/Player.h"
#include "Libraries/Bomb/Bomb.h"
#include "Libraries/MSD_shield/mSD_shield.h"
#include "Libraries/IR/IR.h"
#include "Libraries/Hit/checkHit.h"
#include "Libraries/Menu/Menu.h"

MI0283QT9 lcd;					//LCD variabele
char *wall_Type = "wall3.bmp";
char *crate_Type = "crate3.bmp";
char *level = "level-1";
char *level = "test";
char *player1 = "1-grey.bmp";
char *bom = "bomGREY.bmp";
char *explosion = "ex.bmp";
uint8_t joy_x_axis, joy_y_axis;	//Nunchuck Data
static uint8_t nunchuck_buf[6];	//Nunchuck Buffer
uint8_t grid[16][12];		//Griddata
uint8_t collumnCounter;		//collumnCounter
uint8_t rowCounter;			//rowCounter
uint8_t player1_x = 0, player1_y = 0;		//player locations
uint8_t player2_x = 14, player2_y = 10;
uint8_t player1_xCounter = 0, player1_yCounter = 0;		//Player movement speed
uint8_t player2_x_old = 0, player2_y_old = 0;
uint8_t player1_x_old = 0, player1_y_old = 0;		//Old locations of the player;
uint8_t player1_x_bombdrop = 0, player1_y_bombdrop = 0;		//Location of the dropped bomb;
uint8_t antiholdCounter = 0;				// 1 when the player holds the 'Z' button, so the game doesn't place too many bombs
uint16_t interruptCounter = 0;				//used to count seconds in the interrupt
uint8_t livebombs = 0;
uint16_t IRdata;
uint32_t nTimer = 0;
uint8_t hit = 0;
uint8_t counter = 0;
uint16_t touchx = 0, touchy = 0;
uint8_t menucounter = 0;


uint8_t bombradius = 5;
uint8_t player1_x_speed = 0, player1_y_speed = 0; //Higher is slower
data_store player2_data;
uint8_t max_bombs = 5;
uint8_t score = 0;
uint8_t lives = 2;
uint8_t livescheck = 5;
uint8_t hitCounter = 0;

void init_Timer();

int main() {
	init();
	Serial.begin(9600);
	init_LCD(lcd);
	lcd.touchStartCal();
	startScherm(lcd);
	for (;;)
	{
		touchx = lcd.touchX();
		touchy = lcd.touchY();
		if (menucounter == 0 && lcd.touchRead()) {
			menuScherm(lcd);
			menucounter++;
		}
		if (menucounter == 1 && lcd.touchRead()) {
			if (touchx >= 80 && touchx <= 240 && touchy >= 40 && touchy <= 90) {
				levelSelect(lcd);
				menucounter++;
			}
			else if (touchx >= 65 && touchx <= 270 && touchy >= 160 && touchy <= 210)
			{
				options(lcd);
				menucounter++;
			}
		}
		if (menucounter == 2 && lcd.touchRead()) {
			if (touchx >= 20 && touchx <= 120 && touchy >= 60 && touchy <= 90) {
				level = "level-1";
				break;
			}
		}
	}
	init_Timer();
	init_IR();
	init_Nunchuck();
	init_SDcart(lcd);
	init_Player(player1_x, player1_y, lcd, player1);
	//draw_Grid(lcd);
	//view_Griddata(grid);
	init_Level(grid, level, &player1_x, &player1_y, &player1_x_old, &player1_y_old);
	draw_Walls_Crates(lcd, grid, wall_Type, crate_Type);
	for (;;) {	// MAIN LOOP	
		read_Nunchuck(nunchuck_buf, &joy_x_axis, &joy_y_axis);
		calculate_Movement(&player1_x, &player1_y, joy_x_axis, joy_y_axis, &player1_xCounter, &player1_yCounter, player1_x_speed, player1_y_speed, grid);
		if (dataReady_IR() == 1) {
			player2_data = decode_IR(IRdata);
		}
		check_Bomb(player1_x, player1_y, &player1_x_bombdrop, &player1_y_bombdrop, max_bombs, &livebombs, &antiholdCounter, nunchuck_buf, grid);
		draw_Player(player1_x, player1_y, &player1_x_old, &player1_y_old, lcd, player1);
		//lcd.fillCircle(player2_data.xData, player2_data.yData, 10, RGB(0, 0, 255));
		draw_Bomb(player1_x, player1_y, &player1_x_bombdrop, &player1_y_bombdrop, lcd, bom);
		draw_Explosion(lcd, bombradius, grid, &livebombs, &score, explosion,&hit,player1_x,player1_y);
		updateLives(&hit, &lives, lcd, score);
		clear_Explosion(lcd, bombradius, grid);
		updateLives(&hit, &lives, lcd, score);
	}
	return 0;
}

void init_Timer() {
	TCCR2A = 0;
	TCCR2B = 0;
	TIMSK2 = 0;
	TCCR2A = (1 << COM2B0); 	// toggle OC2A on match
	TCCR2B |= (1 << CS21); 		// 8 prescaler		
	TIMSK2 |= (1 << TOIE2) | (1 << OCIE2A);		// enable overflow interrupt|
	OCR2B = 53; 				// value to compare timer against	| 1/(53*(1/16000000)*8) = 37,7kHz
	OCR2A = 2;								// nanosecond counter
	TCNT2 = 0;										//SET TIMER 2 AAN (Prescaling 1/1024)
	sei();
}

ISR(TIMER2_OVF_vect) {		//3906 voor een halve seconde (ongeveer)
	if (interruptCounter >= 3906 /*3906*/) {
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

ISR(TIMER2_COMPA_vect) { // timer for receiving/sending

}

ISR(INT0_vect) { // receive interrupt
	processRecieve_IR(nTimer, &IRdata);
}
