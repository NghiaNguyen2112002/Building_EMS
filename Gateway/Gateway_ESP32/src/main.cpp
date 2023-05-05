#include <Arduino.h>
// #include <WebServer.h>
#include <WiFi.h>
#include <PubSubClient.h> 
#include <EEPROM.h>

#include "input.h"
#include "global.h"
#include "lcd_i2c.h"
#include "MQTT_server.h"
#include "wifi_controller.h"
#include "Zigbee.h"
#include "fsm.h"
#include "pin.h"

#define SERIAL_DEBUG_BAUD       9600
#define EXCECUTING_CYCLE        50        //50ms

unsigned long time_now = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_DEBUG_BAUD);
  Serial.setTxBufferSize(256);

  EEPROM.begin(512);
  IN_Init();
  ZB_Init(PIN_ZIGBEE_TX, PIN_ZIGBEE_RX);
  WF_Init();
  SV_Init();
  FSM_Init();
  CLCD_Init(PIN_SDA, PIN_SCL, 0x27, 2, 16);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if(millis() >= time_now + EXCECUTING_CYCLE){
    time_now = millis();

    _counter_time_elapsed = (_counter_time_elapsed + 1) % 4000;

    IN_ReadButton();
    
    // program excecuted every 50ms
    if(_time_screen >= 5) _time_screen -= 5;

    // if(Serial.available()) ZB_SendMsg(Serial.readString());
    // Serial.print(ZB_GetMsg());

    FSM_SystemControl();
    FSM_LcdDisplay();

    CLCD_DisplayScreen();
  }

  WFCF_WebSVHandler();
  SV_ClientLoop();

}