#ifndef __INPUT_H__
#define __INPUT_H__

#include "Arduino.h"
#include "pin.h"


//==================BUTTON===================//
#define NO_OF_BUTTONS         2

#define BUTTON_IS_PRESSED     0
#define BUTTON_IS_RELEASED    1

#define MAX_COUNTER           1000      //50s

#define BT0                   0
#define SW_WAKEUP             1

void IN_Init(void);

void IN_ReadButton(void);
bool IN_IsPressed(uint8_t index);
bool IN_IsPressed_ms(uint8_t index, uint16_t duration);
bool IN_IsHeld(uint8_t index);


#endif