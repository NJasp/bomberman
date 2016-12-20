#ifndef IR_H_
#define IR_H_

// config
static const uint16_t ONE_DELAY = 6;
static const uint16_t ZERO_DELAY = 3;
static const uint16_t SPACE_DELAY = 10;
static const uint16_t DELAY_OFFSET = 2;

typedef struct data_store {
	uint8_t type;
	uint8_t xData;
	uint8_t yData;
} data_store;

static const uint8_t PLAYER = 1;
static const uint8_t BOMB = 2;
static const uint8_t LEVEL = 3;

void init_IR();
uint8_t dataReady_IR();
data_store decode_IR(uint16_t data);
uint16_t encode_IR(uint8_t type, uint8_t xData, uint8_t yData);
void send_IR(volatile uint8_t *isSending, uint8_t type, uint8_t xData, uint8_t yData);
void processRecieve_IR(uint32_t currentTime, volatile uint16_t *data);
void processSend_IR(uint32_t currentTime, volatile uint8_t *isSending);
void processData_IR(volatile uint16_t* IRdata, uint8_t* player2_x, uint8_t* player2_y, uint8_t* player2_x_old, uint8_t* player2_y_old, uint8_t* player2_x_bombdrop, uint8_t* player2_y_bombdrop, uint8_t grid[16][12]);
uint8_t processMenuData_IR(uint8_t* stage, uint8_t* level, volatile uint16_t* IRdata);

#endif /* IR_H_ */
