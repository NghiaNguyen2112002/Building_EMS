#include <Arduino.h>
#include <WebServer.h>
#include <WiFi.h>
#include <PubSubClient.h> 
#include <EEPROM.h>
#include <esp_sleep.h>


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
  delay(100);
  Serial.setTxBufferSize(256);
  Serial.begin(SERIAL_DEBUG_BAUD);

  EEPROM.begin(512);
  IN_Init();
  ZB_Init(PIN_ZIGBEE_RX, PIN_ZIGBEE_TX);
  WF_Init();
  SV_Init();
  FSM_Init();
  CLCD_Init(PIN_SDA, PIN_SCL, 0x27, 2, 16);
  

  gpio_wakeup_enable(PIN_DEBUG_RX, GPIO_INTR_LOW_LEVEL);
  gpio_wakeup_enable(PIN_ZIGBEE_RX, GPIO_INTR_LOW_LEVEL);  


  gpio_wakeup_enable(PIN_SW_WAKEUP, GPIO_INTR_LOW_LEVEL);

  esp_sleep_enable_gpio_wakeup();

  Serial.println("\nBEGIN");
}

void loop() {
  // put your main code here, to run repeatedly:  
  if(millis() >= time_now + EXCECUTING_CYCLE){
    time_now = millis();

    _counter_time_elapsed = (_counter_time_elapsed + 1) % 4000;

    IN_ReadButton();
    
    // program excecuted every 50ms
    if(_time_screen >= 5) _time_screen -= 5;
    if(_time_out_sleep >= 5) _time_out_sleep -= 5;
    if(_time_reconnect >= 5) _time_reconnect -= 5;

    // if(Serial.available()) ZB_SendMsg(Serial.readString());
    // Serial.print(ZB_GetMsg());

    FSM_SystemControl();
    FSM_LcdDisplay();

    CLCD_DisplayScreen();
  }

  WFCF_WebSVHandler();
  SV_ClientLoop();
}