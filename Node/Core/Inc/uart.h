/*
 * uart.h
 *
 *  Created on: Apr 27, 2023
 *      Author: user
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "stm32f1xx_hal.h"

void UART_Init(UART_HandleTypeDef* huart);
void UART_SendMsg(uint8_t* msg, uint8_t length);
uint8_t UART_IsReceivedMsg(void);
uint8_t* UART_GetMsg(void);

#endif /* INC_UART_H_ */
