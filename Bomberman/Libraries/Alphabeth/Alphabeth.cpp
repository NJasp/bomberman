#include "Alphabeth.h"

void draw_Keyboard(MI0283QT9 lcd, uint8_t margin, uint8_t boxSizeX, uint8_t boxSizeY, uint8_t middleSpace) {
	uint8_t beginy = 150 - margin - boxSizeY - middleSpace;
	uint8_t beginx = 6;
	lcd.fillScreen(COLOR_BLACK);
	lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2), margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawText(margin + (boxSizeX / 2) + 45, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace + 15, "BACK", COLOR_WHITE, COLOR_BLACK, 2);
	//lcd.drawText(beginx + 115, 120 - margin - boxSizeY, "..........", COLOR_FINE_ORANGE, COLOR_BLACK, 1);
	char b[] = { '.', '.', '.', '.', '.', '.', '.', '.', '.', '.' };
	char c[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	int a;
	for (a = 0; a < 10; a++) {
		lcd.drawChar(beginx + 115 + (a * 5), 120 - margin - boxSizeY, b[a], COLOR_WHITE, COLOR_BLACK, 1);
	}
	int i = 0;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 10; x++) {

			lcd.fillRect(x * 32 + beginx, y * 32 + beginy, 20, 20, COLOR_BLACK);
			lcd.drawRect(x * 32 + beginx, y * 32 + beginy, 20, 20, COLOR_WHITE);
			lcd.drawChar((x * 32 + beginx) + 7, (y * 32 + beginy) + 7, c[i], COLOR_FINE_BLUE, COLOR_BLACK, 1);
			i++;
		}
	}
}