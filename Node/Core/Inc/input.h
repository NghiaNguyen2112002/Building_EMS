/*
 * input.h
 *
 *  Created on: Apr 27, 2023
 *      Author: user
 */

#ifndef INC_INPUT_H_
#define INC_INPUT_H_

#include "DHT.h"
#include "stm32f1xx_hal.h"
#include "main.h"


void IN_Init(ADC_HandleTypeDef* hadc);
//void IN_ReadADC(void);
uint16_t IN_GetValue_MQ2(void);
uint16_t IN_GetValue_MP2(void);

#endif /* INC_INPUT_H_ */
