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
	return sprintf(json_str, "{\"ID\":%u,\"TEMP0\":%0.1f,\"HUMI0\":%0.1f,\"TEMP1\":%0.1f,\"HUMI1\":%0.1f,"
										"\"TEMP2\":%0.1f,\"HUMI2\":%0.1f,\"TEMP3\":%0.1f,\"HUMI3\":%0.1f,"
										"\"GAS\":%u,\"SMOKE\":%u}#",
										NODE_ID, _data.temp_0, _data.humid_0, _data.temp_1, _data.humid_1,
										_data.temp_2, _data.humid_2, _data.temp_3, _data.humid_3,
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

//		DHT_Read(&_dht0);
//		DHT_Read(&_dht1);
//		DHT_Read(&_dht2);
//		DHT_Read(&_dht3);

		_data.temp_0 = DHT_GetTemp(&_dht0);
		_data.humid_0 = DHT_GetHumi(&_dht0);

		_data.temp_1 = DHT_GetTemp(&_dht1);
		_data.humid_1 = DHT_GetHumi(&_dht1);

		_data.temp_2 = DHT_GetTemp(&_dht2);
		_data.humid_2 = DHT_GetHumi(&_dht2);

		_data.temp_3 = DHT_GetTemp(&_dht3);
		_data.humid_3 = DHT_GetHumi(&_dht3);

		_data.gas = IN_GetValue_Gas();
		_data.smoke = IN_GetValue_Smoke();

		mode = SEND_DATA;
		break;
	case SEND_DATA:
		CLCD_PrintStringBuffer(0, 0, "SEND DATA");


//		ZB_SendMsg_DMA(json_str, 132);

		ZB_SendMsg(json_str, ConvertToJsonString());

//		_time_read_data = TIME_READ_DATA;
		mode = IDLING;
		break;
	default:
		mode = INIT;
	}
}
