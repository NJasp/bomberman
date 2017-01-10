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
#include "Libraries/Sound/Sound.h"
#include "Libraries/Eeprom/Eeprom.h"

uint8_t isPlayer2 = 0;															//Set if current player is player 2.
MI0283QT9 lcd;																	//LCD variabele
unsigned char EEMEM  eeprom_Storagearray[5];									// eeprom score array. [0] = player1, [2,3,4] = highscore name
uint8_t joy_x_axis, joy_y_axis;													//Nunchuck Data, for joystick
static uint8_t nunchuck_buf[6];													//Nunchuck Buffer, to store the data received from Nunchuck
uint8_t grid[16][12];															//Griddata
uint8_t collumnCounter;
uint8_t rowCounter;			
uint8_t player1_x = 1, player1_x_old = 0, player1_y = 1, player1_y_old = 0;		//Player1 positions
uint8_t player2_x = 1, player2_y = 1, player2_x_old = 1, player2_y_old = 1;		//Player2 positions
uint8_t player1_xCounter = 0, player1_yCounter = 0;								//Player counter needed to adjust player speed
uint8_t player1_x_bombdrop = 0, player1_y_bombdrop = 0;							//Location of the dropped bomb from player1
uint8_t send_bombdrop_x = 0, send_bombdrop_y = 0;								//Location of the dropped bomb from player2
uint8_t antiholdCounter = 0;													//Needed when the player holds the 'Z' button, so the game doesn't place too many bombs on the same spot
uint32_t nTimer = 0;															//Timer used for IR interrupts
uint8_t tTimer = 0;																//Timer used to create an interval between sending data 
volatile uint8_t isSendingIR = 0;												//Is set when IR is being send over
volatile uint16_t IRdata;														//Is used to store the data in that needs to be send
volatile uint8_t interruptCounter = 0;											//Used to set sending interval
volatile uint16_t menu_interruptCounter = 0;									//Used to set sending interval in menu
uint8_t livebombs = 0;															//Number of bombs currently in the game from this player
uint8_t hit = 0;																//Is set when a player is hit by an explosion
uint8_t menucounter;															//Is used to select different menuscreens (each number represents a different menu screen)
uint16_t LivesCounter = 0;														//Used to be invincible after being hit												
uint8_t stage = 0;																//Is used to select a stage (Startscherm, Menu, Game)
uint8_t newHighscore = 0;														//Is set when a new highscore is reached
uint8_t name[3] = { 0,0,0 };													//Used to temporarily store the new name of a highscore, when you set a new name
uint8_t eepromname[3];															//The name currently in EEPROM, used to compare it with name[3]

uint8_t bombradius = 1;															//The radius a bomb has from the center of the explosion. [0] is just the center of the explosion. [1] is a single explosion circle. [2] is 2 circles etc.
uint8_t playerSpeed = 60;														//Used to set both the players' x and y speed to the same
uint8_t player1_x_speed = 80, player1_y_speed = 80;								//Used to set the players' x and y speed individually
uint8_t max_bombs = 1;															//The maximum of bombs a player can place, before you have to wait until the bombs explode
uint8_t score = 0;										
uint8_t lives = 3;		
uint8_t level = 1;																//The level that is being selected. Standard Level 1 is selected.
uint8_t sendBomb = 0;															//Is set when IR needs to send a bomb to the other player.
uint8_t bombDelayCounter = 0;									
uint8_t MenuMaxBombsCounter = 0;												//Used to delay the input in the menu's, so that one press doesn't go trough the menu instantly

uint8_t isPressed = 0;															//Is set when the 'Z' button is pressed
uint8_t buttonSelect = 1;														//Used to check which menubutton is selected
uint16_t seed = 0;
uint8_t player2isDead = 0;

void init_Timer();

int main() {
	data_store player2_data;
	Serial.begin(9600);
	init();
	init_Timer();
	init_IR();
	init_Nunchuck();
	init_LCD(lcd);
	init_Potmeter();
	update_EEPROM(eeprom_Storagearray, name, eepromname, score, 0, lives, 0);
	uint8_t i;
	for (i = 0; i < 3; i++) {													//Store the EEPROM values in an array
		eepromname[i] = read_eeprom_word(&eeprom_Storagearray[i + 2]);
	}
	if (isPlayer2 == 1) {														//If this is player2, turn the screen around 180 degrees so the screens have the same orientation
		lcd.setOrientation(180);
	}
	for (;;) {																	// MAIN LOOP	
		if (stage == 0) {
			startScherm(lcd, &stage, nunchuck_buf, &joy_x_axis, &joy_y_axis, &isPressed);
		}
		if (stage == 1)
		{
			menucounter = 0;													//The main menu = menucounter 0
			menu(lcd, &stage, &level, eeprom_Storagearray, &playerSpeed, &max_bombs, &newHighscore, &IRdata, &isSendingIR, &menu_interruptCounter, &seed, &menucounter, nunchuck_buf, &joy_x_axis, &joy_y_axis, &isPressed, &buttonSelect, &MenuMaxBombsCounter, name, eepromname, &score, &lives);
			player1_x_speed = playerSpeed;										//After the player went trough the menu, set the selected player speed.
			player1_y_speed = playerSpeed;
		}
		if (stage == 2) {	
			init_Level(grid, level, &player1_x, &player1_y, &player1_x_old, &player1_y_old, isPlayer2, nTimer, &isSendingIR, &seed);			//Initialize the level selected in menu in stage 1
			draw_Sprites(lcd, grid);
			init_Player(player1_x, player1_y, lcd);
			for (;;) {
				set_Brightness(lcd, 7);											//Set the brightness according to the Potentiometers value
				read_Nunchuck(nunchuck_buf, &joy_x_axis, &joy_y_axis, &isPressed);
				calculate_Movement(&player1_x, &player1_y, joy_x_axis, joy_y_axis, &player1_xCounter, &player1_yCounter, player1_x_speed, player1_y_speed, grid);
				draw_Explosion(lcd, bombradius, grid, &livebombs, &score, player1_x, player1_y, &player1_x_bombdrop, &player1_y_bombdrop);
				checkPlayerHit(player1_x, player1_y, &hit, grid, &LivesCounter);
				updateLives(&hit, &lives, lcd, &score, &stage, grid, eeprom_Storagearray, &newHighscore, &isPressed, nunchuck_buf, &livebombs, &player2isDead, &isSendingIR, name, eepromname);
				if (stage == 1)													//If stage is set to 0 in gameover screen. break out main game loop
				{
					break;
				}
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
						if(player2_data.xData < 16 && player2_data.xData > 0 &&
						   player2_data.yData < 12 && player2_data.yData > 0 &&
						   !grid[player2_data.xData][player2_data.yData]) {
							draw_BombSprite(lcd, (player2_data.xData), (player2_data.yData));

							grid[player2_data.xData][player2_data.yData] = 6;
							IRdata = 0;
						}
					}
					else if (player2_data.type == 0 && player2_data.xData == 77 && player2_data.yData == 7) {
						player2isDead = 1;
					}
				}

				// draw other player if position is new
				if (player2_x != player2_x_old || player2_y != player2_y_old) {
					lcd.fillRect(player2_x_old * 20, player2_y_old * 20, 20, 20, Background);
					lcd.fillRect(player2_x * 20, player2_y * 20, 20, 20, RGB(0, 0, 255));
				}

				draw_Player(player1_x, player1_y, &player1_x_old, &player1_y_old, lcd);
				check_Bomb(player1_x, player1_y, &player1_x_bombdrop, &player1_y_bombdrop, max_bombs, &livebombs, &antiholdCounter, nunchuck_buf, grid, &sendBomb);

				// copy values to send them later before they get set to 0
				if (sendBomb) {
					send_bombdrop_x = player1_x_bombdrop;
					send_bombdrop_y = player1_y_bombdrop;
				}

				draw_Bomb(player1_x, player1_y, &player1_x_bombdrop, &player1_y_bombdrop, lcd, grid);

				// Bomb update | IR send interval
				if (interruptCounter >= 100 /*3906*/) {
					if (sendBomb) {
						send_IR(&isSendingIR, BOMB, send_bombdrop_x, send_bombdrop_y);
						send_bombdrop_x = 0;
						send_bombdrop_y = 0;

						sendBomb = 0;
					}
					else {
						send_IR(&isSendingIR, PLAYER, player1_x, player1_y);
					}
					if (bombDelayCounter > 1) {
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
	// only receive while not sending
	if(!isSendingIR)
		processRecieve_IR(nTimer, &IRdata, &interruptCounter, &menu_interruptCounter);
}
