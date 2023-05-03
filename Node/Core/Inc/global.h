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
	uint8_t ID;
	DHT_Name dht0;
	DHT_Name dht1;
	DHT_Name dht2;
	DHT_Name dht3;
	uint16_t MP2;
	uint16_t MQ2;
}Data_Pack;


extern Data_Pack _data;

//extern DHT_Name _dht0, _dht1, _dht2, _dht3;


extern uint16_t _time_read_data;

#endif /* GLOBAL_H_ */
