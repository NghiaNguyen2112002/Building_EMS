#include "MQTT_server.h"

WiFiClient espClient = WiFiClient();
PubSubClient client(espClient);

uint8_t flag_received_msg_from_sv;
static String msg;

void on_message(const char* topic, byte* payload, unsigned int length);

void SV_Init(void){
  client.setServer(SERVER_DOMAIN, 1883);
  client.setCallback(on_message);
}


void SV_Disconnect(void){
    client.disconnect();
}
void SV_Connect(void){
    if ( !client.connected() ) {
      Serial.print("Connecting to Server ...");
      if ( client.connect(CLIENT_ID, SERVER_USER, SERVER_PASS) ) {
        Serial.println( "[DONE]" );

        // Subscribing channel
        client.subscribe(CHANNEL_COMMAND);
      }
      else {
        Serial.print( "[FAILED] [ rc = " );
        Serial.println(client.state() );
      }
    }
    else Serial.println("Server connected");
}

bool SV_IsConnected(void){
  return client.connected();
}

void SV_ClientLoop(void){
  client.loop();
}


void SV_SendData(char* channel, char* json_string){
  Serial.print("Send: "); Serial.println(json_string);

  client.publish(channel, json_string);
}

uint8_t SV_IsReceivedMsg(void){
  if(flag_received_msg_from_sv){
    flag_received_msg_from_sv = 0;
    return 1;
  }

  return 0;
}

String SV_Get_Msg(void){
  return msg;
}

// The callback for when a PUBLISH message is received from the server.
void on_message(const char* topic, byte* payload, unsigned int length) {
  char json[length + 1];
  strncpy (json, (char*)payload, length);
  json[length] = '\0';
  
  flag_received_msg_from_sv = 1;
  
  msg = String(json);

  Serial.println(_cmd);
}
