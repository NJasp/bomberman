#include "Menu.h"
#include "../Nunchuck/Nunchuck.h"
uint8_t margin = 10, boxSizeX = 145, boxSizeY = 52, middleSpace = 10, highlightMargin = 2; //Has to be 320 together for x and 240 together for y;

void startScherm(MI0283QT9 lcd, uint8_t* stage, uint8_t buffer[], uint8_t* x, uint8_t* y, uint8_t* isPressed)
{
	uint8_t toggle1 = 0, toggle2 = 0, drawfreq = 0, redraw = 1;
	//Background
	lcd.fillScreen(COLOR_BLACK);
	//lcd.fillScreen(RGB(127, 127, 127));
	//Titel
	//lcd.drawText(15, 40, "B MBERMAN", RGB(0, 0, 127), RGB(127, 127, 127), 4);
	lcd.drawText(15, 40, "B MBERMAN", /*RGB(0, 0, 127)*/COLOR_WHITE, COLOR_BLACK, 4);
	//Bomb
	lcd.drawCircle(60, 54, 16, RGB(102, 102, 102));
	lcd.fillCircle(54, 46, 2, RGB(127, 127, 127));
	lcd.fillCircle(52, 48, 2, RGB(127, 127, 127));
	lcd.drawRect(53, 35, 15, 5, RGB(102, 102, 102));
	lcd.fillRect(53, 35, 15, 5, RGB(0, 0, 0));
	//Lont
	lcd.fillRect(58, 30, 6, 5, RGB(127, 80, 0));
	lcd.fillRect(56, 28, 6, 5, RGB(127, 80, 0));
	lcd.fillRect(54, 26, 6, 5, RGB(127, 80, 0));
	lcd.fillRect(52, 24, 6, 5, RGB(127, 80, 0));
	//Lijnen
	//lcd.drawLine(0, 70, lcd.width(), 70, RGB(0, 0, 0));
	//lcd.fillRect(0, 115, 50, 50, RGB(0, 0, 0));
	//lcd.fillRect((lcd.width()-50), 115, 50, 50, RGB(0, 0, 0));
	//lcd.fillRect(50, 160, (lcd.width()-100), 5, RGB(0,0,255));
	//lcd.drawLine(0, 199, lcd.width(), 199, RGB(0, 0, 0));
	//lcd.drawLine(0, 30, 20, 0, RGB(0, 0, 0));
	for (;;) {
		read_Nunchuck(buffer, x, y, isPressed);
		if (toggle1) {//Elke loop toggle de animatie van het vuur naar een andere
			//lcd.fillRect(44, 18, 14, 11, RGB(127, 127, 127));
			lcd.fillRect(44, 18, 14, 11, COLOR_BLACK);
			lcd.fillRect(52, 24, 6, 5, RGB(127, 80, 0));
			lcd.fillTriangle(48, 28, 48, 18, 57, 22, RGB(255, 127, 0));
			lcd.fillTriangle(53, 28, 53, 18, 44, 22, RGB(255, 0, 0));
			toggle1 = 0;
		}
		else {
			//lcd.fillRect(44, 18, 14, 11, RGB(127, 127, 127));
			lcd.fillRect(44, 18, 14, 11, COLOR_BLACK);
			lcd.fillRect(52, 24, 6, 5, RGB(127, 80, 0));
			lcd.fillTriangle(50, 18, 46, 25, 55, 25, RGB(255, 127, 0));
			lcd.fillTriangle(50, 28, 46, 20, 55, 20, RGB(255, 0, 0));
			toggle1 = 1;
		}
		if ((!toggle2) && redraw) {//Elke 10e loop toggle tekst aan en uit (en teken het maar 1 keer)
			//lcd.drawText(25, 200, "Touch to continue", RGB(0, 0, 127), RGB(127, 127, 127), 2);
			lcd.drawText(25, 200, "Touch to continue", /*RGB(0, 0, 127)*/COLOR_WHITE, COLOR_BLACK, 2);
			redraw = 0;
		}
		else if (toggle2 && redraw) {
			//lcd.fillRect(25, 200, 268, 15, RGB(127, 127, 127));
			lcd.fillRect(25, 200, 268, 15, COLOR_BLACK);
			redraw = 0;
		}
		//TOGGLE SETTINGS
		if (drawfreq >    100) {//Als er 10 loops voorbij zijn, toggle tekst en reset counter
			redraw = 1;
			drawfreq = 0;
			toggle2 = ~(toggle2);
		}
		else {
			drawfreq++;
		}
		if ((*isPressed)) {
			(*stage) = 1;
			break;
		}
	}
}

void mainMenu(MI0283QT9 lcd) {
	//lcd.fillRect(65, 180, 185, 50, (RGB(0, 0, 0)));
	//lcd.drawText(80, 195, "Options", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 3);
	lcd.fillScreen(COLOR_BLACK);
	//Y row = 1
	lcd.drawRect(margin, margin, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawRect(margin + boxSizeX + middleSpace, margin, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawText(margin + 32, margin + 20, "START", COLOR_WHITE, COLOR_BLACK, 2);
	lcd.drawText(margin + boxSizeX + middleSpace + 12, margin + 20, "SETTINGS", COLOR_WHITE, COLOR_BLACK, 2);
	//Y row = 2
	lcd.drawRect(margin, margin + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawRect(margin + boxSizeX + middleSpace, margin + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawText(margin + 25, margin + boxSizeY + middleSpace + 20, "SCORES", COLOR_WHITE, COLOR_BLACK, 2);
	lcd.drawText(margin + boxSizeX + middleSpace + 30, margin + boxSizeY + middleSpace + 20, "ABOUT", COLOR_WHITE, COLOR_BLACK, 2);
	//Y row = 3
	//lcd.drawRect(margin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawRect(margin + boxSizeX + middleSpace, margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawText(margin + boxSizeX + middleSpace + 35, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + 20, "BACK", COLOR_WHITE, COLOR_BLACK, 2);
	lcd.drawText(0, 227, "Bomberman version 0.1", COLOR_WHITE, COLOR_BLACK, 1); // Version tekst
}

void highscores(MI0283QT9 lcd, unsigned char eeprom_Storagearray[12], uint8_t* newHighscore)
{
	lcd.fillScreen(COLOR_BLACK);
	lcd.drawText(margin + 15, margin + 5, "HIGH SCORES", COLOR_WHITE, COLOR_BLACK, 3);
	lcd.drawRect(margin + (boxSizeX / 2) + middleSpace / 2, margin + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawRect(margin + (boxSizeX / 2) + middleSpace / 2, margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE);
	uint8_t a, b;
	char playerName[] = { (read_eeprom_word((&eeprom_Storagearray[2]))), (read_eeprom_word((&eeprom_Storagearray[3]))), (read_eeprom_word((&eeprom_Storagearray[4]))), (read_eeprom_word((&eeprom_Storagearray[5]))), (read_eeprom_word((&eeprom_Storagearray[6]))), '\0' };
	a = lcd.drawText(margin + (boxSizeX / 2) + middleSpace / 2 + 27, margin + boxSizeY + middleSpace + 15, playerName, RGB(255, 255, 255), RGB(0, 0, 0), 1);
	b = lcd.drawText(a, margin + boxSizeY + middleSpace + 15, ": ", RGB(255, 255, 255), RGB(0, 0, 0), 1);
	lcd.drawInteger(b, margin + boxSizeY + middleSpace + 15, read_eeprom_word(&eeprom_Storagearray[0]), 10, RGB(255, 255, 255), RGB(0, 0, 0), 1);
	if ((*newHighscore)) {
		lcd.drawText(margin + (boxSizeX / 2) + middleSpace / 2 + 5, margin + boxSizeY + middleSpace + 30, "touch to add name", RGB(255, 255, 255), RGB(0, 0, 0), 1);
		if (read_eeprom_word(&eeprom_Storagearray[2]) != '1') {
			(*newHighscore) = 0;
		}
	}
	lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2), margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawText(margin + (boxSizeX / 2) + 45, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace + 15, "BACK", COLOR_WHITE, COLOR_BLACK, 2);
}

/*void keyboard(MI0283QT9 lcd, uint8_t beginx, uint8_t beginy, char b[], char c[]) {
	beginy = 150 - margin - boxSizeY - middleSpace;
	beginx = 6;
	lcd.fillScreen(COLOR_BLACK);
	lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2), margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawText(margin + (boxSizeX / 2) + 45, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace + 15, "BACK", COLOR_WHITE, COLOR_BLACK, 2);
	//lcd.drawText(beginx + 115, 120 - margin - boxSizeY, "..........", COLOR_FINE_ORANGE, COLOR_BLACK, 1);
	uint8_t a;
	for (a = 0; a < 10; a++) {
		lcd.drawChar(beginx + 115 + (a * 5), 120 - margin - boxSizeY, b[a], COLOR_WHITE, COLOR_BLACK, 1);
	}
	uint8_t i;
	for (uint8_t y = 0; y < 3; y++) {
		for (uint8_t x = 0; x < 10; x++) {

			lcd.fillRect(x * 32 + beginx, y * 32 + beginy, 20, 20, COLOR_BLACK);
			lcd.drawRect(x * 32 + beginx, y * 32 + beginy, 20, 20, COLOR_WHITE);
			lcd.drawChar((x * 32 + beginx) + 7, (y * 32 + beginy) + 7, c[i], COLOR_FINE_BLUE, COLOR_BLACK, 1);
			i++;
		}
	}
}*/

void options(MI0283QT9 lcd, uint8_t* playerSpeed, uint8_t* max_bombs)
{
	lcd.fillScreen(COLOR_BLACK);
	lcd.drawText(margin + 45, margin + 5, "SETTINGS", COLOR_WHITE, COLOR_BLACK, 3);
	lcd.drawRect(margin, margin + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.fillRect(margin, margin + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_RED); // Upper-Bottom Rectangle
	lcd.drawRect(margin + (boxSizeX / 2) + middleSpace / 2, margin + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2), margin + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.fillRect(margin + boxSizeX + middleSpace + (boxSizeX / 2), margin + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_GREEN); // Upper-Bottom Rectangle
	lcd.drawText(margin + 30, margin + boxSizeY + middleSpace + 20, "-", COLOR_WHITE, COLOR_FINE_RED, 2);
	lcd.drawText(margin + (boxSizeX / 2) + 25, margin + boxSizeY + middleSpace + 10, "player speed", COLOR_WHITE, COLOR_BLACK, 1);
	lcd.drawRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, (boxSizeX - 60), (boxSizeY / 10), COLOR_FINE_BLUE);
	lcd.fillRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, (boxSizeX - 60) - (*playerSpeed), (boxSizeY / 10), COLOR_FINE_ORANGE);
	lcd.drawText(margin + (boxSizeX / 2) + middleSpace + boxSizeX + 30, margin + boxSizeY + middleSpace + 20, "+", COLOR_WHITE, COLOR_FINE_GREEN, 2);
	//Y row = 3
	lcd.drawRect(margin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.fillRect(margin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_RED); // Upper-Bottom Rectangle
	lcd.drawRect(margin + (boxSizeX / 2) + middleSpace / 2, margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2), margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.fillRect(margin + boxSizeX + middleSpace + (boxSizeX / 2), margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_GREEN); // Upper-Bottom Rectangle
	lcd.drawText(margin + 30, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + 20, "-", COLOR_WHITE, COLOR_FINE_RED, 2);
	lcd.drawText(margin + (boxSizeX / 2) + 25, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + 10, "maxium bombs", COLOR_WHITE, COLOR_BLACK, 1);
	lcd.drawInteger(margin + (boxSizeX / 2) + 70, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + 30, (*max_bombs), 10, COLOR_WHITE, COLOR_BLACK, 1);
	lcd.drawText(margin + boxSizeX + middleSpace + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + 20, "+", COLOR_WHITE, COLOR_FINE_GREEN, 2);
	lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2), margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawText(margin + (boxSizeX / 2) + 45, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace + 15, "BACK", COLOR_WHITE, COLOR_BLACK, 2);
}

void levelSelect(MI0283QT9 lcd)
{
	lcd.fillScreen(COLOR_BLACK);
	//Y row = 1
	lcd.drawText(margin + 5, margin + 5, "LEVEL SELECT", COLOR_WHITE, COLOR_BLACK, 3);
	//Y row = 2
	lcd.drawRect(margin, margin + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawRect(margin + (boxSizeX / 2), margin + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawRect(margin + boxSizeX + middleSpace, margin + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2), margin + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawText(margin + 25, margin + boxSizeY + middleSpace + 20, "1", COLOR_WHITE, COLOR_BLACK, 2);
	lcd.drawText(margin + (boxSizeX / 2) + 25, margin + boxSizeY + middleSpace + 20, "2", COLOR_WHITE, COLOR_BLACK, 2);
	lcd.drawText(margin + boxSizeX + middleSpace + 30, margin + boxSizeY + middleSpace + 20, "3", COLOR_WHITE, COLOR_BLACK, 2);
	lcd.drawText(margin + boxSizeX + middleSpace + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 20, "4", COLOR_WHITE, COLOR_BLACK, 2);
	//Y row = 3
	lcd.drawRect(margin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawRect(margin + boxSizeX + middleSpace, margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawText(margin + 25, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + 20, "RANDOM", COLOR_WHITE, COLOR_BLACK, 2);
	lcd.drawText(margin + boxSizeX + middleSpace + 35, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + 20, "BACK", COLOR_WHITE, COLOR_BLACK, 2);
	lcd.drawText(0, 227, "Bomberman version 0.1", COLOR_WHITE, COLOR_BLACK, 1); // Version tekst
}

void menu(MI0283QT9 lcd, uint8_t* stage, uint8_t* level, unsigned char eeprom_Storagearray[12], uint8_t* playerSpeed, uint8_t* max_bombs, uint8_t* counter, uint8_t* newHighscore, uint8_t dataReady_IR, volatile uint16_t* IRdata, volatile uint8_t* isSendingIR, uint8_t* menucounter, uint8_t buffer[], uint8_t* x, uint8_t* y, uint8_t* isPressed, uint8_t* menuSelect)
{
	for (;;)
	{
		read_Nunchuck(buffer, x, y, isPressed);
		calculateSelectedMenu(lcd, menucounter, menuSelect, (*x), (*y));
		_delay_ms(1);
		if(dataReady_IR) {
			if(processMenuData_IR(stage, level, IRdata)) {
				break;
			}
		}
		set_Brightness(lcd, 7);
		if ((*menucounter) == 0) { //START SCREEN
			if ((*isPressed)) {
				(*menuSelect) = 1;
				(*isPressed) = 0;
				mainMenu(lcd);
				(*menucounter) = 1;
			}
		}
		if ((*menucounter) == 1) { //MAIN MENU
			if ((*menuSelect) == 1 && (*isPressed)) {
				(*isPressed) = 0;
				levelSelect(lcd);
				(*menucounter) = 2;
				(*menuSelect) = 5;
			}
			else if ((*menuSelect) == 2 && (*isPressed)) {
				(*isPressed) = 0;
				(*menuSelect) = 11;
				options(lcd, playerSpeed, max_bombs);
				(*menucounter) = 3;
			}
			else if ((*menuSelect) == 3 && (*isPressed)) {
				(*isPressed) = 0;
				highscores(lcd, eeprom_Storagearray, newHighscore);
				(*menucounter) = 4;
			}
		}
		if ((*menucounter) == 2) { //LEVEL SELECT
			//if (touchx >= margin && touchx <= margin + (boxSizeX / 2) && touchy >= margin + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY) { // level 1
			if ((*menuSelect) == 5 && (*isPressed)) {
			(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 1;
				// send over level
				send_IR(isSendingIR, LEVEL, 127, 1);
				break;
			}
			//if (touchx >= margin + (boxSizeX / 2) && touchx <= margin + (boxSizeX / 2) + (boxSizeX / 2) && touchy >= margin + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY) { // level 2
			if ((*menuSelect) == 6 && (*isPressed)) {
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 2;
				// send over level
				send_IR(isSendingIR, LEVEL, 127, 2);
				break;
			}
			//if (touchx >= margin + boxSizeX + middleSpace && touchx <= margin + boxSizeX + middleSpace + (boxSizeX / 2) && touchy >= margin + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY) { // level 3
			if ((*menuSelect) == 7 && (*isPressed)) {
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 3;
				// send over level
				send_IR(isSendingIR, LEVEL, 127, 3);
				break;
			}
			//if (touchx >= margin + boxSizeX + middleSpace + (boxSizeX / 2) && touchx <= margin + boxSizeX + middleSpace + (boxSizeX / 2) + (boxSizeX / 2) && touchy >= 60 && touchy <= 160) { // level random 180, 60, 120, 100
			if ((*menuSelect) == 8 && (*isPressed)) {
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 5; // moet straks random level zijn, niet het test level
			}
			//if (touchx >= margin && touchx <= margin + boxSizeX && touchy >= margin + boxSizeY + middleSpace + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY) { // level random 180, 60, 120, 100
			if ((*menuSelect) == 9 && (*isPressed)) {
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 0; // moet straks random level zijn, niet het test level
				// send over level
				send_IR(isSendingIR, LEVEL, 127, 0);
				break;
			}
			//if (touchx >= margin + boxSizeX + middleSpace && touchx <= margin + boxSizeX + middleSpace + boxSizeX && touchy >= margin + boxSizeY + middleSpace + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY) { // back to menu
			if ((*menuSelect) == 10 && (*isPressed)) {
				(*menucounter) = 0;
			}
		}
		/*if ((*menucounter) == 3) { //SETTINGS
			//if (touchx >= margin && touchx <= margin + (boxSizeX / 2) && touchy >= margin + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY) { // pressed on - button
			if ((*menuSelect) == 11 && (*isPressed)) {
				if ((*playerSpeed) < 85 && (*playerSpeed) >= 0) {
					(*playerSpeed)++;
					//Serial.println((*playerSpeed));
					lcd.fillRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, (boxSizeX - 60), (boxSizeY / 10), COLOR_BLACK);
					lcd.drawRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, (boxSizeX - 60), (boxSizeY / 10), COLOR_FINE_BLUE);
					lcd.fillRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, (boxSizeX - 60) - (*playerSpeed), (boxSizeY / 10), COLOR_FINE_ORANGE);
				}
			}

			//if (touchx >= margin + (boxSizeX / 2) + middleSpace + boxSizeX && touchx <= margin + (boxSizeX / 2) + middleSpace + boxSizeX + (boxSizeX / 2) && touchy >= margin + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY) { // pressed on - button
			if ((*menuSelect) == 12 && (*isPressed)) {
				if ((*playerSpeed) <= 85 && (*playerSpeed) > 0) {
					lcd.fillRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, (boxSizeX - 60), (boxSizeY / 10), COLOR_BLACK);
					lcd.drawRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, (boxSizeX - 60), (boxSizeY / 10), COLOR_FINE_BLUE);
					lcd.fillRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, ((boxSizeX - 60) - (*playerSpeed)) + 1, (boxSizeY / 10), COLOR_FINE_ORANGE);
					(*playerSpeed)--;
					//Serial.println((*playerSpeed));
				}
			}

			//if (touchx >= margin && touchx <= margin + (boxSizeX / 2) && touchy >= margin + boxSizeY + middleSpace + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY + middleSpace + (boxSizeY)) { // pressed on - button
			if ((*menuSelect) == 13 && (*isPressed)) {
				if ((*counter) == 0) {
					if ((*max_bombs) > 1) {
						(*max_bombs)--;
						lcd.drawInteger(margin + (boxSizeX / 2) + 70, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + 30, (*max_bombs), 10, COLOR_WHITE, COLOR_BLACK, 1);
					}
				}
				(*counter)++;
				if ((*counter) == 252) {
					(*counter) = 0;
				}
			}
			//if (touchx >= margin + (boxSizeX / 2) + middleSpace + boxSizeX && touchx <= margin + (boxSizeX / 2) + middleSpace + boxSizeX + (boxSizeX / 2) && touchy >= margin + boxSizeY + middleSpace + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY + middleSpace + (boxSizeY)) { // pressed on - button
			if ((*menuSelect) == 14 && (*isPressed)) {
				if ((*counter) == 0) {
					if ((*max_bombs) < 5) {
						(*max_bombs)++;
						lcd.drawInteger(margin + (boxSizeX / 2) + 70, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + 30, (*max_bombs), 10, COLOR_WHITE, COLOR_BLACK, 1);
					}
				}
				(*counter)++;
				if ((*counter) == 252) {
					(*counter) = 0;
				}
			}
			//lcd.fillRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, (boxSizeX - 60) - (*playerSpeed), (boxSizeY / 10), COLOR_FINE_ORANGE);
			//if (touchx >= margin + (boxSizeX / 2) + (middleSpace / 2) && touchx <= margin + (boxSizeX / 2) + (middleSpace / 2) + boxSizeX && touchy >= margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY) { // back to menu
			if ((*menuSelect) == 15 && (*isPressed)) {
				(*menucounter) = 0;
			}
		}
		if ((*menucounter) == 4) { //HIGHSCORES
			//if (touchx >= margin + (boxSizeX / 2) + (middleSpace / 2) && touchx <= margin + (boxSizeX / 2) + (middleSpace / 2) + boxSizeX && touchy >= margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY) { // back to menu
			if ((*menuSelect) == 16 && (*isPressed)) {
				(*menucounter) = 0;
			}
			if ((*menuSelect) == 17 && (*isPressed)) {
				(*menucounter) = 0;
			}
		}*/
	}
}

void calculateSelectedMenu(MI0283QT9 lcd, uint8_t* menucounter, uint8_t* menuSelect, uint8_t joy_x_axis, uint8_t joy_y_axis) {
	/*
	MENU SELECT BUTTONS
	-1 START
	-2 SETTINGS (CHEATS)
	-3 SCORES
	-4 ABOUT
	-5 BACK

	-11 LEVEL 1
	-12 LEVEL 2
	-12 LEVEL 3
	-13 LEVEL 4
	-14 LEVEL RANDOM

	-21 ENTER SCORE NAME
	*/

	/*
	ACTIVE MENU SELECTION
	-0 START
	-1 MAIN
	-2 START
	-3 SETTINGS
	-4 SCORES
	-5 ABOUT

	*/
	//MENUCOUNTER == MAIN MENU
	if ((*menucounter) == 1) {
		//CHECK MOVEMENTS WITH NUNCHUCK - MAIN MENU
		if ((*menuSelect) == 1) {
			lcd.drawRect(margin - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); // Upper-Bottom Rectangle
		}
		//NUNCHUCK TO RIGHT
		if (joy_x_axis > 140 && (*menuSelect) == 1) { //Nunchuck moved to the right
			(*menuSelect) = 2;
			lcd.drawRect(margin - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE);
		}
		if (joy_x_axis > 140 && (*menuSelect) == 3) { //Nunchuck moved to the right
			(*menuSelect) = 4;
			lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); // Upper-Bottom Rectangle
		}

		//NUNCHUCK TO LEFT
		if (joy_x_axis < 114 && (*menuSelect) == 2) { //Nunchuck moved to the left
			(*menuSelect) = 1;
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
			lcd.drawRect(margin - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); // Upper-Bottom Rectangle
		}
		if (joy_x_axis < 114 && (*menuSelect) == 4) { //Nunchuck moved to the left
			(*menuSelect) = 3;
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
			lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); // Upper-Bottom Rectangle
		}

		//NUNCHUCK DOWN
		if (joy_y_axis < 114 && (*menuSelect) == 1) { //Nunchuck moved down
			(*menuSelect) = 3;
			lcd.drawRect(margin - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
			lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE);
		}
		if (joy_y_axis < 114 && (*menuSelect) == 2) { //Nunchuck moved down
			(*menuSelect) = 4;
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE);
		}

		//NUNCHUCK UP
		if (joy_y_axis > 140 && (*menuSelect) == 3) { //Nunchuck moved to the left
			(*menuSelect) = 1;
			lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
			lcd.drawRect(margin - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE);
		}
		if (joy_y_axis > 140 && (*menuSelect) == 4) { //Nunchuck moved up
			(*menuSelect) = 2;
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE);
		}
	}
	//MENUCOUNTER == LEVEL SELECT
	if ((*menucounter) == 2) {
		if ((*menuSelect) == 5) {
			lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); // Upper-Bottom Rectangle
		}
		//NUNCHUCK TO RIGHT
		if (joy_x_axis > 140 && (*menuSelect) == 5) { //Nunchuck moved to the right
			(*menuSelect) = 6;
			lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 5
			lcd.drawRect(margin + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 6
		}
		if (joy_x_axis > 180 && (*menuSelect) == 6) { //Nunchuck moved to the right
			(*menuSelect) = 7;
			lcd.drawRect(margin + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 6
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 7
		}
		if (joy_x_axis > 140 && (*menuSelect) == 7) { //Nunchuck moved to the right
			(*menuSelect) = 8;
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 7
			lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 8
		}
		if (joy_x_axis > 140 && (*menuSelect) == 9) { //Nunchuck moved to the right
			(*menuSelect) = 10;
			lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 9
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 10
		}
		//NUNCHUCK TO LEFT
		if (joy_x_axis < 114 && (*menuSelect) == 8) { //Nunchuck moved to the right
			(*menuSelect) = 7;
			lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 8
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 7
		}
		if (joy_x_axis < 114 && (*menuSelect) == 7) { //Nunchuck moved to the right
			(*menuSelect) = 6;
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 7
			lcd.drawRect(margin + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 6
		}
		if (joy_x_axis < 114 && (*menuSelect) == 6) { //Nunchuck moved to the right
			(*menuSelect) = 5;
			lcd.drawRect(margin + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 6
			lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 5
		}
		if (joy_x_axis < 114 && (*menuSelect) == 10) { //Nunchuck moved to the right
			(*menuSelect) = 9;
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 10
			lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 9
		}
		//NUNCHUCK DOWN
		if (joy_y_axis < 114 && (*menuSelect) == 5) { //Nunchuck moved down
			(*menuSelect) = 9;
			lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 5
			lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 9
		}
		if (joy_y_axis < 114 && (*menuSelect) == 6) { //Nunchuck moved down
			(*menuSelect) = 9;
			lcd.drawRect(margin + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 6
			lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 9
		}
		if (joy_y_axis < 114 && (*menuSelect) == 7) { //Nunchuck moved down
			(*menuSelect) = 10;
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 7
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 10
		}
		if (joy_y_axis < 114 && (*menuSelect) == 8) { //Nunchuck moved down
			(*menuSelect) = 10;
			lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 8
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 10
		}

		//NUNCHUCK UP
		if (joy_y_axis > 140 && (*menuSelect) == 9) { //Nunchuck moved to the left
			(*menuSelect) = 5;
			lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 9
			lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 5
		}
		if (joy_y_axis > 140 && (*menuSelect) == 10) { //Nunchuck moved up
			(*menuSelect) = 7;
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 10
			lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 7
		}
	}
}
/*
lcd.fillScreen(COLOR_BLACK);
//Y row = 1
lcd.drawText(margin + 5, margin + 5, "LEVEL SELECT", COLOR_WHITE, COLOR_BLACK, 3);
//Y row = 2
lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_BLUE); //MenuSelect 5
lcd.drawRect(margin + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_BLUE); //MenuSelect 6
lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_BLUE); //MenuSelect 7
lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_BLUE); //MenuSelect 8
lcd.drawText(margin + 25, margin + boxSizeY + middleSpace + 20, "1", COLOR_WHITE, COLOR_BLACK, 2);
lcd.drawText(margin + (boxSizeX / 2) + 25, margin + boxSizeY + middleSpace + 20, "2", COLOR_WHITE, COLOR_BLACK, 2);
lcd.drawText(margin + boxSizeX + middleSpace + 30, margin + boxSizeY + middleSpace + 20, "3", COLOR_WHITE, COLOR_BLACK, 2);
lcd.drawText(margin + boxSizeX + middleSpace + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 20, "4", COLOR_WHITE, COLOR_BLACK, 2);
//Y row = 3
lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_BLUE); //MenuSelect 9
lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_BLUE); //MenuSelect 10
lcd.drawText(margin + 25, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + 20, "RANDOM", COLOR_WHITE, COLOR_BLACK, 2);
lcd.drawText(margin + boxSizeX + middleSpace + 35, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + 20, "BACK", COLOR_WHITE, COLOR_BLACK, 2);
lcd.drawText(0, 227, "Bomberman version 0.1", COLOR_WHITE, COLOR_BLACK, 1); // Version tekst
*/