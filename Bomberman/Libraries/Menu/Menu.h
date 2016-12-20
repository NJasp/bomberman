#ifndef Menu_H_
#define Menu_H_

#include "../Includes/Includes.h"

void init_ADS();
void startScherm(MI0283QT9 lcd, uint8_t* stage);
void menu(MI0283QT9 lcd, uint8_t* stage, uint8_t* level, unsigned char eeprom_Storagearray[12], uint8_t* playerSpeed, uint8_t* max_bombs, uint8_t* counter, uint8_t* newHighscore, uint8_t dataReady_IR, volatile uint16_t* IRdata, volatile uint8_t* isSendingIR);
void mainMenu(MI0283QT9 lcd);
void levelSelect(MI0283QT9 lcd);
void options(MI0283QT9 lcd, uint8_t* playerSpeed, uint8_t* max_bombs);
void highscores(MI0283QT9 lcd, unsigned char eeprom_Storagearray[12], uint8_t* newHighscore);


#endif
