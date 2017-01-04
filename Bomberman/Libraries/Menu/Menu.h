#ifndef Menu_H_
#define Menu_H_

#include "../Includes/Includes.h"

void startScherm(MI0283QT9 lcd, uint8_t* stage, uint8_t buffer[], uint8_t* x, uint8_t* y, uint8_t* isPressed, uint8_t* counter);
void menu(MI0283QT9 lcd, uint8_t* stage, uint8_t* level, unsigned char eeprom_Storagearray[12], uint8_t* playerSpeed, uint8_t* max_bombs, uint8_t* newHighscore, volatile uint16_t* IRdata, volatile uint8_t* isSendingIR, volatile uint8_t* interruptCounter, uint16_t* seed, uint8_t* menucounter, uint8_t buffer[], uint8_t* x, uint8_t* y, uint8_t* isPressed, uint8_t* menuSelect, uint8_t* counter);
void calculateSelectedMenu(MI0283QT9 lcd, uint8_t* menucounter, uint8_t* menuSelect, uint8_t joy_x_axis, uint8_t joy_y_axis);
void mainMenu(MI0283QT9 lcd);
void levelSelect(MI0283QT9 lcd);
void options(MI0283QT9 lcd, uint8_t* playerSpeed, uint8_t* max_bombs);
void highscores(MI0283QT9 lcd, unsigned char eeprom_Storagearray[12], uint8_t* newHighscore);
void keyboard(MI0283QT9 lcd);

#endif
