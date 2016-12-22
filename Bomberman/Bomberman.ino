#define read_eeprom_word(address) eeprom_read_word ((const uint16_t*)address)
#define write_eeprom_word(address,value) eeprom_write_word ((uint16_t*)address,(uint16_t)value)
#include "Libraries/Levels/Levels.h"
#include "Libraries/LCD/LCD.h"
#include "Libraries/Nunchuck/Nunchuck.h"
#include "Libraries/DebugTools/DebugTools.h"
#include "Libraries/Player/Player.h"
#include "Libraries/Bomb/Bomb.h"
#include "Libraries/IR/IR.h"
#include "Libraries/Menu/Menu.h"
#include "Libraries/Hit/checkHit.h"
#include "Libraries/Sprites/Sprites.h"
#include "Libraries/Leds/Leds.h"
#include "Libraries/Potmeter/Potmeter.h"

uint8_t isPlayer2 = 0;				//LCD variabele
MI0283QT9 lcd;
unsigned char EEMEM  eeprom_Storagearray[12];// eeprom score array. [0] = player1, [1] = player 2
uint8_t joy_x_axis, joy_y_axis;	//Nunchuck Data
static uint8_t nunchuck_buf[6];	//Nunchuck Buffer
uint8_t grid[16][12];		//Griddata
uint8_t collumnCounter;		//collumnCounter
uint8_t rowCounter;			//rowCounter
uint8_t player1_x = 1, player1_x_old = 0, player1_y = 1, player1_y_old = 0;
uint8_t player2_x = 1, player2_y = 1, player2_x_old = 1, player2_y_old = 1;
//uint8_t player2_x = 14, player2_y = 10, player2_x_old = 14, player2_y_old = 10;
uint8_t player1_xCounter = 0, player1_yCounter = 0;		//Player movement speed
uint8_t player1_x_bombdrop = 0, player1_y_bombdrop = 0;		//Location of the dropped bomb p1
uint8_t player2_x_bombdrop = 0, player2_y_bombdrop = 0;		//Location of the dropped bomb p2
uint8_t antiholdCounter = 0;				// 1 when the player holds the 'Z' button, so the game doesn't place too many bombs
uint32_t nTimer = 0;
uint8_t tTimer = 0;
volatile uint8_t isSendingIR = 0;
volatile uint16_t IRdata;
volatile uint8_t interruptCounter = 0;				//used to count seconds in the interrupt
uint16_t touchx = 0, touchy = 0;
uint8_t livebombs = 0;
uint8_t hit = 0;
uint8_t menucounter = 0;
uint16_t LivesCounter = 0;
uint8_t maxBombCounter = 0;
uint8_t stage = 0;
uint8_t newHighscore = 0;

uint8_t bombradius = 2;
uint8_t playerSpeed = 60;
uint8_t player1_x_speed = 80, player1_y_speed = 80; //Higher is slower
uint8_t max_bombs = 1;
uint8_t score = 0;
uint8_t lives = 3;
uint8_t level = 1;
uint8_t reset_EEPROM = 0;
uint8_t sendBomb = 0;
uint8_t bombDelayCounter = 0;
uint8_t NunchuckReadCounter = 0;

uint8_t isPressed = 0;
uint8_t menuSelect = 1;
uint16_t speakerCounter;
uint16_t speakerTone = 1000;

void init_Timer();

int main() {
	DDRD = (1 << PORTD4); // speaker port
	data_store player2_data;
	init();
	Serial.begin(9600);
	init_Timer();
	init_IR();
	init_Nunchuck();
	init_LCD(lcd);
	init_Potmeter();
	for (;;) {	// MAIN LOOP	
		//set_Brightness(lcd, 7);	// Hier werkt overal de set_brightness, maar bij het laden van het spel is het scherm zwart voor ongeveer 5-10 seconden en daarna komt het spel opeens tevoorschijn
		if (stage == 0) {
			startScherm(lcd, &stage, nunchuck_buf, &joy_x_axis, &joy_y_axis, &isPressed, &NunchuckReadCounter);
		}
		if (stage == 1)
		{
			update_EEPROM();
			menu(lcd, &stage, &level, eeprom_Storagearray, &playerSpeed, &max_bombs, &newHighscore, dataReady_IR(), &IRdata, &isSendingIR, &menucounter, nunchuck_buf, &joy_x_axis, &joy_y_axis, &isPressed, &menuSelect, &NunchuckReadCounter);
			player1_x_speed = playerSpeed;
			player1_y_speed = playerSpeed;
			if (!isPlayer2) {
				init_Player(player1_x, player1_y, lcd);
				init_Level(grid, level, &player1_x, &player1_y, &player1_x_old, &player1_y_old, isPlayer2);
				draw_Sprites(lcd, grid);
			}
		}
		if (stage == 2) {
			if (isPlayer2) {
				init_Player(player1_x, player1_y, lcd);
				init_Level(grid, level, &player1_x, &player1_y, &player1_x_old, &player1_y_old, isPlayer2);
				draw_Sprites(lcd, grid);
			}
			// TODO: sync up arduinos, set to send
			for (;;) {
				set_Brightness(lcd, 7);
				if (stage == 1)
				{
					break;
				}
				read_Nunchuck(nunchuck_buf, &joy_x_axis, &joy_y_axis, &isPressed);
				calculate_Movement(&player1_x, &player1_y, joy_x_axis, joy_y_axis, &player1_xCounter, &player1_yCounter, player1_x_speed, player1_y_speed, grid);
				draw_Explosion(lcd, bombradius, grid, &livebombs, &score, &player1_x_bombdrop, &player1_y_bombdrop);
				checkPlayerHit(player1_x, player1_y, &hit, grid, &LivesCounter);
				update_EEPROM();
				updateLives(&hit, &lives, lcd, &score, &stage, grid, eeprom_Storagearray, &newHighscore, &isPressed);
				clear_Explosion(lcd, bombradius, grid, player1_x, player1_y);
				set_Leds(lives);

				if (dataReady_IR() && IRdata != 0) {
					player2_data = decode_IR(IRdata);

					// process IR data
					if (player2_data.type == PLAYER) {
						player2_x_old = player2_x;
						player2_y_old = player2_y;
						if (!grid[player2_data.xData][player2_data.yData]) {
							player2_x = player2_data.xData;
							player2_y = player2_data.yData;
						}
					}
					else if (player2_data.type == BOMB) {
						player2_x_bombdrop = player2_data.xData;
						player2_y_bombdrop = player2_data.yData;
						grid[player2_data.xData][player2_data.yData] = 6;
						IRdata = 0;
					}
				}

				// draw other player position if new
				if (player2_x != player2_x_old || player2_y != player2_y_old) {
					lcd.fillRect(player2_x_old * 20, player2_y_old * 20, 20, 20, Background);

					// draw the bomb again when drawing over it
//					if (player2_x_old == player2_x_bombdrop && player2_y_old == player2_y_bombdrop && !grid[player2_x_bombdrop][player2_y_bombdrop]) {
//						draw_BombSprite(lcd, player2_x_bombdrop, player1_y_bombdrop);
//					}

					lcd.fillRect(player2_x * 20, player2_y * 20, 20, 20, RGB(0, 0, 255));
				}

				draw_Player(player1_x, player1_y, &player1_x_old, &player1_y_old, lcd);
				check_Bomb(player1_x, player1_y, &player1_x_bombdrop, &player1_y_bombdrop, max_bombs, &livebombs, &antiholdCounter, nunchuck_buf, grid, &sendBomb);
				draw_Bomb(player1_x, player1_y, &player1_x_bombdrop, &player1_y_bombdrop, lcd, grid);
				//lcd.fillRect(player2_x_bombdrop * 20, player2_y_bombdrop * 20, 20, 20, RGB(255, 0, 0));
				//checkPlayerHit(player1_x, player1_y, &hit, grid);

				// Bomb update | IR send interval
				if (interruptCounter >= 100 /*3906*/) {
					if (sendBomb) {
						send_IR(&isSendingIR, BOMB, player2_x_bombdrop, player2_y_bombdrop);
						sendBomb = 0;
						player2_x_bombdrop = 0;
						player2_y_bombdrop = 0;
					}
					else {
						send_IR(&isSendingIR, PLAYER, player1_x, player1_y);
					}
					if (bombDelayCounter > 2) {
						bombDelayCounter = 0;
						for (rowCounter = 0; rowCounter < 12; rowCounter++) {
							for (collumnCounter = 0; collumnCounter < 16; collumnCounter++) {
								if ((grid[collumnCounter][rowCounter] > 3 && grid[collumnCounter][rowCounter] < 7) || (grid[collumnCounter][rowCounter] > 7 && grid[collumnCounter][rowCounter] < 10)) {
									grid[collumnCounter][rowCounter]--;
								}
							}
						}
					}
					bombDelayCounter++;
					interruptCounter = 0;
				}
				else {
					interruptCounter++;
				}

				// speaker sound, set PORTB4 to input to toggle speaker off
				if(speakerCounter > speakerTone) {
					PORTD ^= (1 << PORTD4);
					speakerCounter = 0;
				}
				speakerCounter++;
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

void update_EEPROM() {

	if (read_eeprom_word(&eeprom_Storagearray[0]) < score && lives == 0) { //if score of player1 in eeprom < score in game
		write_eeprom_word(&eeprom_Storagearray[0], score);  // write highest score to [0] (player 1 in eeprom)
		newHighscore = 1;
	}
	if (reset_EEPROM) {
		write_eeprom_word(&eeprom_Storagearray[0], 0);
		write_eeprom_word(&eeprom_Storagearray[1], 0);
	}
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
	// only receive while not sending
	if(!isSendingIR)
		processRecieve_IR(nTimer, &IRdata, &interruptCounter);
}
