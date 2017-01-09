#define read_eeprom_word(address) eeprom_read_word ((const uint16_t*)address)
#define write_eeprom_word(address,value) eeprom_write_word ((uint16_t*)address,(uint16_t)value)
#include "checkHit.h"
#include "../Nunchuck/Nunchuck.h"
#include "../Eeprom/Eeprom.h"

void checkPlayerHit(uint8_t player1_x, uint8_t player1_y, uint8_t *hit, uint8_t grid[16][12], uint16_t* LivesCounter) { // Player can only be hit once by the same bom.
	if ((grid[player1_x][player1_y] == 7 || grid[player1_x][player1_y] == 8 || grid[player1_x][player1_y] == 9)) {
		if ((*LivesCounter) == 0) { // Check so that we can only be hit once by the same bom.
			(*hit) = 1;
		}
		if ((*LivesCounter) == 750) {
			(*LivesCounter) = 0;
		}
		(*LivesCounter)++;
	}
	else {
		(*LivesCounter) = 0;
	}
}


void updateLives(uint8_t* hit, uint8_t* lives, MI0283QT9 lcd, uint8_t* score, uint8_t* stage, uint8_t grid[16][12], unsigned char eeprom_Storagearray[12], uint8_t* newHighscore, uint8_t* isPressed, uint8_t nunchuck_buf[6], uint8_t* livebombs, uint8_t* player2isDead, volatile uint8_t* isSendingIR, uint8_t name[3], uint8_t eepromname[1]) {

	if (!(*lives) || *player2isDead) {
		(*stage) = 3; // Game over.
		uint8_t a, b, c;

		lcd.fillScreen(COLOR_BLACK);

		if(!(*lives))
			lcd.drawText(50, 60, "YOU LOSE!", COLOR_WHITE, COLOR_BLACK, 3);
			lcd.drawText(120, 100, "Scores", COLOR_WHITE, COLOR_BLACK, 1);
			a = lcd.drawText(120, 120, "Player ", COLOR_WHITE, COLOR_BLACK, 1);
			b = lcd.drawInteger(a, 120, 1, 10, COLOR_WHITE, COLOR_BLACK, 1);
			c = lcd.drawText(b, 120, ": ", COLOR_WHITE, COLOR_BLACK, 1);
			lcd.drawInteger(c, 120, (*score), 10, COLOR_WHITE, COLOR_BLACK, 1);
		}
		else {
			update_EEPROM(eeprom_Storagearray, name, eepromname, (*score) + 5, 0, (*lives), 0);
			lcd.drawText(50, 60, "YOU WIN!!", COLOR_WHITE, COLOR_BLACK, 3);
		//}
		lcd.drawText(120, 100, "Scores", COLOR_WHITE, COLOR_BLACK, 1);
		a = lcd.drawText(120, 120, "Player ", COLOR_WHITE, COLOR_BLACK, 1);
		b = lcd.drawInteger(a, 120, 1, 10, COLOR_WHITE, COLOR_BLACK, 1);
		c = lcd.drawText(b, 120, ": ", COLOR_WHITE, COLOR_BLACK, 1);
		lcd.drawInteger(c, 120, (*score), 10, COLOR_WHITE, COLOR_BLACK, 1);
		
		if ((*newHighscore)) {
			lcd.drawText(110, 140, "NEW HIGHSCORE!!", COLOR_WHITE, COLOR_BLACK, 1);
			lcd.drawText(70, 160, "Please add your name in the scores menu", COLOR_WHITE, COLOR_BLACK, 1);
			//(*newHighscore) = 0;
		}


		lcd.drawText(25, 200, " 'Z' to continue", COLOR_WHITE, COLOR_BLACK, 2);
		uint8_t sendDelay = 0;
		for (;;)
		{
			read_Nunchuck(nunchuck_buf, 0, 0, isPressed); // Back to menu.
			if ((*isPressed))
			{
				(*isPressed) = 0;
				resetVariables(score, stage, lives, grid, livebombs, player2isDead);
				break;
			}

			// only send over 'dead' messages if you died first
			if(!(*lives)) {
				sendDelay++;
				if(sendDelay == 100) {
					send_IR(isSendingIR, MISC, 77, 7);
					sendDelay = 0;
				}
			}
		}
	}
	if ((*hit) && (*lives)) { // If you are hit and you still have some lives left, lives -1 and the check on getting hit set on 0.
		(*lives)--;
		(*hit) = 0;
	}
}

void resetVariables(uint8_t* score, uint8_t* stage, uint8_t* lives, uint8_t grid[16][12], uint8_t* livebombs, uint8_t* player2isDead)
{ // Clear all used variables that are used while playing the game. So we can use them again without resetting.
	uint8_t row, collumn;

	(*score) = 0;
	(*lives) = 3;
	(*stage) = 1;
	(*livebombs) = 0;
	(*player2isDead) = 0;

	// Clear Row and Collum so that when the next game is selected, there wont spawn any old block from the previous game.
	for (row = 0; row < 12; row++) {
		for (collumn = 0; collumn < 16; collumn++) {
			grid[collumn][row] = 0;
		}
	}
}
