#ifndef __MQTT_SERVER_H__
#define __MQTT_SERVER_H__

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h> 

#include "global.h"


// Adafruit server is used in this library//
#define SERVER_PASS                         ""
#define SERVER_DOMAIN                       "broker.mqtt-dashboard.com"
#define SERVER_USER                         ""

#define CLIENT_ID                           "Building"


//==========CHANNEL===========//
#define CHANNEL_DATA                             "building_data"
#define CHANNEL_COMMAND                          "building_cmd"

void SV_Init(void);
void SV_Connect(void);
bool SV_IsConnected(void);
void SV_SendData(char* channel, char* json_string);

uint8_t SV_IsReceivedMsg(void);
String SV_Get_Msg(void);
void SV_ClientLoop(void);

#endif