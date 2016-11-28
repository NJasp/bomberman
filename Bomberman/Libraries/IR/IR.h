#ifndef IR_H_
#define IR_H_

typedef struct data_store{
	uint8_t type;
	uint8_t xData;
	uint8_t yData;
} data_store;

static const uint8_t ONE_DELAY 	= 70;
static const uint8_t ZERO_DELAY = 40;
static const uint8_t SPACE_DELAY= 10;
static const uint8_t LEVEL 		= 0;
static const uint8_t PLAYER 	= 1;
static const uint8_t BOMB 		= 2;
static const uint8_t MAP 		= 3;

void IR_init();
void IR_toggle();
void IR_off();
void IR_on();
uint8_t IR_ison();
uint8_t IR_isSending();
data_store IR_decode(uint16_t data);
uint16_t IR_encode(uint8_t type, uint8_t xData, uint8_t yData);
void IR_send(uint8_t type, uint8_t xData, uint8_t yData);
<<<<<<< HEAD
void IR_processRecieve(uint32_t currentTime, uint16_t *data);
void IR_processSend(uint32_t currentTime);

#endif /* IR_H_ */
