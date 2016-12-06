#include "checkHit.h"
uint8_t counter2 = 0;

void checkPlayerHit(uint8_t player1_x, uint8_t player1_y, uint8_t *hit, uint8_t grid[16][12]) {
	if ((grid[player1_x][player1_y] == 7 || grid[player1_x][player1_y] == 8 || grid[player1_x][player1_y] == 9)) {
		(*hit) = 1;
	}
}

void updateLives(uint8_t* hit, uint8_t* lives, MI0283QT9 lcd, uint8_t score) {
	if (!(*lives)) {
		Serial.println("player is dead");
		lcd.fillScreen(RGB(0, 0, 0));
		lcd.drawText(50, 60, "Game over", RGB(255, 255, 255), RGB(0, 0, 0), 3);
		lcd.drawText(70, 100, "Score player 1: ", RGB(255, 255, 255), RGB(0, 0, 0), 1);
		lcd.drawInteger(200, 100, score, 10, RGB(255, 255, 255), RGB(0, 0, 0), 1);
		while (1);
	}
	if ((*hit) && (*lives)) {
		//Serial.println("level--");
		(*lives)--;
		//Serial.println((*lives));
		(*hit) = 0;
	}
}