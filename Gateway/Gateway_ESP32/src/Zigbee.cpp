#include "Zigbee.h"

SoftwareSerial sSerial;

static String msg;

void ZB_Init(uint8_t pin_rx, uint8_t pin_tx){
    sSerial.begin(9600, SWSERIAL_8N1, pin_rx, pin_tx);
}

void ZB_SendMsg(String msg){
    sSerial.print(msg);
}

uint8_t ZB_IsReceivedMsg(void){
    return sSerial.available();
}

String ZB_GetMsg(void){
    if(sSerial.available()){
        msg = sSerial.readStringUntil('#');
    }

    return msg;
}
