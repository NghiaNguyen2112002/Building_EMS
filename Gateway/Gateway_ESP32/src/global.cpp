#include "global.h"

WiFiClient _espClient = WiFiClient();
PubSubClient _client(_espClient);

Data_Pack _data_node[NO_OF_NODES];

String _wifi_name = "MANGDAYKTX H1-518";
String _wifi_pass = "20202024"; 

String _cmd = "";

bool _flag_config_success = false;

bool _flag_received_cmd_from_sv = false;

uint16_t _time_screen = 0;

uint16_t _counter_time_elapsed = 0;