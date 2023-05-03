#include "fsm.h"

uint8_t mode_lcd, mode_sys;
uint8_t node_turn;

void DecodeDataJsonStr(char* json_str){
	uint8_t i = 0, node_id;
	char* token;

/*
	{"ID":0,"TEMP0":30.4,"HUMI0":50.4,"TEMP1":31.4,"HUMI1":51.4,
		"TEMP2":32.4,"HUMI2":52.4,"TEMP3":33.4,"HUMI3":53.4,
		"GAS":40,"SMOKE":30}

	0  	"ID"					14	"TEMP3"
	1   0						15	33.4
	2  	"TEMP0"					16	"HUMI3"
	3 	30.4					17	53.4
	4  	"HUMI0"					18	"GAS"
	5  	50.4					19	40
	6	"TEMP1"					20	"SMOKE"
	7	31.4					21	30
	8	"HUMI1"
	9	51.4
	10	"TEMP2"
	11	32.4
	12	"HUMI2"
	13	52.4
*/
	token = strtok(json_str, ":,{}");

	for(i = 0; (i < 100) && (token != NULL); i++){
		if(i == 1) {
			node_id = atoi(token);
			_data_node[node_id].node_id = node_id;
			_data_node[node_id].is_connected = 1;
		}
		else if(i == 3) _data_node[node_id].temp_0 = atoff(token);
		else if(i == 5) _data_node[node_id].humid_0 = atoff(token);

		else if(i == 7) _data_node[node_id].temp_1 = atoff(token);
		else if(i == 9) _data_node[node_id].humid_1 = atoff(token);

		else if(i == 11) _data_node[node_id].temp_2 = atoff(token);
		else if(i == 13) _data_node[node_id].humid_2 = atoff(token);

		else if(i == 15) _data_node[node_id].temp_3 = atoff(token);
		else if(i == 17) _data_node[node_id].humid_3 = atoff(token);

		else if(i == 19) _data_node[node_id].gas = atoi(token);
		else if(i == 21) _data_node[node_id].smoke = atoi(token);

		token = strtok(NULL, ":,{}");
	}
}


uint8_t SystemMode(void){
	return mode_sys;
}


//==================HIGH LEVEL FUNCTION==================//
void FSM_Init(void){
	mode_lcd = INIT;
	mode_sys = INIT;

	_time_screen = 30;
	node_turn = 0;
}

void FSM_LcdDisplay(void){
	switch(mode_lcd){
	case INIT:

		CLCD_CreateChar(0, icon_temp);
		CLCD_CreateChar(1, icon_humi);

		CLCD_PrintStringBuffer(0, 0, SCREEN_INIT_0);
		CLCD_PrintStringBuffer(1, 0, SCREEN_INIT_1);

		if(_time_screen < 5){
			CLCD_PrintStringBuffer(0, 0, SCREEN_READY_DISPLAY_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_READY_DISPLAY_1);
			mode_lcd = READY_DISPLAY;
		}
		break;
	case READY_DISPLAY:

		CLCD_PrintCharBuffer(1, 12 + (_counter_time_elapsed/10) % 4, '.');
		if((_counter_time_elapsed/10) % 4 == 3) CLCD_PrintStringBuffer(1, 0, SCREEN_READY_DISPLAY_1);

		if(SystemMode() == SYS_CONNECT_WF){
			CLCD_PrintStringBuffer(0, 0, SCREEN_WIFI_CONNECTING_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);

			mode_lcd = DISPLAY_CONNECTWF;
		}
		else if(SystemMode() == SYS_CONFIG_WF){
			CLCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);

			mode_lcd = DISPLAY_CONFIGWF;
		}
		else if(_data_node[node_turn].is_connected){
			_time_screen = TIME_SCREEN;

			mode_lcd = DISPLAY_DHT01;
		}
		else{
			mode_lcd = TURN_NEXT_NODE;
		}
		break;

	case DISPLAY_DHT01:

	break;
	case DISPLAY_DHT12:

	break;
	case DISPLAY_GAS_SMOKE:

	break;
	case TURN_NEXT_NODE:

		node_turn = (node_turn + 1) % NO_OF_NODES;
		
		mode_lcd = READY_DISPLAY;
		break;
	case DISPLAY_CONFIGWF:

		if(SystemMode() == SYS_CONNECT_WF) {
			CLCD_PrintStringBuffer(0, 0, SCREEN_WIFI_CONNECTING_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);

			mode_lcd = DISPLAY_CONNECTWF;
		}
		break;
	case DISPLAY_CONNECTWF:
		//every 500ms print a '.'
		CLCD_PrintCharBuffer(1, 6 + (_counter_time_elapsed/10) % 5, '.');

		if((_counter_time_elapsed/10) % 5 == 4) CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);

		if(SystemMode() == SYS_CONFIG_WF){
			CLCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);

			mode_lcd = DISPLAY_CONFIGWF;
		}
		else if(SystemMode() == SYS_PROCESS_DATA) {
			CLCD_PrintStringBuffer(0, 0, SCREEN_READY_DISPLAY_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_READY_DISPLAY_1);

			mode_lcd = READY_DISPLAY;
		}
		break;
	default:
		mode_lcd = INIT;
	}

}

void FSM_SystemControl(void){
	switch(mode_sys){
	case INIT:
//      READ WIFI NAME + WIFI PASS FROM  EEPROM
        if (EEPROM.read(0) != 0) {      
        	_wifi_name = "";
            _wifi_pass = "";   

// 			the first 32 memory cell save wf name
            for (int i = 0; i < 32; i++) {           
				_wifi_name += char(EEPROM.read(i));
            }
// 			the next 64 save wf pass
            for (int i = 32; i < 96; ++i) {               
              _wifi_pass += char(EEPROM.read(i));
        	}
        }	
		
		Serial.print("Connecting to WF: ");
		Serial.println(_wifi_name + "  " + _wifi_pass);
		
		WF_Connect(_wifi_name, _wifi_pass);

		mode_sys = SYS_CONNECT_WF;
		break;
	case SYS_CONNECT_WF:
		if(WF_IsConnected()) {
			Serial.println("Connect Wifi successful!");

			SV_Connect();

			mode_sys = SYS_PROCESS_DATA;
		}
		else if(IN_IsPressed_ms(BT0, 2000)){
			WF_Disconnect();
			WF_CreateWebserver();
			Serial.println("Begin config Wifi");
			mode_sys = SYS_CONFIG_WF;
		}
		break;
	case SYS_CONFIG_WF:
		if(WFCF_IsDone()){
			_wifi_name = WFCF_Get_WFName();
			_wifi_pass = WFCF_Get_WFPass();

	//      SAVE WIFI NAME + WIFI PASS TO EEPROM
			for (int i = 0; i < 96; i++) {
				EEPROM.write(i, 0);               //Clear EEPROM
			}
			for (int i = 0; i < _wifi_name.length(); i++) {
				EEPROM.write(i, _wifi_name[i]);
			}
			for (int i = 0; i < _wifi_pass.length(); i++) {
				EEPROM.write(32 + i, _wifi_pass[i]);
			}
				EEPROM.commit();

			Serial.println("Config Wifi successful!");
			Serial.println(_wifi_name + "  " + _wifi_pass);

			Serial.println("Connecting to Wifi: ");
			Serial.println(_wifi_name + "  " + _wifi_pass);
			
			WF_CloseAP();
			WF_Connect(_wifi_name, _wifi_pass);

			mode_sys = SYS_CONNECT_WF;
		}
		break;
	case SYS_PROCESS_DATA:		
		if(ZB_IsReceivedMsg()){
			Serial.println("Received: ");
			Serial.println((char*)ZB_GetMsg().c_str());

			DecodeDataJsonStr((char*)ZB_GetMsg().c_str());

			if(SV_IsConnected()){
				Serial.println("Sending to Server: ");
				SV_SendData(CHANNEL_DATA, (char*)ZB_GetMsg().c_str());
			}
			else SV_Connect();
		}
		
		if(WF_IsConnected() == false){
			Serial.print("Connecting to WF: ");
			Serial.println(_wifi_name + "  " + _wifi_pass);
			
			WF_Connect(_wifi_name, _wifi_pass);

			mode_sys = SYS_CONNECT_WF;
		}
		else if(IN_IsPressed_ms(BT0, 2000)){
			WF_Disconnect();
			WF_CreateWebserver();
			Serial.println("Begin config Wifi");
			mode_sys = SYS_CONFIG_WF;
		}

		break;
	default:
		mode_sys = INIT;
	}
}