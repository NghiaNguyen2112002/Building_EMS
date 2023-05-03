/*
 * fsm.c
 *
 *  Created on: Apr 27, 2023
 *      Author: user
 */

#include "fsm.h"

uint8_t mode;


void FSM_Init(void){
	mode = INIT;
}
void FSM_SystemControl(void){
	switch(mode){
	case INIT:
		_time_read_data = TIME_READ_DATA;
		mode = IDLING;
		break;
	case IDLING:
		if(_time_read_data < 5) mode = READ_DATA;
		break;
	case READ_DATA:

		mode = SEND_DATA;
		break;
	case SEND_DATA:

		break;
	default:
		mode = INIT;
	}
}
