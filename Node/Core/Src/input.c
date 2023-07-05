/*
 * input.c
 *
 *  Created on: Apr 27, 2023
 *      Author: user
 */

#include "input.h"

ADC_HandleTypeDef* adc1;
ADC_HandleTypeDef* adc2;


//===========================HIGH LEVEL FUNCTION===========================//
void IN_Init(ADC_HandleTypeDef* hadc_1, ADC_HandleTypeDef* hadc_2){

	adc1 = hadc_1;
	adc2 = hadc_2;
}


uint16_t IN_GetValue_Gas(void){
	HAL_ADC_Start(adc1);
	return HAL_ADC_GetValue(adc1) * 100 / 4095;

}

uint16_t IN_GetValue_Smoke(void){
	HAL_ADC_Start(adc2);
	return HAL_ADC_GetValue(adc2) * 100 / 4095;
}
