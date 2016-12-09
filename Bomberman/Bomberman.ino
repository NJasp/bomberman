#include "Libraries/Levels/Levels.h"
#include "Libraries/LCD/LCD.h"
#include "Libraries/Nunchuck/Nunchuck.h"
#include "Libraries/DebugTools/DebugTools.h"
#include "Libraries/Player/Player.h"
#include "Libraries/Bomb/Bomb.h"
#include "Libraries/IR/IR.h"
#include "Libraries/Menu/Menu.h"
#include "Libraries/Hit/checkHit.h"

MI0283QT9 lcd;					//LCD variabele
uint8_t joy_x_axis, joy_y_axis;	//Nunchuck Data
static uint8_t nunchuck_buf[6];	//Nunchuck Buffer
uint8_t grid[16][12];		//Griddata
uint8_t collumnCounter;		//collumnCounter
uint8_t rowCounter;			//rowCounter
uint8_t player1_x = 0, player1_y = 0;		//player locations
uint8_t player2_x = 14, player2_y = 10, player2_x_old = 14, player2_y_old = 10;
uint8_t player1_xCounter = 0, player1_yCounter = 0;		//Player movement speed
uint8_t player1_x_old = 0, player1_y_old = 0;		//Old locations of the player;
uint8_t player1_x_bombdrop = 0, player1_y_bombdrop = 0;		//Location of the dropped bomb;
uint8_t antiholdCounter = 0;				// 1 when the player holds the 'Z' button, so the game doesn't place too many bombs
uint32_t nTimer = 0;
uint8_t tTimer = 0;
volatile uint8_t isSendingIR = 0;
volatile uint16_t IRdata;
uint16_t interruptCounter = 0;				//used to count seconds in the interrupt
uint16_t touchx = 0, touchy = 0;
uint8_t livebombs = 0;
uint8_t hit = 0;
uint8_t menucounter = 0;
uint8_t stage = 1;

uint8_t bombradius = 5;
uint8_t player1_x_speed = 0, player1_y_speed = 0; //Higher is slower
data_store player2_data;
uint8_t max_bombs = 5;
uint8_t score = 0;
uint8_t lives = 1;
uint8_t level = 1;

void init_Timer();

int main() {
	init();
	Serial.begin(9600);
	init_Timer();
	init_IR();
	init_Nunchuck();
	init_LCD(lcd);
	lcd.touchStartCal();
	startScherm(lcd);

	for (;;) {	// MAIN LOOP	
		if (stage == 1)
		{
			menu();
		}
		if (stage == 2) {
			init_Player(player1_x, player1_y, lcd);
			init_Level(grid, level, &player1_x, &player1_y, &player1_x_old, &player1_y_old);
			draw_Walls_Crates(lcd, grid);
			for (;;) {
				read_Nunchuck(nunchuck_buf, &joy_x_axis, &joy_y_axis);
				calculate_Movement(&player1_x, &player1_y, joy_x_axis, joy_y_axis, &player1_xCounter, &player1_yCounter, player1_x_speed, player1_y_speed, grid);
				//updateLives(&hit, &lives, &livesCheck, lcd, score, &hitCounter);

				if (dataReady_IR()) {
					player2_data = decode_IR(IRdata);

					// process IR data
					if (player2_data.type == PLAYER) {
						player2_x = player2_data.xData;
						player2_y = player2_data.yData;
					}

					// TODO: implement other types
				}

				// draw other player position if new
				if (player2_x != player2_x_old || player2_y != player2_y_old) {
					lcd.fillRect(player2_x_old * 20, player2_y_old * 20, 20, 20, Background);
					lcd.fillRect(player2_x * 20, player2_y * 20, 20, 20, RGB(0, 0, 255));
				}

				check_Bomb(player1_x, player1_y, &player1_x_bombdrop, &player1_y_bombdrop, max_bombs, &livebombs, &antiholdCounter, nunchuck_buf, grid);
				draw_Player(player1_x, player1_y, &player1_x_old, &player1_y_old, lcd);
				//lcd.fillCircle(player2_data.xData, player2_data.yData, 10, RGB(0, 0, 255));
				draw_Bomb(player1_x, player1_y, &player1_x_bombdrop, &player1_y_bombdrop, lcd);
				draw_Explosion(lcd, bombradius, grid, &livebombs, &score, &hit, player1_x, player1_y);
				clear_Explosion(lcd, bombradius, grid);
				updateLives(&hit, &lives, lcd, score);

				// Bomb update | IR send interval
				if (interruptCounter >= 100 /*3906*/) {
					send_IR(&isSendingIR, PLAYER, player1_x, player1_y);
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
		}
	}
	return 0;
}

void init_Timer() {
	TCCR2A = 0;
	TCCR2B = 0;
	TIMSK2 = 0;
	TCCR2A = (1 << COM2B0) | (1 << WGM21); 	// toggle OC2A on match
	TCCR2B |= (1 << CS21); 		// 8 prescaler		
	TIMSK2 |= (1 << OCIE2A);		// enable overflow interrupt|
	OCR2B = 26; 				// value to compare timer against	| 1/(53*(1/16000000)*8) = 37,7kHz
	OCR2A = 26;								// nanosecond counter
	TCNT2 = 0;										//SET TIMER 2 AAN (Prescaling 1/1024)
	sei();
}

ISR(TIMER2_COMPA_vect) {// timer for receiving/sending

	tTimer++;
	if (tTimer == 10) {
		nTimer++;
		// send function
		if (isSendingIR) {
			processSend_IR(nTimer, &isSendingIR);
		}
		tTimer = 0;
	}

}

ISR(INT0_vect) { // receive interrupt
	processRecieve_IR(nTimer, &IRdata);
}

void menu()
{
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
				stage = 2;
				lcd.fillScreen(Background);
				level = 1;
				break;
			}
			if (touchx >= 20 && touchx <= 120 && touchy >= 120 && touchy <= 150) {
				stage = 2;
				lcd.fillScreen(Background);
				level = 2;
				break;
			}
			if (touchx >= 20 && touchx <= 120 && touchy >= 180 && touchy <= 210) {
				stage = 2;
				lcd.fillScreen(Background);
				level = 3;
				break;
			}
			if (touchx >= 180 && touchx <= 250 && touchy >= 200 && touchy <= 230) {
				stage = 1;
				lcd.fillScreen(Background);
				menucounter = 0;
				menu();
			}
		}
	}
}