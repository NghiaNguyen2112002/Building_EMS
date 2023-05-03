#ifndef __INC_WIFI_CONTROLLER_H__
#define __INC_WIFI_CONTROLLER_H__

#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <EEPROM.h>

#define WIFI_NAME                           "Holmes211"
#define WIFI_PASSWORD                       "0906631096"

#define WIFI_GATEWAY_NAME                   "GATEWAY"
#define WIFI_GATEWAY_PASS                   "123456789"

#define TIME_CHECK_WF                       300       //3s

void WF_Init(void);


void WF_Connect(String wifi_name, String wifi_pass);
void WF_Disconnect(void);
bool WF_IsConnected(void);

void WF_BeginAP(void);
void WF_CloseAP(void);

void WF_CreateWebserver(void);

void WFCF_WebSVHandler(void);
uint8_t WFCF_IsDone(void);
String WFCF_Get_WFName(void);
String WFCF_Get_WFPass(void);

#endif