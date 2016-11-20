#ifndef IR_H_
#define IR_H_

#define PLAYER 1;
#define BOMB 2;
#define MAP 3;

void IR_init();
void IR_toggle();
uint32_t IR_decode(uint32_t data);
uint32_t IR_encode(uint8_t, ...);
void IR_send(uint8_t type, uint8_t xPos, uint8_t yPos);
void IR_test();
#endif /* IR_H_ */
