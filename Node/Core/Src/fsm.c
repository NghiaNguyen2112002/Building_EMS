/*
 * fsm.c
 *
 *  Created on: Apr 27, 2023
 *      Author: user
 */

#include "fsm.h"

uint8_t mode;
char json_str[200];


uint8_t ConvertToJsonString(void){
	return sprintf(json_str, "{\"ID\":%u,\"TEMP\":%0.1f,\"HUMI\":%0.1f,"
										"\"GAS\":%u,\"SMOKE\":%u}#",
										NODE_ID, _data.temp, _data.humid,
										_data.gas, _data.smoke);
}


//==================HIGH LEVEL FUNCTION==================//
void FSM_Init(void){
	mode = INIT;
}
void FSM_SystemControl(void){
	switch(mode){
	case INIT:

//		_time_read_data = TIME_READ_DATA;
		mode = IDLING;
		break;
	case IDLING:
//		if(_time_read_data < 5) mode = READ_DATA;

		mode = READ_DATA;
		break;
	case READ_DATA:
		CLCD_PrintStringBuffer(0, 0, "READ DATA");

		DHT_Read(&_dht);

		_data.temp = DHT_GetTemp(&_dht);
		_data.humid = DHT_GetHumi(&_dht);

		_data.gas = IN_GetValue_Gas();
		_data.smoke = IN_GetValue_Smoke();

		mode = SEND_DATA;
		break;
	case SEND_DATA:
		CLCD_PrintStringBuffer(0, 0, "SEND DATA");

		ZB_SendMsg(json_str, ConvertToJsonString());

//		_time_read_data = TIME_READ_DATA;
		mode = IDLING;
		break;
	default:
		mode = INIT;
	}
}
