#define read_eeprom_word(address) eeprom_read_word ((const uint16_t*)address)
#define write_eeprom_word(address,value) eeprom_write_word ((uint16_t*)address,(uint16_t)value)
#include "checkHit.h"

unsigned int EEMEM  eeprom_Storagearray[2]; // eeprom score array. [0] = player1, [1] = player 2
unsigned int player_scoreArray[4] = { 1,0,2,0 }; //player score array in game. [0] = number of player1, [1] = score of player at place [0], [2] = number of player2, [3] = score of player at place[2]

uint8_t counter2 = 0;
uint8_t reset_EEPROM = 0;

void checkPlayerHit(uint8_t player1_x, uint8_t player1_y, uint8_t *hit, uint8_t grid[16][12]) {
	if ((grid[player1_x][player1_y] == 7 || grid[player1_x][player1_y] == 8 || grid[player1_x][player1_y] == 9)) {
		(*hit) = 1;
	}
}


void updateLives(uint8_t* hit, uint8_t* lives, MI0283QT9 lcd, uint8_t* score, uint8_t* stage) {
	if (reset_EEPROM) {
		write_eeprom_word(&eeprom_Storagearray[0], 0);
		write_eeprom_word(&eeprom_Storagearray[1], 0);
	}
	if (!(*lives)) {
		uint8_t a, b, c;
		if (read_eeprom_word(&eeprom_Storagearray[0]) < (*score)) { //if score of player1 in eeprom < score in game
			write_eeprom_word(&eeprom_Storagearray[0], (*score));  // write highest score to [0] = player 1 in eeprom
		}
		
		player_scoreArray[1] = read_eeprom_word(&eeprom_Storagearray[0]); //read score of player1 from eeprom
		player_scoreArray[3] = read_eeprom_word(&eeprom_Storagearray[1]); //read score of player2 from eeprom
		lcd.fillScreen(RGB(0, 0, 0));
		if (player_scoreArray[1] > player_scoreArray[3]) { //make win conditon. check which player has the highest score
			lcd.drawText(50, 60, " You win ", RGB(255, 255, 255), RGB(0, 0, 0), 3);
		}
		else {
			lcd.drawText(50, 60, "Game over", RGB(255, 255, 255), RGB(0, 0, 0), 3);
		}
		lcd.drawText(120, 100, "High scores", RGB(255, 255, 255), RGB(0, 0, 0), 1);
		a = lcd.drawText(120, 120, "Player ", RGB(255, 255, 255), RGB(0, 0, 0), 1);
		b = lcd.drawInteger(a, 120, player_scoreArray[0], 10, RGB(255, 255, 255), RGB(0, 0, 0), 1);
		c = lcd.drawText(b, 120, ": ", RGB(255, 255, 255), RGB(0, 0, 0), 1);
		lcd.drawInteger(c, 120, player_scoreArray[1], 10, RGB(255, 255, 255), RGB(0, 0, 0), 1);

		a = lcd.drawText(120, 140, "Player ", RGB(255, 255, 255), RGB(0, 0, 0), 1);
		b = lcd.drawInteger(a, 140, player_scoreArray[2], 10, RGB(255, 255, 255), RGB(0, 0, 0), 1);
		c = lcd.drawText(b, 140, ": ", RGB(255, 255, 255), RGB(0, 0, 0), 1);
		lcd.drawInteger(c, 140, player_scoreArray[3], 10, RGB(255, 255, 255), RGB(0, 0, 0), 1);
		(*score) = 0;
		(*lives) = 1;
		(*stage) = 1;
		lcd.drawText(30, 200, "Touch to continue", RGB(255, 255, 255), RGB(0, 0, 0), 2);
		while (1);
	}
	if ((*hit) && (*lives)) {
		(*lives)--;
		(*hit) = 0;
	}
}
