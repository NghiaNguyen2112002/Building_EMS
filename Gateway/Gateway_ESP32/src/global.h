#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <Arduino.h>
#include <WebServer.h>
#include <WiFi.h>
#include <PubSubClient.h> 

#define NO_OF_NODES             2

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

    uint8_t is_connected; // = 1 if receiving data from node

    Data_Pack(){
        node_id = 0;
        temp_0 = humid_0 = 0;
        temp_1 = humid_1 = 0;
        temp_2 = humid_2 = 0;
        temp_3 = humid_3 = 0;
        gas = 0;
        smoke = 0;
        is_connected = 0;
    }
}Data_Pack;

extern Data_Pack _data_node[];

// Create WF client
extern WiFiClient _espClient;
// Create MQTT instance
extern PubSubClient _client;


extern String _wifi_name, _wifi_pass;

extern String _cmd;
extern bool _flag_config_success, _flag_received_cmd_from_sv;

extern uint16_t _time_screen;

extern uint16_t _counter_time_elapsed;
#endif