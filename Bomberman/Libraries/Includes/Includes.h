#ifndef Includes_H_
#define Includes_H_
#define Background RGB(102, 102, 102)
#define read_eeprom_word(address) eeprom_read_word ((const uint16_t*)address)
#define write_eeprom_word(address,value) eeprom_write_word ((uint16_t*)address,(uint16_t)value)
//102,102,102 is de donkere

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <Arduino.h>
#include "MI0283QT9.h"
#include "../IR/IR.h"
#include "Wire.h"
#include "SPI.h"
#include <BMPheader.h>
#include "eeprom.h"

#endif
