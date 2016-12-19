#ifndef Menu_H_
#define Menu_H_

#include "../Includes/Includes.h"

void startScherm(MI0283QT9 lcd, uint8_t* stage);
void menu(MI0283QT9 lcd, uint8_t* stage, uint8_t* level, unsigned int eeprom_Storagearray[2], uint8_t* playerSpeed, uint8_t* max_bombs, uint8_t* counter, uint8_t* counter2);
void mainMenu(MI0283QT9 lcd);
void levelSelect(MI0283QT9 lcd);
void options(MI0283QT9 lcd, uint8_t* playerSpeed, uint8_t* max_bombs);
void highscores(MI0283QT9 lcd, unsigned int eeprom_Storagearray[2]);


#endif