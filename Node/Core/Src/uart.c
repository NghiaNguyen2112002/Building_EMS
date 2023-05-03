/*
 * uart.c
 *
 *  Created on: Apr 27, 2023
 *      Author: user
 */


#include "uart.h"

UART_HandleTypeDef* uart_zigbee;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == uart_zigbee->Instance){

	}

}

//==================HIGH LEVEL FUNCTION==================//
void UART_Init(UART_HandleTypeDef* huart){
	uart_zigbee = huart;

}

void UART_SendMsg(uint8_t* msg, uint8_t length){
	HAL_UART_Transmit(uart_zigbee, msg, length, 1000);
}

uint8_t UART_IsReceivedMsg(void){

}

uint8_t* UART_GetMsg(void){

}
