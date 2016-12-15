#include "Menu.h"

void startScherm(MI0283QT9 lcd, uint8_t* stage)
{
	uint8_t toggle1 = 0, toggle2 = 0, drawfreq = 0, redraw = 1;
	//Background
	lcd.fillScreen(RGB(127, 127, 127));
	//Titel
	lcd.drawText(15, 40, "B MBERMAN", RGB(0, 0, 127), RGB(127, 127, 127), 4);
	//Bomb
	lcd.fillCircle(60, 54, 16, RGB(0, 0, 0));
	lcd.fillCircle(54, 46, 2, RGB(127, 127, 127));
	lcd.fillCircle(52, 48, 2, RGB(127, 127, 127));
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
			lcd.fillRect(44, 18, 14, 11, RGB(127, 127, 127));
			lcd.fillRect(52, 24, 6, 5, RGB(127, 80, 0));
			lcd.fillTriangle(48, 28, 48, 18, 57, 22, RGB(255, 127, 0));
			lcd.fillTriangle(53, 28, 53, 18, 44, 22, RGB(255, 0, 0));
			toggle1 = 0;
		}
		else {
			lcd.fillRect(44, 18, 14, 11, RGB(127, 127, 127));
			lcd.fillRect(52, 24, 6, 5, RGB(127, 80, 0));
			lcd.fillTriangle(50, 18, 46, 25, 55, 25, RGB(255, 127, 0));
			lcd.fillTriangle(50, 28, 46, 20, 55, 20, RGB(255, 0, 0));
			toggle1 = 1;
		}
		if ((!toggle2) && redraw) {//Elke 10e loop toggle tekst aan en uit (en teken het maar 1 keer)
			lcd.drawText(25, 200, "Touch to continue", RGB(0, 0, 127), RGB(127, 127, 127), 2);
			redraw = 0;
		}
		else if (toggle2 && redraw) {
			lcd.fillRect(25, 200, 268, 15, RGB(127, 127, 127));
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


void menuLevelSelect(MI0283QT9 lcd)
{
	lcd.fillRect(80, 20, 160, 50, (RGB(0, 0, 0)));
	lcd.drawText(105, 35, "Level", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 3);
	/*lcd.fillCircle(40, 35, 5, COLOR_FINE_RED); // Top left circle
	lcd.fillCircle(40, 35 + 34, 5, COLOR_FINE_RED); // Bottom left circle
	lcd.fillCircle(40 + 235, 35, 5, COLOR_FINE_RED); // Top right circle
	lcd.fillCircle(40 + 235, 35 + 34, 5, COLOR_FINE_RED); // Bottom right circle
	lcd.fillRect(40, 35 - 5, 40 + 235, 35 + 34 + 5, COLOR_FINE_RED); // Upper-Bottom Rectangle
	lcd.fillRect(40 - 5, 35, 40 + 235 + 5, 35 + 34, COLOR_FINE_RED); // Left-Right Rectangle
	lcd.drawText(40, 35, "Start game", COLOR_WHITE, COLOR_FINE_RED, 3); // Button tekst
																		 // Options button
																		 */
}


void menuHighscores(MI0283QT9 lcd)
{
	lcd.fillRect(40, 100, 250, 50, (RGB(0, 0, 0)));
	lcd.drawText(50, 115, "Highscores", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 3);
	/*
	lcd.fillCircle(75, 100, 5, COLOR_FINE_GREEN); // Top left circle;
	lcd.fillCircle(75, 100 + 34, 5, COLOR_FINE_GREEN); // Bottom left circle
	lcd.fillCircle(75 + 165, 100, 5, COLOR_FINE_GREEN); // Top right circle
	lcd.fillCircle(75 + 165, 100 + 34, 5, COLOR_FINE_GREEN); // Bottom right circle
	lcd.fillRect(75, 100 - 5, 75 + 165, 100 + 34 + 5, COLOR_FINE_GREEN); // Upper-Bottom Rectangle
	lcd.fillRect(75 - 5, 100, 75 + 165 + 5, 100 + 34, COLOR_FINE_GREEN); // Left-Right Rectangle
	lcd.drawText(75, 100, "Options", COLOR_WHITE, COLOR_FINE_GREEN, 3); // Button tekst
																		// Highscores button
																		*/
}


void menuOptions(MI0283QT9 lcd)
{
	lcd.fillRect(65, 180, 185, 50, (RGB(0, 0, 0)));
	lcd.drawText(80, 195, "Options", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 3);

	//lcd.fillCircle(40, 165, 5, COLOR_FINE_ORANGE); // Top left circle
	//lcd.fillCircle(40, 165 + 34, 5, COLOR_FINE_ORANGE); // Bottom left circle
	//lcd.fillCircle(40 + 235, 165, 5, COLOR_FINE_ORANGE); // Top right circle
	//lcd.fillCircle(40 + 235, 165 + 34, 5, COLOR_FINE_ORANGE); // Bottom right circle
	/*
	lcd.fillRect(5, 5, 155, 54, COLOR_FINE_ORANGE); // Upper-Bottom Rectangle
	lcd.fillRect(155 + 5 + 10, 5, 165, 54, COLOR_FINE_ORANGE); // Upper-Bottom Rectangle
	lcd.fillRect(5, 5, 155, 54, COLOR_FINE_ORANGE); // Upper-Bottom Rectangle
	lcd.fillRect(155 + 5 + 10, 59, 165, 108, COLOR_FINE_ORANGE); // Upper-Bottom Rectangle
	lcd.drawText(40, 165, "Highscores", COLOR_WHITE, COLOR_FINE_ORANGE, 3); // Button tekst
																			// Version number
	lcd.drawText(0, 227, "Bomberman version 0.1", COLOR_WHITE, COLOR_FINE_BLUE, 1); // Version tekst
	*/
}


void Highscores(MI0283QT9 lcd, unsigned int eeprom_Storagearray[2])
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
	backToMenu(lcd);
}



void options(MI0283QT9 lcd)
{
	lcd.fillScreen(RGB(255, 255, 255));
	lcd.drawText(55, 20, "Options", (RGB(0, 0, 0)), (RGB(255, 255, 255)), 3);
	backToMenu(lcd);
}


void menuScherm(MI0283QT9 lcd)
{
	lcd.fillScreen(RGB(255, 255, 255));
	menuLevelSelect(lcd);
	menuHighscores(lcd);
	menuOptions(lcd);
	//menuHighscores(lcd);
}


void levelSelect(MI0283QT9 lcd)
{
	lcd.fillScreen(RGB(255, 255, 255));
	lcd.drawText(10, 10, "Level Select", (RGB(0, 0, 0)), (RGB(255, 255, 255)), 3);
	level1(lcd);
	level2(lcd);
	level3(lcd);
	levelRandom(lcd);
	backToMenu(lcd);
}


void level1(MI0283QT9 lcd)
{
	lcd.fillRect(20, 60, 120, 30, (RGB(0, 0, 0)));
	lcd.drawText(28, 65, "Level 1", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 2);
}


void level2(MI0283QT9 lcd)
{
	lcd.fillRect(20, 120, 120, 30, (RGB(0, 0, 0)));
	lcd.drawText(28, 125, "Level 2", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 2);
}


void level3(MI0283QT9 lcd)
{
	lcd.fillRect(20, 180, 120, 30, (RGB(0, 0, 0)));
	lcd.drawText(28, 185, "Level 3", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 2);
}


void levelRandom(MI0283QT9 lcd)
{
	lcd.fillRect(180, 60, 120, 100, (RGB(0, 0, 0)));
	lcd.drawText(188, 65, "Random", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 2);
	lcd.drawText(188, 90, "Gene-", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 2);
	lcd.drawText(188, 105, "rated", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 2);
	lcd.drawText(188, 130, "Level", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 2);
}


void backToMenu(MI0283QT9 lcd)
{
	lcd.fillRect(180, 200, 100, 30, (RGB(0, 0, 0)));
	lcd.drawText(188, 205, "Menu", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 2);
}


void menu(MI0283QT9 lcd, uint8_t* stage, uint8_t* level, unsigned int eeprom_Storagearray[2])
{
	uint8_t menucounter = 0;
	uint16_t touchx, touchy;
	for (;;)
	{
		set_Brightness(lcd, 7);
		touchx = 0;
		touchy = 0;
		if (menucounter == 0 /*&& lcd.touchRead()*/) {
			menuScherm(lcd);
			menucounter = 1;
		}
		if (menucounter == 1 && lcd.touchRead()) {
			touchx = lcd.touchX();
			touchy = lcd.touchY();
			if (touchx >= 80 && touchx <= 240 && touchy >= 20 && touchy <= 70) // Level select
			{
				levelSelect(lcd);
				menucounter = 2;
			}
			else if (touchx >= 65 && touchx <= 270 && touchy >= 180 && touchy <= 230) // Options
			{
				options(lcd);
				menucounter = 3;
			}
			else if (touchx >= 40 && touchx <= 290 && touchy >= 100 && touchy <= 150) // Highscores
			{
				Highscores(lcd, eeprom_Storagearray);
				menucounter = 4;
			}
		}
		if (menucounter == 2 && lcd.touchRead()) {
			touchx = lcd.touchX();
			touchy = lcd.touchY();
			if (touchx >= 20 && touchx <= 120 && touchy >= 60 && touchy <= 90) { // level 1
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 4;
				break;
			}
			if (touchx >= 20 && touchx <= 120 && touchy >= 120 && touchy <= 150) { // level 2
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 2;
				break;
			}
			if (touchx >= 20 && touchx <= 120 && touchy >= 180 && touchy <= 210) { // level 3
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 3;
				break;
			}
			if (touchx >= 180 && touchx <= 300 && touchy >= 60 && touchy <= 160) { // level random 180, 60, 120, 100
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 0; // moet straks random level zijn, niet het test level
				break;
			}
			if (touchx >= 180 && touchx <= 250 && touchy >= 200 && touchy <= 230) { // back to menu
				menucounter = 0;
			}
		}
		if (menucounter == 3 && lcd.touchRead()) {
			touchx = lcd.touchX();
			touchy = lcd.touchY();
			if (touchx >= 180 && touchx <= 250 && touchy >= 200 && touchy <= 230) { // back to menu
				menucounter = 0;
			}
		}
		if (menucounter == 4 && lcd.touchRead()) {
			touchx = lcd.touchX();
			touchy = lcd.touchY();
			if (touchx >= 180 && touchx <= 250 && touchy >= 200 && touchy <= 230) { // back to menu
				menucounter = 0;
			}
		}
	}
}

