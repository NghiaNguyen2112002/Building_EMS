/*
 * input.c
 *
 *  Created on: Apr 27, 2023
 *      Author: user
 */

#include "input.h"

ADC_HandleTypeDef* adc;
uint16_t ADC_value[2];


//===========================HIGH LEVEL FUNCTION===========================//
void IN_Init(ADC_HandleTypeDef* hadc){
	adc = hadc;

	HAL_ADC_Start_DMA(hadc, (uint32_t*) ADC_value, 2);
}


uint16_t IN_GetValue_Gas(void){
	return ADC_value[1];
}

uint16_t IN_GetValue_Smoke(void){
	return ADC_value[0];
}
