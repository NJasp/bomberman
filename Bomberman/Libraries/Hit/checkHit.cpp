#define read_eeprom_word(address) eeprom_read_word ((const uint16_t*)address)
#define write_eeprom_word(address,value) eeprom_write_word ((uint16_t*)address,(uint16_t)value)
#include "checkHit.h"

void checkPlayerHit(uint8_t player1_x, uint8_t player1_y, uint8_t *hit, uint8_t grid[16][12], uint8_t* LivesCounter) {
	if ((grid[player1_x][player1_y] == 7 || grid[player1_x][player1_y] == 8 || grid[player1_x][player1_y] == 9)) {
		if ((*LivesCounter) == 0) {
			(*hit) = 1;
		}
		if ((*LivesCounter) == 140) {
			(*hit) = 1;
			(*LivesCounter) = 0;
		}
		(*LivesCounter)++;
	}
	else {
		(*LivesCounter) = 0;
	}
}


void updateLives(uint8_t* hit, uint8_t* lives, MI0283QT9 lcd, uint8_t* score, uint8_t* stage, uint8_t grid[16][12]) {

	if (!(*lives)) {
		(*stage) = 3;
		uint8_t a, b, c;

		lcd.fillScreen(RGB(0, 0, 0));
		//if (player_scoreArray[1] > player_scoreArray[3]) { //make win conditon. check which player has the highest score
		//	lcd.drawText(50, 60, " You win ", RGB(255, 255, 255), RGB(0, 0, 0), 3);
		//}
		//else {
		lcd.drawText(50, 60, " End game", RGB(255, 255, 255), RGB(0, 0, 0), 3);
		//}
		lcd.drawText(120, 100, "Scores", RGB(255, 255, 255), RGB(0, 0, 0), 1);
		a = lcd.drawText(120, 120, "Player ", RGB(255, 255, 255), RGB(0, 0, 0), 1);
		b = lcd.drawInteger(a, 120, 1, 10, RGB(255, 255, 255), RGB(0, 0, 0), 1);
		c = lcd.drawText(b, 120, ": ", RGB(255, 255, 255), RGB(0, 0, 0), 1);
		lcd.drawInteger(c, 120, (*score), 10, RGB(255, 255, 255), RGB(0, 0, 0), 1);

		//a = lcd.drawText(120, 140, "Player ", RGB(255, 255, 255), RGB(0, 0, 0), 1);
		//b = lcd.drawInteger(a, 140, player_scoreArray[2], 10, RGB(255, 255, 255), RGB(0, 0, 0), 1);
		//c = lcd.drawText(b, 140, ": ", RGB(255, 255, 255), RGB(0, 0, 0), 1);
		//lcd.drawInteger(c, 140, (*score2), 10, RGB(255, 255, 255), RGB(0, 0, 0), 1);
		//(*score) = 0;
		//(*lives) = 1;
		//(*stage) = 1;
		lcd.drawText(30, 200, "Touch to continue", RGB(255, 255, 255), RGB(0, 0, 0), 2);
		for (;;)
		{
			//set_Brightness(lcd, 7);
			if (lcd.touchRead())
			{
				resetVariables(score, stage, lives, grid);
				break;
			}
		}
	}
	if ((*hit) && (*lives)) {
		(*lives)--;
		(*hit) = 0;
	}
}

void resetVariables(uint8_t* score, uint8_t* stage, uint8_t* lives, uint8_t grid[16][12])
{
	uint8_t row, collumn;

	(*score) = 0;
	(*lives) = 3;
	(*stage) = 1;

	for (row = 0; row < 12; row++) {
		for (collumn = 0; collumn < 16; collumn++) {
			grid[collumn][row] = 0;
		}
	}
}
