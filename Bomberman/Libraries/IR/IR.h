#ifndef IR_H_
#define IR_H_

#include "../Includes/Includes.h"

// config
static const uint16_t ONE_DELAY  = 60;
static const uint16_t ZERO_DELAY = 40;
static const uint16_t SPACE_DELAY= 10;
static const uint16_t DELAY_OFFSET= 6;

typedef struct data_store{
	uint8_t type;
	uint8_t xData;
	uint8_t yData;
} data_store;

static const uint8_t LEVEL 		= 0;
static const uint8_t PLAYER 	= 1;
static const uint8_t BOMB 		= 2;
static const uint8_t MAP 		= 3;

void init_IR();
void toggle_IR();
void off_IR();
void on_IR();
uint8_t isOn_IR();
uint8_t isSending_IR();
uint8_t dataReady_IR();
data_store decode_IR(uint16_t data);
uint16_t encode_IR(uint8_t type, uint8_t xData, uint8_t yData);
void send_IR(uint8_t type, uint8_t xData, uint8_t yData);
void processRecieve_IR(uint32_t currentTime, uint16_t *data);
void processSend_IR(uint32_t currentTime);

#endif /* IR_H_ */
