#include "wifi_controller.h"

WebServer webserver(80);

String list_wf;
// the Wifi radio's status
int status = WL_IDLE_STATUS;

String wf_name, wf_pass;

uint8_t flag_config_success;

String MakePage(String title, String contents);


void WF_Init(void){
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect();

  // WiFi.softAP(WIFI_GATEWAY_NAME, WIFI_GATEWAY_PASS);

  // Serial.print("IP ap: "); Serial.println(WiFi.softAPIP());
}

bool WF_IsConnected(void){
  if(WiFi.status() == WL_CONNECTED){
    // Serial.print("IP sta: "); Serial.println(WiFi.localIP());
    return true;
  }

  return false;
}
void WF_Connect(String wifi_name, String wifi_pass){
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(wifi_name.c_str(), wifi_pass.c_str());
  }
}

void WF_BeginAP(void){
  WiFi.softAP(WIFI_GATEWAY_NAME, WIFI_GATEWAY_PASS);
  Serial.print("IP ap: "); Serial.println(WiFi.softAPIP());
}

void WF_CloseAP(void){
  WiFi.softAPdisconnect();
}

void WF_Disconnect(void){
  WiFi.disconnect();
}

//=======Webserver for config wifi=========//
void WF_CreateWebserver(void){
  WiFi.disconnect();              //ngat ket noi wifi
  WiFi.softAP(WIFI_GATEWAY_NAME, WIFI_GATEWAY_PASS);
  Serial.println(WiFi.softAPIP());

  int n = WiFi.scanNetworks();
  delay(100);
  list_wf = "";
  
  for (int i = 0; i < n; i++) {    //scan wf and list them
    list_wf += "<option value='";
    list_wf += WiFi.SSID(i);
    list_wf += "'>";
    list_wf += WiFi.SSID(i);
    list_wf += "</option>";
  }

  webserver.on("/", [](){
    String s = "<h1>Wi-Fi Configuration</h1>";
      s += "<form method='get' action='setap'><label>SSID: </label><select name='wf_name'>";
      s += list_wf;
      s += "Password: <input name='pass' length=64 type='passwod'>";
      s += "<input type='submit'>";
    webserver.send(200, "text/html", MakePage("Wifi Configuration", s));  
  });

  webserver.on("/setap", [](){
    wf_name = webserver.arg("wf_name");
    wf_pass = webserver.arg("pass");

    Serial.println(wf_name);
    Serial.println(wf_pass);
    
    String s = "<h1>Wifi configuration's successful !!</h1>";
    webserver.send(200, "text/html", MakePage("", s));
    
    flag_config_success = true;

  });

  Serial.println("Begin web server");
  webserver.begin();
}

void WFCF_WebSVHandler(void){
  webserver.handleClient();
}

uint8_t WFCF_IsDone(void){
  if(flag_config_success){
    flag_config_success = 0;
    return 1;
  }

  return 0;
}

String WFCF_Get_WFName(void){
  return wf_name;
}

String WFCF_Get_WFPass(void){
  return wf_pass;
}


//==================SUBFUNCTION=============//
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus){
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}


String MakePage(String title, String contents) {
  String s = "<!DOCTYPE html><html><head>";
  s += "<meta name=\"viewport\" content=\"width=device-width,user-scalable=0\">";
  s += "<title>";
  s += title;
  s += "</title></head><body>";
  s += contents;
  s += "</body></html>";
  return s;
}
