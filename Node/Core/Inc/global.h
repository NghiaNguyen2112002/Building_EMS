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
    float temp_0;
    float humid_0;
    float temp_1;
    float humid_1;
    float temp_2;
    float humid_2;
    float temp_3;
    float humid_3;
    uint16_t gas;
    uint16_t smoke;

//    Data_Pack(void){
//        node_id = NODE_ID;
//        temp_0 = humid_0 = 0;
//        temp_1 = humid_1 = 0;
//        temp_2 = humid_2 = 0;
//        temp_3 = humid_3 = 0;
//        gas = 0;
//        smoke = 0;
//    }
}Data_Pack;

extern Data_Pack _data;

extern DHT_Name _dht0, _dht1, _dht2, _dht3;


extern uint16_t _time_read_data;

#endif /* GLOBAL_H_ */
