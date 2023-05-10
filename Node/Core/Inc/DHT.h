/*
 * DHT.h
 *
 *  Created on: Apr 25, 2023
 *      Author: user
 */

#ifndef INC_DHT_H_
#define INC_DHT_H_

#include "stm32f1xx_hal.h"
#include "main.h"
#include "lcd_i2c.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	GPIO_TypeDef* 			DHT_port;
	uint16_t 				DHT_pin;
	TIM_HandleTypeDef* 		timer;
	float 					temp;
	float 					humi;
}DHT_Name;

void DHT_Init(DHT_Name* DHT, GPIO_TypeDef* DHT_port, uint16_t DHT_pin, TIM_HandleTypeDef* timer);
void DHT_Read(DHT_Name* DHT);
float DHT_GetTemp(DHT_Name* DHT);
float DHT_GetHumi(DHT_Name* DHT);

#endif /* INC_DHT_H_ */
