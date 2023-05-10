/*
 * DHT.c
 *
 *  Created on: Apr 25, 2023
 *      Author: user
 */


#include "DHT.h"

void Delay_us(DHT_Name* DHT, uint16_t duration){
	__HAL_TIM_SET_COUNTER(DHT->timer, 0);
	while(__HAL_TIM_GET_COUNTER(DHT->timer) < duration){}
}

void SetPinIn(DHT_Name* DHT){
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /*Configure GPIO pin*/
	  GPIO_InitStruct.Pin = DHT->DHT_pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(DHT->DHT_port, &GPIO_InitStruct);
}

void SetPinOut(DHT_Name* DHT){
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /*Configure GPIO pin*/
	  GPIO_InitStruct.Pin = DHT->DHT_pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(DHT->DHT_port, &GPIO_InitStruct);
}

static void WritePin(DHT_Name* DHT, uint8_t value){
	HAL_GPIO_WritePin(DHT->DHT_port, DHT->DHT_pin, value);
}

static uint8_t ReadPin(DHT_Name* DHT){
	return HAL_GPIO_ReadPin(DHT->DHT_port, DHT->DHT_pin);
}

//===========================HIGH LEVEL FUNCTION===========================//
void DHT_Init(DHT_Name* DHT, GPIO_TypeDef* DHT_port, uint16_t DHT_pin, TIM_HandleTypeDef* timer){
	DHT->DHT_port = DHT_port;
	DHT->DHT_pin = DHT_pin;
	DHT->timer = timer;

	DHT->humi = DHT->temp = 0;

	SetPinOut(DHT);
	WritePin(DHT, 1);
}


void DHT_Read(DHT_Name* DHT){
	uint16_t time_out = 0;
	uint8_t data[5] = {0, 0, 0, 0, 0};

	uint16_t temp, humi;
/*
	data[0] integral Humi
	data[1] decimal Humi
	data[2] integral Temp
	data[3] decimal Temp
	data[4] SUM
*/

	DHT->humi = DHT->temp = 0;

	SetPinOut(DHT);
	WritePin(DHT, 0);
	HAL_Delay(20);


	SetPinIn(DHT);

	Delay_us(DHT, 40);

	if(!ReadPin(DHT)){
		Delay_us(DHT, 80);
	}

	for(time_out = 0; (time_out < 100) && ReadPin(DHT); time_out++);

//	start DHT successful => read
	for(uint8_t i = 0; i < 5; i++){
		for(uint8_t j = 0; j < 8; j++){

			for(time_out = 0; (time_out < 100) && !ReadPin(DHT); time_out++);

			Delay_us(DHT, 40);

			if(!ReadPin(DHT)) data[i] &= (~(1<<(7-j)));
			else data[i] |= (1 << (7-j));


			for(time_out = 0; (time_out < 100) && ReadPin(DHT); time_out++);
		}
	}

	if(data[4] != (data[0] + data[1] + data[2] + data[3]))
		return;

	humi = (float)(data[0] * 1.0 + data[1] / 10.0);
	temp = (float)(data[2] * 1.0 + data[3] / 10.0);

	DHT->humi = humi;
	DHT->temp = temp;

	SetPinOut(DHT);
	WritePin(DHT, 1);
}

float DHT_GetTemp(DHT_Name* DHT){
//	return 30.4;
//	return random()%100 + random()%10 / 10.0;
	return DHT->temp;
}

float DHT_GetHumi(DHT_Name* DHT){
//	return 50.4;
//	return random()%100 + random()%10 / 10.0;
	return DHT->humi;
}

