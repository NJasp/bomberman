#include "Menu.h"


void startScherm(MI0283QT9 lcd)
{
	lcd.fillScreen(RGB(255, 255, 255));
	lcd.drawText(55, 20, "Bomberman", (RGB(0, 0, 0)), (RGB(255, 255, 255)), 3);
	lcd.drawText(30, 80, "Touch to continue", RGB(0,0,0), RGB(255,255,255), 2);
}

void menuLevelSelect(MI0283QT9 lcd)
{
	lcd.drawRect(80, 40, 160, 50, (RGB(0, 0, 0)));
	lcd.fillRect(80, 40, 160, 50, (RGB(0, 0, 0)));
	lcd.drawText(105, 55, "Level", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 3);
}

void menuOptions(MI0283QT9 lcd)
{
	lcd.drawRect(65, 160, 185, 50, (RGB(0, 0, 0)));
	lcd.fillRect(65, 160, 185, 50, (RGB(0, 0, 0)));
	lcd.drawText(80, 175, "Options", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 3);
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
	menuOptions(lcd);
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

void menu(MI0283QT9 lcd, uint8_t* stage, uint8_t* level)
{
	uint8_t menucounter = 0;
	for (;;)
	{
		uint16_t touchx = 0, touchy = 0;
		touchx = lcd.touchX();
		touchy = lcd.touchY();

		if (menucounter == 0 && lcd.touchRead()) {
			menuScherm(lcd);
			menucounter = 1;
		}
		if (menucounter == 1 && lcd.touchRead()) {
			if (touchx >= 80 && touchx <= 240 && touchy >= 40 && touchy <= 90) {
				levelSelect(lcd);
				menucounter = 2;
			}
			else if (touchx >= 65 && touchx <= 270 && touchy >= 160 && touchy <= 210)
			{
				options(lcd);
				menucounter = 3;
			}
		}
		if (menucounter == 2 && lcd.touchRead()) {
			if (touchx >= 20 && touchx <= 120 && touchy >= 60 && touchy <= 90) {
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 1;
				break;
			}
			if (touchx >= 20 && touchx <= 120 && touchy >= 120 && touchy <= 150) {
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 2;
				break;
			}
			if (touchx >= 20 && touchx <= 120 && touchy >= 180 && touchy <= 210) {
				(*stage) = 2;
				lcd.fillScreen(Background);
				(*level) = 3;
				break;
			}
			if (touchx >= 180 && touchx <= 250 && touchy >= 200 && touchy <= 230) {
				menucounter = 0;
			}
		}
		if (menucounter == 3 && lcd.touchRead()) {
			if (touchx >= 180 && touchx <= 250 && touchy >= 200 && touchy <= 230) {
				menucounter = 0;
			}
		}
	}
}
