#ifndef INC_FSM_H_
#define INC_FSM_H_


#include <Arduino.h>
#include <string.h>
#include <EEPROM.h>

#include "global.h"
#include "screen_lcd.h"
#include "wifi_controller.h"
#include "MQTT_server.h"
#include "lcd_i2c.h"
#include "input.h"
#include "Zigbee.h"

//==================MODE FSM LCD DISPLAY==================//
#define INIT						0
#define READY_DISPLAY               1
#define DISPLAY_DHT01               2
#define DISPLAY_DHT12               3
#define DISPLAY_GAS_SMOKE           4
#define DISPLAY_CONFIGWF            5
#define DISPLAY_CONNECTWF           6
#define TURN_NEXT_NODE              7

//==================MODE FSM DATA PROCESSING==================//
//#define INIT						0
#define READ_DATA					1
#define IDLING						2
#define SEND_DATA					3

//==================MODE FSM SYSTEM CONTROL==================//
//#define INIT						0
#define SYS_CONNECT_WF				1
#define SYS_CONFIG_WF				2
#define SYS_PROCESS_DATA			3


//==================TIME==================//
#define TIME_SCREEN						500

//==================MSG FROM ESP==================//
#define ONRELAY							"ONRELAY"
#define OFFRELAY						"OFFRELAY"
#define CONFIG_WF_SUCCESS				"CONFIG_SUCCESS"
#define CONNECT_WF_SUCCESS				"CONNECT_SUCCESS"
#define DISCONNECT_WF					"DISCONNECT"


//==================CMD TO ESP==================//
#define CMD_CONNECT_WF					"CONNECT"
#define CMD_CONFIG_WF					"CONFIG"
#define CMD_TRANSMIT_DATA				"TRANSMIT"

void FSM_Init(void);
void FSM_LcdDisplay(void);
void FSM_SystemControl(void);

#endif /* INC_FSM_H_ */