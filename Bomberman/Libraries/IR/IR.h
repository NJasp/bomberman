#ifndef IR_H_
#define IR_H_

// config
static const uint16_t ONE_DELAY  = 6;
static const uint16_t ZERO_DELAY = 3;
static const uint16_t SPACE_DELAY= 10;
static const uint16_t DELAY_OFFSET= 2;

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
uint8_t dataReady_IR();
data_store decode_IR(uint16_t data);
uint16_t encode_IR(uint8_t type, uint8_t xData, uint8_t yData);
void send_IR(volatile uint8_t *isSending, uint8_t type, uint8_t xData, uint8_t yData);
void processRecieve_IR(uint32_t currentTime, volatile uint16_t *data);
void processSend_IR(uint32_t currentTime, volatile uint8_t *isSending);

#endif /* IR_H_ */
