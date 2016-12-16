#include "Menu.h"
uint8_t margin = 10, boxSizeX = 145, boxSizeY = 52, middleSpace = 10; //Has to be 320 together for x and 240 together for y;

void startScherm(MI0283QT9 lcd, uint8_t* stage)
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
			lcd.drawText(25, 200, "Touch to continue", RGB(0, 0, 127), COLOR_BLACK, 2);
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
		if (lcd.touchRead()) {
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

void highscores(MI0283QT9 lcd, unsigned int eeprom_Storagearray[2])
{
	lcd.fillScreen(RGB(255, 255, 255));
	lcd.drawText(40, 20, "Highscores", (RGB(0, 0, 0)), (RGB(255, 255, 255)), 3);
	uint8_t a, b, c;
	lcd.drawText(120, 100, "Scores", RGB(255, 255, 255), RGB(0, 0, 0), 1);
	a = lcd.drawText(120, 120, "Player ", RGB(255, 255, 255), RGB(0, 0, 0), 1);
	b = lcd.drawInteger(a, 120, 1, 10, RGB(255, 255, 255), RGB(0, 0, 0), 1);
	c = lcd.drawText(b, 120, ": ", RGB(255, 255, 255), RGB(0, 0, 0), 1);
	lcd.drawInteger(c, 120, read_eeprom_word(&eeprom_Storagearray[0]), 10, RGB(255, 255, 255), RGB(0, 0, 0), 1);

	//a = lcd.drawText(120, 140, "Player ", RGB(255, 255, 255), RGB(0, 0, 0), 1);
	//b = lcd.drawInteger(a, 140, player_scoreArray[2], 10, RGB(255, 255, 255), RGB(0, 0, 0), 1);
	//c = lcd.drawText(b, 140, ": ", RGB(255, 255, 255), RGB(0, 0, 0), 1);
	//lcd.drawInteger(c, 140, (*score2), 10, RGB(255, 255, 255), RGB(0, 0, 0), 1);
}

void options(MI0283QT9 lcd, uint8_t* playerSpeed)
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
	lcd.drawText(margin + boxSizeX + middleSpace + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 20, "+", COLOR_WHITE, COLOR_FINE_GREEN, 2);
	//Y row = 3
	lcd.drawRect(margin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.fillRect(margin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_RED); // Upper-Bottom Rectangle
	lcd.drawRect(margin + (boxSizeX / 2) + middleSpace / 2, margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2), margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.fillRect(margin + boxSizeX + middleSpace + (boxSizeX / 2), margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_GREEN); // Upper-Bottom Rectangle
	lcd.drawText(margin + 30, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + 20, "-", COLOR_WHITE, COLOR_FINE_RED, 2);
	lcd.drawText(margin + (boxSizeX / 2) + 25, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + 10, "maxium bombs", COLOR_WHITE, COLOR_BLACK, 1);
	lcd.drawText(margin + boxSizeX + middleSpace + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + 20, "+", COLOR_WHITE, COLOR_FINE_GREEN, 2);
	lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2), margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawText(margin + (boxSizeX / 2) + 45, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace + 15, "BACK", COLOR_WHITE, COLOR_BLACK, 2);
}

void levelSelect(MI0283QT9 lcd)
{
	/*
	lcd.fillScreen(RGB(255, 255, 255));
	lcd.drawText(10, 10, "Level Select", (RGB(0, 0, 0)), (RGB(255, 255, 255)), 3);
	level1(lcd);
	level2(lcd);
	level3(lcd);
	levelRandom(lcd);
	backToMenu(lcd);
	*/

	lcd.fillScreen(COLOR_BLACK);
	//Y row = 1
	/*lcd.drawRect(margin, margin, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawRect(margin + boxSizeX + middleSpace, margin, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	*/
	lcd.drawText(margin + 5, margin + 5, "LEVEL SELECT", COLOR_WHITE, COLOR_BLACK, 3);
	
	//lcd.drawText(margin + boxSizeX + middleSpace + 12, margin + 20, "SETTINGS", COLOR_WHITE, COLOR_BLACK, 2);
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

void menu(MI0283QT9 lcd, uint8_t* stage, uint8_t* level, unsigned int eeprom_Storagearray[2], uint8_t* playerSpeed)
{
	uint8_t menucounter = 0;
	uint16_t touchx, touchy;
	for (;;)
	{
		set_Brightness(lcd, 7);
		touchx = 0;
		touchy = 0;
		if (menucounter == 0 /*&& lcd.touchRead()*/) {
			mainMenu(lcd);
			menucounter = 1;
		}
		if (menucounter == 1 && lcd.touchRead()) {
			touchx = lcd.touchX();
			touchy = lcd.touchY();
			if (touchx >= margin && touchx <= margin + boxSizeX && touchy >= margin && touchy <= margin + boxSizeY) // Level select
			{
				levelSelect(lcd);
				menucounter = 2;
			}
			else if (touchx >= margin + boxSizeX + middleSpace && touchx <= margin + boxSizeX + middleSpace + boxSizeX && touchy >= margin && touchy <= margin + boxSizeY) // Options
			{
				options(lcd, playerSpeed);
				menucounter = 3;
			}
			else if (touchx >= margin && touchx <= margin + boxSizeX && touchy >= margin + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY) // Highscores
			{
				highscores(lcd, eeprom_Storagearray);
				menucounter = 4;
			}
		}
		if (menucounter == 2 && lcd.touchRead()) {
			touchx = lcd.touchX();
			touchy = lcd.touchY();
			if (touchx >= margin && touchx <= margin + (boxSizeX / 2) && touchy >= margin + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY) { // level 1
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 1;
				break;
			}
			if (touchx >= margin + (boxSizeX / 2) && touchx <= margin + (boxSizeX / 2) + (boxSizeX / 2) && touchy >= margin + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY) { // level 2
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 2;
				break;
			}
			if (touchx >= margin + boxSizeX + middleSpace && touchx <= margin + boxSizeX + middleSpace + (boxSizeX / 2) && touchy >= margin + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY) { // level 3
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 3;
				break;
			}
			if (touchx >= margin + boxSizeX + middleSpace + (boxSizeX / 2) && touchx <= margin + boxSizeX + middleSpace + (boxSizeX / 2) + (boxSizeX / 2) && touchy >= 60 && touchy <= 160) { // level random 180, 60, 120, 100
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 4; // moet straks random level zijn, niet het test level
			}
			if (touchx >= margin && touchx <= margin + boxSizeX && touchy >= margin + boxSizeY + middleSpace + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY) { // level random 180, 60, 120, 100
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 0; // moet straks random level zijn, niet het test level
				break;
			}
			if (touchx >= margin + boxSizeX + middleSpace && touchx <= margin + boxSizeX + middleSpace + boxSizeX && touchy >= margin + boxSizeY + middleSpace + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY) { // back to menu
				menucounter = 0;
			}
		}
		if (menucounter == 3 && lcd.touchRead()) {
			touchx = lcd.touchX();
			touchy = lcd.touchY();
			if (touchx >= margin && touchx <= margin + (boxSizeX / 2) && touchy >= margin + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY) { // pressed on - button
				(*playerSpeed)--;
				lcd.fillRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, (5), (boxSizeY / 10), COLOR_FINE_ORANGE);
			}
			if (touchx >= margin + (boxSizeX / 2) + (middleSpace / 2) && touchx <= margin + (boxSizeX / 2) + (middleSpace / 2) + boxSizeX + boxSizeX && touchy >= margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY) { // back to menu
				menucounter = 0;
			}
		}
		if (menucounter == 4 && lcd.touchRead()) {
			touchx = lcd.touchX();
			touchy = lcd.touchY();
			if (touchx >= margin + boxSizeX + middleSpace && touchx <= margin + boxSizeX + middleSpace + boxSizeX && touchy >= margin + boxSizeY + middleSpace + boxSizeY + middleSpace && touchy <= margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY) { // back to menu
				menucounter = 0;
			}
		}
	}
}

