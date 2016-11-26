#ifndef IR_H_
#define IR_H_

typedef struct data_store{
	uint8_t type;
	uint8_t xData;
	uint8_t yData;
} data_store;

#define PLAYER 1;
#define BOMB 2;
#define MAP 3;

void IR_init();
void IR_toggle();
void IR_off();
void IR_on();
data_store IR_decode(uint16_t data);
uint16_t IR_encode(uint8_t type, uint8_t xData, uint8_t yData);
void IR_send(uint8_t type, uint8_t xData, uint8_t yData);
//void IR_test();

#endif /* IR_H_ */
