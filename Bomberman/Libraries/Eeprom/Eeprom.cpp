#include "Eeprom.h"

void update_EEPROM(unsigned char eeprom_Storagearray[12], uint8_t name[3], uint8_t eepromname[1], uint8_t score, uint8_t* newHighscore, uint8_t lives, uint8_t reset_EEPROM) {
	if (!(name[0] == 0 || name[1] == 0 || name[2] == 0)) {
		if (name[0] != eepromname[0] || name[1] != eepromname[1] || name[2] != eepromname[2]) {
			write_eeprom_word(&eeprom_Storagearray[2], name[0]);
			write_eeprom_word(&eeprom_Storagearray[3], name[1]);
			write_eeprom_word(&eeprom_Storagearray[4], name[2]);
		}
	}

	if (read_eeprom_word(&eeprom_Storagearray[0]) < score && lives == 0) { //if score of player1 in eeprom < score in game
		write_eeprom_word(&eeprom_Storagearray[0], score);  // write highest score to [0] (player 1 in eeprom)
		(*newHighscore) = 1;
	}
	if (reset_EEPROM) {
		Serial.println(eeprom_Storagearray[2]);
		Serial.println(eeprom_Storagearray[3]);
		Serial.println(eeprom_Storagearray[4]);
		write_eeprom_word(&eeprom_Storagearray[0], 0);
		write_eeprom_word(&eeprom_Storagearray[1], 0);
		write_eeprom_word(&eeprom_Storagearray[2], 0);
		write_eeprom_word(&eeprom_Storagearray[3], 0);
		write_eeprom_word(&eeprom_Storagearray[4], 0);
	}
}