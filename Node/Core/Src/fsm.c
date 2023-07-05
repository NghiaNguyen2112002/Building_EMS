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
	return sprintf(json_str, "!wkp#!{\"ID\":%u,\"TEMP\":%0.1f,\"HUMI\":%0.1f,"
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

		_time_read_data = TIME_READ_DATA;

		mode = SYS_WAKEUP;
		break;
	case SYS_WAKEUP:

		CLCD_PrintStringBuffer(0, 0, "WAKEUP");
		if(_time_read_data == 0){
			_time_read_data = TIME_READ_DATA;

			DHT_Read(&_dht);

			_data.temp = DHT_GetTemp(&_dht);
			_data.humid = DHT_GetHumi(&_dht);

			_data.gas = IN_GetValue_Gas();
			_data.smoke = IN_GetValue_Smoke();

			ZB_SendMsg("wkp", 3);
			HAL_Delay(100);
			ZB_SendMsg(json_str, ConvertToJsonString());
		}
		mode = SYS_SLEEP;
		break;

	case SYS_SLEEP:

		CLCD_PrintStringBuffer(0, 0, "SLEEP ");

		HAL_SuspendTick();
		HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
		HAL_ResumeTick();

		mode = SYS_WAKEUP;
		break;
	default:
		mode = INIT;
	}
}
