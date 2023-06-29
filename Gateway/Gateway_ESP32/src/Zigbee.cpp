#include "Zigbee.h"

SoftwareSerial sSerial;


bool flag;
static String msg, result;

void ZB_Init(uint8_t pin_rx, uint8_t pin_tx){
    sSerial.begin(9600, SWSERIAL_8N1, pin_rx, pin_tx);
}

void ZB_SendMsg(String msg){
    sSerial.print(msg);
}

uint8_t ZB_IsReceivedMsg(void){

    return Serial.available();
    // return sSerial.available();
}

String ZB_GetMsg(void){
    // if(sSerial.available()){
    //     msg = sSerial.readStringUntil('#');
    // }

    flag = false;
    result = "";
    if(Serial.available()){
        msg = Serial.readStringUntil('#');

    }
    if(Serial.available()){
        msg = Serial.readStringUntil('#');
    }

    Serial.println(msg);

    for(uint16_t i = 0; i < msg.length(); i++){
        if(flag) result += msg[i];

        if(msg[i] == '!'){
            flag = true;
        }

    }
    // msg = msg.substring(msg.lastIndexOf('!'));

    return result;
}
