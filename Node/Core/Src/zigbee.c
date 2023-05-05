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

void ZB_SendMsg_DMA(char* msg, uint8_t length){
	HAL_UART_Transmit_DMA(uart_zigbee, msg, length);
}

uint8_t ZB_IsReceivedMsg(void){

	return 0;
}

uint8_t* ZB_GetMsg(void){

	return NULL;
}
