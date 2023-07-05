#include "Zigbee.h"

SoftwareSerial sSerial;


bool flag;
static String msg, result;

void ZB_Init(uint8_t pin_rx, uint8_t pin_tx){
    // Serial1.begin(9600);
    Serial1.begin(9600, SERIAL_8N1, pin_rx, pin_tx);
}

void ZB_SendMsg(String msg){
    Serial1.print(msg);
}

uint8_t ZB_IsReceivedMsg(void){

    // return Serial.available();
    return Serial1.available();
}

String ZB_GetMsg(void){
    flag = false;
    result = "";
    
    if(Serial1.available()){
        msg = Serial1.readStringUntil('#');

    }
    if(Serial1.available()){
        msg = Serial1.readStringUntil('#');
    }

    // msg = Serial1.readString();
    Serial.print("Receive: "); Serial.println(msg);

    if(msg.length() < 10) return "";

    
    for(uint16_t i = 0; i < msg.length(); i++){
        if(flag) {
            result += msg[i];
        }

        if(msg[i] == '!'){
            flag = true;
        }

    }
    return result;
}
