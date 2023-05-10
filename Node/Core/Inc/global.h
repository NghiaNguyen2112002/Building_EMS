/*
 * global.h
 *
 *  Created on: Apr 25, 2023
 *      Author: user
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "DHT.h"


#define NODE_ID				0


typedef struct Data_Pack{
    uint8_t node_id;
    float temp;
    float humid;
    uint16_t gas;
    uint16_t smoke;

//    Data_Pack(void){
//        node_id = NODE_ID;
//        temp = humid = 0;
//        gas = 0;
//        smoke = 0;
//    }
}Data_Pack;

extern Data_Pack _data;

extern DHT_Name _dht;


extern uint16_t _time_read_data;

#endif /* GLOBAL_H_ */
