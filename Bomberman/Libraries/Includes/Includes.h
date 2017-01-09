#ifndef Includes_H_
#define Includes_H_
#define Background RGB(102, 102, 102)
#define COLOR_FINE_RED RGB(255, 0, /*75*/ 20)
#define COLOR_FINE_GREEN RGB(100, 200, 0)
#define COLOR_FINE_ORANGE RGB(255,165,0)
#define COLOR_FINE_BLUE RGB(100,100,140)
#define COLOR_WHITE RGB(255,255,255)
#define COLOR_BLACK RGB(0,0,0)
#define COLOR_DARK_YELLOW RGB(127, 80, 0)
#define COLOR_GREY RGB(127, 127, 127)
#define read_eeprom_word(address) eeprom_read_word ((const uint16_t*)address)
#define write_eeprom_word(address,value) eeprom_write_word ((uint16_t*)address,(uint16_t)value)
//102,102,102 is de donkere

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <Arduino.h>
#include "../IR/IR.h"
#include "Wire.h"
#include "SPI.h"
#include "avr/eeprom.h"
#include "MI0283QT9.h"

#endif
