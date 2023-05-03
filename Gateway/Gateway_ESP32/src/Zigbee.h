#ifndef INC_ZIGBEE_H_
#define INC_ZIGBEE_H_

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "pin.h"


void ZB_Init(uint8_t pin_rx, uint8_t pin_tx);
void ZB_SendMsg(String msg);
uint8_t ZB_IsReceivedMsg(void);
String ZB_GetMsg(void);

#endif /* INC_ZIGBEE_H_ */
