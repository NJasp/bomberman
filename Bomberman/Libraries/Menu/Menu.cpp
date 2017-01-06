#include "Menu.h"
#include "../Nunchuck/Nunchuck.h"
#include "../Eeprom/Eeprom.h"

uint8_t margin = 10, boxSizeX = 145, boxSizeY = 52, middleSpace = 10, highlightMargin = 2; //Has to be 320 together for x and 240 together for y;
uint8_t antiZhold = 0;
uint8_t sensitivityRight = 140; //140
uint8_t sensitivityLeft = 114; //114
uint8_t sensitivityLaggScreenRight = 145;
uint8_t sensitivityLaggScreenLeft = 110;
uint8_t charSelectSpeedCounter = 0;
uint8_t lettercounter = 0;
char currentChar = 'A';

void startScherm(MI0283QT9 lcd, uint8_t* stage, uint8_t buffer[], uint8_t* x, uint8_t* y, uint8_t* isPressed, uint8_t* counter)
{
	uint8_t toggle1 = 0, toggle2 = 0, drawfreq = 0, redraw = 1;
	//Background
	lcd.fillScreen(COLOR_BLACK);
	lcd.drawText(15, 40, "B MBERMAN", COLOR_WHITE, COLOR_BLACK, 4);
	//BOMB
	lcd.drawCircle(60, 54, 16, Background);
	lcd.fillCircle(54, 46, 2, COLOR_GREY);
	lcd.fillCircle(52, 48, 2, COLOR_GREY);
	lcd.drawRect(53, 35, 15, 5, Background);
	lcd.fillRect(53, 35, 15, 5, COLOR_BLACK);
	//Lont
	lcd.fillRect(58, 30, 6, 5, COLOR_DARK_YELLOW);
	lcd.fillRect(56, 28, 6, 5, COLOR_DARK_YELLOW);
	lcd.fillRect(54, 26, 6, 5, COLOR_DARK_YELLOW);
	lcd.fillRect(52, 24, 6, 5, COLOR_DARK_YELLOW);
	//Lijnen
	//lcd.drawLine(0, 70, lcd.width(), 70, COLOR_BLACK);
	//lcd.fillRect(0, 115, 50, 50, COLOR_BLACK);
	//lcd.fillRect((lcd.width()-50), 115, 50, 50, COLOR_BLACK);
	//lcd.fillRect(50, 160, (lcd.width()-100), 5, RGB(0,0,255));
	//lcd.drawLine(0, 199, lcd.width(), 199, COLOR_BLACK);
	//lcd.drawLine(0, 30, 20, 0, COLOR_BLACK);
	for (;;) {
		read_Nunchuck(buffer, x, y, isPressed);
		//if (toggle1) {//Elke loop toggle de animatie van het vuur naar een andere
			//lcd.fillRect(44, 18, 14, 11, COLOR_GREY);
			//lcd.fillRect(44, 18, 14, 11, COLOR_BLACK);
			//lcd.fillRect(52, 24, 6, 5, COLOR_DARK_YELLOW);
			//lcd.fillTriangle(48, 28, 48, 18, 57, 22, RGB(255, 127, 0));
			//lcd.fillTriangle(53, 28, 53, 18, 44, 22, RGB(255, 0, 0));
		//	toggle1 = 0;
		//}
		//else {
		//	//lcd.fillRect(44, 18, 14, 11, COLOR_GREY);
		//	lcd.fillRect(44, 18, 14, 11, COLOR_BLACK);
		//	lcd.fillRect(52, 24, 6, 5, COLOR_DARK_YELLOW);
		//	lcd.fillTriangle(50, 18, 46, 25, 55, 25, RGB(255, 127, 0));
		//	lcd.fillTriangle(50, 28, 46, 20, 55, 20, RGB(255, 0, 0));
		//	toggle1 = 1;
		//}
		//if ((!toggle2) && redraw) {//Elke 10e loop toggle tekst aan en uit (en teken het maar 1 keer)
			//lcd.drawText(25, 200, "Touch to continue", RGB(0, 0, 127), COLOR_GREY, 2);
			lcd.drawText(25, 200, " 'Z' to continue", COLOR_WHITE, COLOR_BLACK, 2);
		//	redraw = 0;
		//}
		//else if (toggle2 && redraw) {
			//lcd.fillRect(25, 200, 268, 15, COLOR_GREY);
		//	lcd.fillRect(25, 200, 268, 15, COLOR_BLACK);
		//	redraw = 0;
		//}
		//TOGGLE SETTINGS
		/*if (drawfreq >    100) {//Als er 10 loops voorbij zijn, toggle tekst en reset counter
			redraw = 1;
			drawfreq = 0;
			toggle2 = ~(toggle2);
		}
		else {
			drawfreq++;
		}*/
		if ((*isPressed)) {
			(*stage) = 1;
			break;
		}
	}
}

void mainMenu(MI0283QT9 lcd) {
	//lcd.fillRect(65, 180, 185, 50, (COLOR_BLACK));
	//lcd.drawText(80, 195, "Options", (COLOR_WHITE), (COLOR_BLACK), 3);
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
	//lcd.drawRect(margin + boxSizeX + middleSpace, margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	//lcd.drawText(margin + boxSizeX + middleSpace + 35, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + 20, "BACK", COLOR_WHITE, COLOR_BLACK, 2);
	lcd.drawText(0, 227, "Bomberman version 0.1", COLOR_WHITE, COLOR_BLACK, 1); // Version tekst
}

void highscores(MI0283QT9 lcd, unsigned char eeprom_Storagearray[12], uint8_t* newHighscore)
{
	lcd.fillScreen(COLOR_BLACK);
	lcd.drawText(margin + 15, margin + 5, "HIGH SCORES", COLOR_WHITE, COLOR_BLACK, 3);
	lcd.drawRect(margin + (boxSizeX / 2) + middleSpace / 2, margin + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	uint8_t a, b;
	char playerName[] = { (read_eeprom_word((&eeprom_Storagearray[2]))), (read_eeprom_word((&eeprom_Storagearray[3]))), (read_eeprom_word((&eeprom_Storagearray[4]))), (read_eeprom_word((&eeprom_Storagearray[5]))), '\0' };
	a = lcd.drawText(margin + (boxSizeX / 2) + middleSpace / 2 + 27, margin + boxSizeY + middleSpace + 15, playerName, COLOR_WHITE, COLOR_BLACK, 1);
	b = lcd.drawText(a, margin + boxSizeY + middleSpace + 15, ": ", COLOR_WHITE, COLOR_BLACK, 1);
	lcd.drawInteger(b, margin + boxSizeY + middleSpace + 15, read_eeprom_word(&eeprom_Storagearray[0]), 10, COLOR_WHITE, COLOR_BLACK, 1);
	if ((*newHighscore)) {
		lcd.drawText(margin + (boxSizeX / 2) + middleSpace / 2 + 5, margin + boxSizeY + middleSpace + 30, "touch to add name", COLOR_WHITE, COLOR_BLACK, 1);
		if (read_eeprom_word(&eeprom_Storagearray[2]) != '1') {
			(*newHighscore) = 0;
		}
	}
	lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2), margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawText(margin + (boxSizeX / 2) + 45, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace + 15, "BACK", COLOR_WHITE, COLOR_BLACK, 2);
}

void keyboard(MI0283QT9 lcd) {
	lcd.fillScreen(COLOR_BLACK);
	lcd.drawLine(margin + (boxSizeX / 2) + middleSpace + 4, margin + boxSizeY - 15, margin + (boxSizeX / 2) + middleSpace + 34, margin + boxSizeY - 15, COLOR_WHITE);
	lcd.drawLine(margin + (boxSizeX / 2) + middleSpace + 52, margin + boxSizeY - 15, margin + (boxSizeX / 2) + middleSpace + 82, margin + boxSizeY - 15, COLOR_WHITE);
	lcd.drawLine(margin + (boxSizeX / 2) + middleSpace + 101, margin + boxSizeY - 15, margin + (boxSizeX / 2) + middleSpace + 131, margin + boxSizeY - 15, COLOR_WHITE);
	lcd.drawRect(margin, margin + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.fillRect(margin, margin + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_RED); // Upper-Bottom Rectangle
	lcd.drawRect(margin + (boxSizeX / 2) + middleSpace / 2, margin + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2), margin + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.fillRect(margin + boxSizeX + middleSpace + (boxSizeX / 2), margin + boxSizeY + middleSpace, boxSizeX / 2, boxSizeY, COLOR_FINE_GREEN); // Upper-Bottom Rectangle
	lcd.drawText(margin + 30, margin + boxSizeY + middleSpace + 20, "-", COLOR_WHITE, COLOR_FINE_RED, 2);
	lcd.drawText(margin + (boxSizeX / 2) + middleSpace + boxSizeX + 30, margin + boxSizeY + middleSpace + 20, "+", COLOR_WHITE, COLOR_FINE_GREEN, 2);
	lcd.drawRect(margin + (boxSizeX / 2) + middleSpace / 2, margin + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawText(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + middleSpace + 5, "SELECT", COLOR_WHITE, COLOR_BLACK, 2);
	//Y row = 3
	lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2), margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawText(margin + (boxSizeX / 2) + 45, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace + 15, "BACK", COLOR_WHITE, COLOR_BLACK, 2);
}

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

void about(MI0283QT9 lcd)
{
	lcd.fillScreen(COLOR_BLACK);

	lcd.drawText(margin + 90, margin + 5, "About", COLOR_WHITE, COLOR_BLACK, 3);
	lcd.drawText(margin + 5, margin + 45, "ICT Windesheim", COLOR_WHITE, COLOR_BLACK, 2);
	lcd.drawText(margin + 5, margin + 75, "Made by:", COLOR_WHITE, COLOR_BLACK, 1);
	lcd.drawText(margin + 5, margin + 90, "- Nils Jaspers", COLOR_WHITE, COLOR_BLACK, 1);
	lcd.drawText(margin + 5, margin + 105, "- Koen Sleurink", COLOR_WHITE, COLOR_BLACK, 1);
	lcd.drawText(margin + 5, margin + 120, "- Martijn van Olst", COLOR_WHITE, COLOR_BLACK, 1);
	lcd.drawText(margin + 5, margin + 135, "- Mike Schotman", COLOR_WHITE, COLOR_BLACK, 1);

	lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2), margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace, boxSizeX, boxSizeY, COLOR_FINE_BLUE); // Upper-Bottom Rectangle
	lcd.drawText(margin + (boxSizeX / 2) + 45, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace + 15, "BACK", COLOR_WHITE, COLOR_BLACK, 2);
}

void menu(MI0283QT9 lcd, uint8_t* stage, uint8_t* level, unsigned char eeprom_Storagearray[12], uint8_t* playerSpeed, uint8_t* max_bombs, uint8_t* newHighscore, volatile uint16_t* IRdata, volatile uint8_t* isSendingIR, volatile uint8_t* interruptCounter, uint16_t* seed, uint8_t* menucounter, uint8_t buffer[], uint8_t* x, uint8_t* y, uint8_t* isPressed, uint8_t* menuSelect, uint8_t* counter, uint8_t name[], uint8_t eepromname[], uint8_t* score, uint8_t* lives)
{
	int8_t levelToSend = -1;
	for (;;)
	{
		read_Nunchuck(buffer, x, y, isPressed);
		calculateSelectedMenu(lcd, menucounter, menuSelect, (*x), (*y));

		// receiving levels
		if(dataReady_IR()) {
			if(processMenuData_IR(stage, level, IRdata, isPressed, seed)) {
				lcd.fillScreen(Background);
				break;
			}
		}

		//set_Brightness(lcd, 7);
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
				(*menuSelect) = 11;
			}
			else if ((*menuSelect) == 3 && (*isPressed)) {
				(*isPressed) = 0;
				highscores(lcd, eeprom_Storagearray, newHighscore);
				(*menucounter) = 4;
				(*menuSelect) = 16;
			}
			else if ((*menuSelect) == 4 && (*isPressed)) {
				(*isPressed) = 0;
				about(lcd);
				(*menucounter) = 6;
				(*menuSelect) = 21;
			}
		}
		if ((*menucounter) == 2) { //LEVEL SELECT
			if ((*menuSelect) == 5 && (*isPressed)) {
				(*isPressed) = 0;
				(*stage) = 2;
				(*level) = 1;
				// send over level
				levelToSend = 1;
			} else if ((*menuSelect) == 6 && (*isPressed)) {
				(*isPressed) = 0;
				(*stage) = 2;
				(*level) = 2;
				// send over level
				levelToSend = 2;
			} else if ((*menuSelect) == 7 && (*isPressed)) {
				(*isPressed) = 0;
				(*stage) = 2;
				(*level) = 3;
				// send over level
				levelToSend = 3;
			} else if ((*menuSelect) == 8 && (*isPressed)) {
				(*isPressed) = 0;
				(*stage) = 2;
				(*level) = 5;
				levelToSend = 5;
			} else if ((*menuSelect) == 9 && (*isPressed)) {
				(*isPressed) = 0;
				(*stage) = 2;
				(*level) = 0; // random level
				levelToSend = 0;
			} else if ((*menuSelect) == 10 && (*isPressed)) {
				(*isPressed) = 0;
				(*menucounter) = 0;
			}

			// sending levels
			if(*interruptCounter >= 100){
				// random level
				if(levelToSend == 0){
					*seed = 0;
					*isPressed = 0;
					*stage = 2;
					lcd.fillScreen(Background);
					break;
				}
				// normal level
				else if(levelToSend > 0){
					*isPressed = 0;
					*stage = 2;
					*level = levelToSend;
					send_IR(isSendingIR, LEVEL, 127, levelToSend);
					lcd.fillScreen(Background);
					break;
				}

				// noise to keep sensor calibrated
				send_IR(isSendingIR, 0, 0, 0);
				*interruptCounter = 0;
			}
			*interruptCounter++;
		}


		if ((*menucounter) == 3) { //SETTINGS
			if ((*menuSelect) == 11 && (*isPressed)) {
				(*isPressed) = 0;
				if ((*playerSpeed) < 85 && (*playerSpeed) >= 0) {
					(*playerSpeed)++;
					lcd.fillRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, (boxSizeX - 60), (boxSizeY / 10), COLOR_BLACK);
					lcd.drawRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, (boxSizeX - 60), (boxSizeY / 10), COLOR_FINE_BLUE);
					lcd.fillRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, (boxSizeX - 60) - (*playerSpeed), (boxSizeY / 10), COLOR_FINE_ORANGE);
				}
			} else if ((*menuSelect) == 12 && (*isPressed)) {
				(*isPressed) = 0;
				if ((*playerSpeed) <= 85 && (*playerSpeed) > 0) {
					lcd.fillRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, (boxSizeX - 60), (boxSizeY / 10), COLOR_BLACK);
					lcd.drawRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, (boxSizeX - 60), (boxSizeY / 10), COLOR_FINE_BLUE);
					lcd.fillRect(margin + (boxSizeX / 2) + 30, margin + boxSizeY + middleSpace + 30, ((boxSizeX - 60) - (*playerSpeed)) + 1, (boxSizeY / 10), COLOR_FINE_ORANGE);
					(*playerSpeed)--;
				}
			} else if ((*menuSelect) == 13 && (*isPressed)) {
				(*isPressed) = 0;
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
			} else if ((*menuSelect) == 14 && (*isPressed)) {
				(*isPressed) = 0;
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
			} else if ((*menuSelect) == 15 && (*isPressed)) {
				(*isPressed) = 0;
				(*menucounter) = 0;
			}
		}
		if ((*menucounter) == 4) { //HIGHSCORES
			if ((*menuSelect) == 16 && (*isPressed)) {
				keyboard(lcd);
				(*menucounter) = 5;
				(*menuSelect) = 18;
				(*isPressed) = 0;
			} else if ((*menuSelect) == 17 && (*isPressed)) {
				(*isPressed) = 0;
				(*menucounter) = 0;
			}
		}
		if ((*menucounter) == 5) { //KEYBOARD
			if (!(*isPressed)) {
				lcd.drawChar(margin + (boxSizeX / 2) + (middleSpace / 2) + (boxSizeX / 2 - 5), margin + boxSizeY + middleSpace + 15, currentChar, COLOR_WHITE, COLOR_BLACK, 2);
			}
			if ((*menuSelect) == 18 && (*isPressed)) {
				(*isPressed) = 0;
				if (currentChar > 'A' && currentChar <= 'Z') {
					if (charSelectSpeedCounter == 0) {
						currentChar--;
						lcd.drawChar(margin + (boxSizeX / 2) + (middleSpace / 2) + (boxSizeX / 2 - 5), margin + boxSizeY + middleSpace + 15, currentChar, COLOR_WHITE, COLOR_BLACK, 2);
					}
					charSelectSpeedCounter++;
					if (charSelectSpeedCounter == 30) {
						charSelectSpeedCounter = 0;
					}
				}
			}
			if ((*menuSelect) == 19 && (*isPressed)) {
				(*isPressed) = 0;
				if (currentChar >= 'A' && currentChar < 'Z') {
					if (charSelectSpeedCounter == 0) {
						currentChar++;
						lcd.drawChar(margin + (boxSizeX / 2) + (middleSpace / 2) + (boxSizeX / 2 - 5), margin + boxSizeY + middleSpace + 15, currentChar, COLOR_WHITE, COLOR_BLACK, 2);
					}
					charSelectSpeedCounter++;
					if (charSelectSpeedCounter == 50) {
						charSelectSpeedCounter = 0;
					}
				}
			}
			if ((*menuSelect) == 22 && (*isPressed)) {
				(*isPressed) = 0;
				if ((*counter) == 0) {
					if (lettercounter < 3) {
						name[lettercounter] = currentChar;
						switch (lettercounter) {
						case 0:
							lcd.drawChar(margin + (boxSizeX / 2) + middleSpace + 10, margin + boxSizeY - 40, currentChar, COLOR_WHITE, COLOR_BLACK, 3);
							break;
						case 1:
							lcd.drawChar(margin + (boxSizeX / 2) + middleSpace + 58, margin + boxSizeY - 40, currentChar, COLOR_WHITE, COLOR_BLACK, 3);
							break;
						case 2:
							lcd.drawChar(margin + (boxSizeX / 2) + middleSpace + 107, margin + boxSizeY - 40, currentChar, COLOR_WHITE, COLOR_BLACK, 3);
							break;
						}
						lettercounter++;
					}
				}
				(*counter)++;
				if ((*counter) == 252) {
					(*counter) = 0;
				}
			}
			if ((*menuSelect) == 20 && (*isPressed)) {
				(*isPressed) = 0;
				(*menucounter) = 0;
				lettercounter = 0;
				update_EEPROM(eeprom_Storagearray, name, eepromname, (*score), 0, (*lives));
			}
		}
		if ((*menucounter) == 6) { // ABOUT
			if ((*menuSelect) == 21 && (*isPressed)) {
				(*isPressed) = 0;
				(*menucounter) = 0;
			}
		}
	}
}

void calculateSelectedMenu(MI0283QT9 lcd, uint8_t* menucounter, uint8_t* menuSelect, uint8_t joy_x_axis, uint8_t joy_y_axis) {
	_delay_ms(1);
	//MENUCOUNTER == MAIN MENU
	if ((*menucounter) == 1) {
		if (antiZhold == 1) {
			if ((*menuSelect) == 1) {
				lcd.drawRect(margin - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); // Upper-Bottom Rectangle
				antiZhold = 1;
			}
			//NUNCHUCK TO RIGHT
			if (joy_x_axis > sensitivityRight && (*menuSelect) == 1) { //Nunchuck moved to the right
				(*menuSelect) = 2;
				lcd.drawRect(margin - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE);
				antiZhold = 0;
			}
			else if (joy_x_axis > sensitivityRight && (*menuSelect) == 3) {
				(*menuSelect) = 4;
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); // Upper-Bottom Rectangle
				antiZhold = 0;
			}

			//NUNCHUCK TO LEFT
			if (joy_x_axis < sensitivityLeft && (*menuSelect) == 2) { //Nunchuck moved to the left
				(*menuSelect) = 1;
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
				lcd.drawRect(margin - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); // Upper-Bottom Rectangle
				antiZhold = 0;
			}
			else if (joy_x_axis < sensitivityLeft && (*menuSelect) == 4) {
				(*menuSelect) = 3;
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); // Upper-Bottom Rectangle
				antiZhold = 0;
			}

			//NUNCHUCK DOWN
			if (joy_y_axis < sensitivityLeft && (*menuSelect) == 1) { //Nunchuck moved down
				(*menuSelect) = 3;
				lcd.drawRect(margin - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE);
				antiZhold = 0;
			}
			else if (joy_y_axis < sensitivityLeft && (*menuSelect) == 2) {
				(*menuSelect) = 4;
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE);
				antiZhold = 0;
			}

			//NUNCHUCK UP
			if (joy_y_axis > sensitivityRight && (*menuSelect) == 3) { //Nunchuck moved to the left
				(*menuSelect) = 1;
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
				lcd.drawRect(margin - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE);
				antiZhold = 1;
			}
			else if (joy_y_axis > sensitivityRight && (*menuSelect) == 4) {
				(*menuSelect) = 2;
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK);
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE);
				antiZhold = 1;
			}
		}
		else {
			if (joy_y_axis > 114 && joy_y_axis < 140 && joy_x_axis > 114 && joy_x_axis < 140) {
				antiZhold = 1;
			}
		}
	}
	//MENUCOUNTER == LEVEL SELECT
	if ((*menucounter) == 2) {
		if (antiZhold == 1) {
			if ((*menuSelect) == 5) {
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); // Upper-Bottom Rectangle
				antiZhold = 1;
			}
			//NUNCHUCK TO RIGHT
			if (joy_x_axis > sensitivityLaggScreenRight && (*menuSelect) == 5) { //Nunchuck moved to the right
				(*menuSelect) = 6;
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 5
				lcd.drawRect(margin + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 6
				antiZhold = 0;
			}
			else if (joy_x_axis > sensitivityLaggScreenRight && (*menuSelect) == 6) {
				(*menuSelect) = 7;
				lcd.drawRect(margin + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 6
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 7
				antiZhold = 0;
			}
			else if (joy_x_axis > sensitivityLaggScreenRight && (*menuSelect) == 7) {
				(*menuSelect) = 8;
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 7
				lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 8
				antiZhold = 0;
			}
			else if (joy_x_axis > sensitivityLaggScreenRight && (*menuSelect) == 9) {
				(*menuSelect) = 10;
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 9
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 10
				antiZhold = 0;
			}
			//NUNCHUCK TO LEFT
			if (joy_x_axis < sensitivityLaggScreenLeft && (*menuSelect) == 8) { //Nunchuck moved to the right
				(*menuSelect) = 7;
				lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 8
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 7
				antiZhold = 0;
			}
			else if (joy_x_axis < sensitivityLaggScreenLeft && (*menuSelect) == 7) {
				(*menuSelect) = 6;
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 7
				lcd.drawRect(margin + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 6
				antiZhold = 0;
			}
			else if (joy_x_axis < sensitivityLaggScreenLeft && (*menuSelect) == 6) {
				(*menuSelect) = 5;
				lcd.drawRect(margin + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 6
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 5
				antiZhold = 0;
			}
			else if (joy_x_axis < sensitivityLaggScreenLeft && (*menuSelect) == 10) {
				(*menuSelect) = 9;
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 10
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 9
				antiZhold = 0;
			}
			//NUNCHUCK DOWN
			if (joy_y_axis < sensitivityLaggScreenLeft && (*menuSelect) == 5) { //Nunchuck moved down
				(*menuSelect) = 9;
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 5
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 9
				antiZhold = 0;
			}
			else if (joy_y_axis < sensitivityLaggScreenLeft && (*menuSelect) == 6) {
				(*menuSelect) = 9;
				lcd.drawRect(margin + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 6
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 9
				antiZhold = 0;
			}
			else if (joy_y_axis < sensitivityLaggScreenLeft && (*menuSelect) == 7) {
				(*menuSelect) = 10;
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 7
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 10
				antiZhold = 0;
			}
			else if (joy_y_axis < sensitivityLaggScreenLeft && (*menuSelect) == 8) {
				(*menuSelect) = 10;
				lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 8
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 10
				antiZhold = 0;
			}

			//NUNCHUCK UP
			if (joy_y_axis > sensitivityLaggScreenRight && (*menuSelect) == 9) { //Nunchuck moved to the left
				(*menuSelect) = 5;
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 9
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 5
				antiZhold = 0;
			}
			else if (joy_y_axis > sensitivityLaggScreenRight && (*menuSelect) == 10) {
				(*menuSelect) = 7;
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 10
				lcd.drawRect(margin + boxSizeX + middleSpace - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 7
				antiZhold = 0;
			}
		}
		else {
			if (joy_y_axis > 114 && joy_y_axis < 140 && joy_x_axis > 114 && joy_x_axis < 140) {
				antiZhold = 1;
			}
		}
	}
	//MENUCOUNTER == SETTINGS
	if ((*menucounter) == 3) {
		if (antiZhold == 1) {
			if ((*menuSelect) == 11) {
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); // Upper-Bottom Rectangle
				antiZhold = 0;
			}
			//NUNCHUCK TO RIGHT
			if (joy_x_axis > sensitivityRight && (*menuSelect) == 11) { //Nunchuck moved to the right
				(*menuSelect) = 12;
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 11
				lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 12
				antiZhold = 0;
			}
			else if (joy_x_axis > sensitivityRight && (*menuSelect) == 13) {
				(*menuSelect) = 14;
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 13
				lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 14
				antiZhold = 0;
			}
			//NUNCHUCK TO LEFT
			if (joy_x_axis < sensitivityLeft && (*menuSelect) == 12) { //Nunchuck moved to the right
				(*menuSelect) = 11;
				lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 12
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 11
				antiZhold = 0;
			}
			else if (joy_x_axis < sensitivityLeft && (*menuSelect) == 14) {
				(*menuSelect) = 13;
				lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 14
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 13
				antiZhold = 0;
			}
			//NUNCHUCK DOWN
			if (joy_y_axis < sensitivityLeft && (*menuSelect) == 11) { //Nunchuck moved down
				(*menuSelect) = 13;
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 11
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 13
				antiZhold = 0;
			}
			else if (joy_y_axis < sensitivityLeft && (*menuSelect) == 12) {
				(*menuSelect) = 14;
				lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 12
				lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 14
				antiZhold = 0;
			}
			else if (joy_y_axis < sensitivityLeft && (*menuSelect) == 14) {
				(*menuSelect) = 15;
				lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 14
				lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 15
				antiZhold = 0;
			}
			else if (joy_y_axis < sensitivityLeft && (*menuSelect) == 13) {
				(*menuSelect) = 15;
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 13
				lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 15
				antiZhold = 0;
			}

			//NUNCHUCK UP
			if (joy_y_axis > sensitivityRight && (*menuSelect) == 13) { //Nunchuck moved to the left
				(*menuSelect) = 11;
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 13
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 11
				antiZhold = 0;
			}
			else if (joy_y_axis > sensitivityRight && (*menuSelect) == 14) {
				(*menuSelect) = 12;
				lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 14
				lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 12
				antiZhold = 0;
			}
			else if (joy_y_axis > sensitivityRight && (*menuSelect) == 15) {
				(*menuSelect) = 13;
				lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 15
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 13
				antiZhold = 0;
			}
		}
		else {
			if (joy_y_axis > 114 && joy_y_axis < 140 && joy_x_axis > 114 && joy_x_axis < 140) {
				antiZhold = 1;
			}
		}
	}
	//MENUCOUNTER == HIGHSCORES
	if ((*menucounter) == 4) {
		if (antiZhold == 1) {
			if ((*menuSelect) == 16) {
				lcd.drawRect(margin + (boxSizeX / 2) + middleSpace / 2 - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 16
				antiZhold = 0;
			}
			if (joy_y_axis < sensitivityLeft && (*menuSelect) == 16) {
				(*menuSelect) = 17;
				lcd.drawRect(margin + (boxSizeX / 2) + middleSpace / 2 - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 16
				lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 17
				antiZhold = 0;
			}
			if (joy_y_axis > sensitivityRight && (*menuSelect) == 17) {
				(*menuSelect) = 16;
				lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //MenuSelect 17
				lcd.drawRect(margin + (boxSizeX / 2) + middleSpace / 2 - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 16
				antiZhold = 0;
			}
		}
		else {
			if (joy_y_axis > 114 && joy_y_axis < 140 && joy_x_axis > 114 && joy_x_axis < 140) {
				antiZhold = 1;
			}
		}
	}
	//MENUCOUNTER == KEYBOARD
	if ((*menucounter == 5)) {
		if (antiZhold == 1) {
			if ((*menuSelect) == 18) {
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //Menuselect 18
				antiZhold = 0;
			}
			//NUNCHUCK TO RIGHT
			if (joy_x_axis > sensitivityRight && (*menuSelect) == 18) { //Nunchuck moved to the right
				(*menuSelect) = 19;
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //Menuselect 18
				lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //Menuselect 19
				antiZhold = 0;
			}
			//NUNCHUCK TO LEFT
			if (joy_x_axis < sensitivityLeft && (*menuSelect) == 19) { //Nunchuck moved to the right
				(*menuSelect) = 18;
				lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //Menuselect 19
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //Menuselect 18
				antiZhold = 0;
			}
			//NUNCHUCK DOWN
			else if (joy_y_axis < sensitivityLeft && (*menuSelect) == 18) {
				(*menuSelect) = 22;
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //Menuselect 18
				lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //Menuselect 22
				antiZhold = 0;
			}
			else if (joy_y_axis < sensitivityLeft && (*menuSelect) == 19) {
				(*menuSelect) = 22;
				lcd.drawRect(margin + boxSizeX + middleSpace + (boxSizeX / 2) - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //Menuselect 19
				lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //Menuselect 22
				antiZhold = 0;
			}
			else if (joy_y_axis < sensitivityLeft && (*menuSelect) == 22) {
				(*menuSelect) = 20;
				lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //Menuselect 22
				lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //Menuselect 20
				antiZhold = 0;
			}

			//NUNCHUCK UP
			if (joy_y_axis > sensitivityLaggScreenRight && (*menuSelect) == 20) { //Nunchuck moved to the left
				(*menuSelect) = 22;
				lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //Menuselect 20
				lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //Menuselect 22
				antiZhold = 0;
			}
			if (joy_y_axis > sensitivityLaggScreenRight && (*menuSelect) == 22) { //Nunchuck moved to the left
				(*menuSelect) = 18;
				lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_BLACK); //Menuselect 22
				lcd.drawRect(margin - highlightMargin, margin + boxSizeY + middleSpace - highlightMargin, boxSizeX / 2 + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //Menuselect 18
				antiZhold = 0;
			}
		}
		else {
			if (joy_y_axis > 114 && joy_y_axis < 140 && joy_x_axis > 114 && joy_x_axis < 140) {
				antiZhold = 1;
			}
		}
	}
	// MENUCOUTNER == ABOUT
	if ((*menucounter) == 6) {
		if (antiZhold == 1) {
			if ((*menuSelect) == 21) {
				antiZhold = 0;
			}
			if (joy_y_axis < sensitivityLeft && (*menuSelect) == 21) {
				(*menuSelect) = 21;
				lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 21
				antiZhold = 0;
			}
			if (joy_y_axis > sensitivityRight && (*menuSelect) == 21) {
				(*menuSelect) = 21;
				lcd.drawRect(margin + (boxSizeX / 2) + (middleSpace / 2) - highlightMargin, margin + boxSizeY + middleSpace + boxSizeY + middleSpace + boxSizeY + middleSpace - highlightMargin, boxSizeX + (highlightMargin * 2), boxSizeY + (highlightMargin * 2), COLOR_FINE_ORANGE); //MenuSelect 21
				antiZhold = 0;
			}
		}
		else {
			if (joy_y_axis > 114 && joy_y_axis < 140 && joy_x_axis > 114 && joy_x_axis < 140) {
				antiZhold = 1;
			}
		}
	}
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
