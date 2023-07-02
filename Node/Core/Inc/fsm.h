/*
 * fsm.h
 *
 *  Created on: Apr 27, 2023
 *      Author: user
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "input.h"
#include "DHT.h"
#include "global.h"
#include "stm32f1xx_hal.h"
#include "main.h"
#include "zigbee.h"
#include "lcd_i2c.h"

//==================MODE FSM SYSTEM CONTROL==================//
#define INIT						0
#define SYS_SLEEP					1
#define SYS_WAKEUP					2


//==================TIME==================//
#define TIME_READ_DATA					5			//readdata every 5s


void FSM_Init(void);
void FSM_SystemControl(void);

#endif /* INC_FSM_H_ */
