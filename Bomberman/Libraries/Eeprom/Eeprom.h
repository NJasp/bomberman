#ifndef Eeprom_H_
#define Eeprom_H_

#include "../Includes/Includes.h"

void update_EEPROM(unsigned char eeprom_Storagearray[12], uint8_t name[3], uint8_t eepromname[1], uint8_t score, uint8_t* newHighscore, uint8_t lives, uint8_t reset_EEPROM);

#endif
