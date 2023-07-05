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


void IN_Init(ADC_HandleTypeDef* hadc_1, ADC_HandleTypeDef* hadc_2);
uint16_t IN_GetValue_Gas(void);
uint16_t IN_GetValue_Smoke(void);

#endif /* INC_INPUT_H_ */
