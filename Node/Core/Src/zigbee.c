/*
 * uart.c
 *
 *  Created on: Apr 27, 2023
 *      Author: user
 */


#include "zigbee.h"

UART_HandleTypeDef* uart_zigbee;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == uart_zigbee->Instance){

	}

}

//==================HIGH LEVEL FUNCTION==================//
void ZB_Init(UART_HandleTypeDef* huart){
	uart_zigbee = huart;

}

void ZB_SendMsg(char* msg, uint8_t length){
	uint8_t i;
	for(i = 0; i < length; i++){
		HAL_UART_Transmit(uart_zigbee, msg + i, 1, 100);

	}

//	HAL_UART_Transmit(uart_zigbee, (uint8_t*)msg, length, 2000);


}

uint8_t ZB_IsReceivedMsg(void){

	return 0;
}

uint8_t* ZB_GetMsg(void){

	return NULL;
}


