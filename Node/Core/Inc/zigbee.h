/*
 * uart.h
 *
 *  Created on: Apr 27, 2023
 *      Author: user
 */

#ifndef INC_ZIGBEE_H_
#define INC_ZIGBEE_H_

#include "stm32f1xx_hal.h"
#include "lcd_i2c.h"

/*
==========================NOTE==========================

	MAX ZIGBEE DATA PACKET SENT IS 128 BYTE
*/


void ZB_Init(UART_HandleTypeDef* huart);
void ZB_SendMsg(char* msg, uint8_t length);
void ZB_SendMsg_DMA(char* msg, uint8_t length);
uint8_t ZB_IsReceivedMsg(void);
uint8_t* ZB_GetMsg(void);

#endif /* INC_ZIGBEE_H_ */
