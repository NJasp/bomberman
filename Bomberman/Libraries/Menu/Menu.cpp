#include "Menu.h"


void startScherm(MI0283QT9 lcd)
{
	lcd.fillScreen(RGB(255, 255, 255));
	lcd.drawText(55, 20, "Bomberman", (RGB(0, 0, 0)), (RGB(255, 255, 255)), 3);
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
}

void level1(MI0283QT9 lcd)
{
	lcd.drawRect(20, 60, 120, 30, (RGB(0, 0, 0)));
	lcd.fillRect(20, 60, 120, 30, (RGB(0, 0, 0)));
	lcd.drawText(28, 65, "Level 1", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 2);
}

void level2(MI0283QT9 lcd)
{
	lcd.drawRect(20, 120, 120, 30, (RGB(0, 0, 0)));
	lcd.fillRect(20, 120, 120, 30, (RGB(0, 0, 0)));
	lcd.drawText(28, 125, "Level 2", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 2);
}

void level3(MI0283QT9 lcd)
{
	lcd.drawRect(20, 180, 120, 30, (RGB(0, 0, 0)));
	lcd.fillRect(20, 180, 120, 30, (RGB(0, 0, 0)));
	lcd.drawText(28, 185, "Level 3", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 2);
}

void levelRandom(MI0283QT9 lcd)
{
	lcd.drawRect(180, 60, 120, 100, (RGB(0, 0, 0)));
	lcd.fillRect(180, 60, 120, 100, (RGB(0, 0, 0)));
	lcd.drawText(188, 65, "Random", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 2);
	lcd.drawText(188, 90, "Gene-", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 2);
	lcd.drawText(188, 105, "rated", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 2);
	lcd.drawText(188, 130, "Level", (RGB(255, 255, 255)), (RGB(0, 0, 0)), 2);
}

