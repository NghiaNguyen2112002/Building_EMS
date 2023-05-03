/*
 * fsm.h
 *
 *  Created on: Apr 27, 2023
 *      Author: user
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "input.h"
#include "DHT.h"
#include "global.h"
#include "stm32f1xx_hal.h"
#include "main.h"

//==================MODE FSM SYSTEM CONTROL==================//
#define INIT						0
#define IDLING						1
#define READ_DATA					2
#define SEND_DATA					3


//==================TIME==================//
#define TIME_READ_DATA					1000


void FSM_Init(void);
void FSM_SystemControl(void);

#endif /* INC_FSM_H_ */
