#ifndef Menu_H_
#define Menu_H_

#include "../Includes/Includes.h"

void startScherm(MI0283QT9 lcd, uint8_t* stage);
void menu(MI0283QT9 lcd, uint8_t* stage, uint8_t* level, unsigned int eeprom_Storagearray[2]);
void menuLevelSelect(MI0283QT9 lcd);
void menuOptions(MI0283QT9 lcd);
void options(MI0283QT9 lcd);
void menuScherm(MI0283QT9 lcd);
void levelSelect(MI0283QT9 lcd);
void level1(MI0283QT9 lcd);
void level2(MI0283QT9 lcd);
void level3(MI0283QT9 lcd);
void levelRandom(MI0283QT9 lcd);
void backToMenu(MI0283QT9 lcd);


#endif