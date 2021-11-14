#include "Globals.h"
void The_Setup_Function()
{
      // Serial.begin(256000);//to use serial for other purposes than communicating
    #if defined XSerial || defined XSerial_Nextion 
        Serial.begin(256000);
    #endif
    #ifdef XBluetooth
      SerialBT.begin("ESP32_UC"); //Bluetooth device name
    #endif
    #ifdef WifiAP
      Start_WifiAP();
    #endif
    #ifdef XHusarnet
      Start_Husarnet();
    #endif
    #if defined XHWSerial || defined XHWSerial_Nextion
        HWSERIAL.begin(256000);
    #endif
    pinMode(2, OUTPUT);//Digital Output 2
    #ifdef XHusarnet
    xTaskCreate(taskWifi,   /* Task function. */
            "taskWifi", /* String with name of task. */
            10000,      /* Stack size in bytes. */
            NULL,       /* Parameter passed as input of the task */
            1,          /* Priority of the task. */
            NULL);      /* Task handle. */
    #endif
}
#ifdef XHusarnet
void Start_Husarnet()
{
    // Save Wi-Fi credentials
    for (int i = 0; i < (sizeof(wifiNetworks)/sizeof(wifiNetworks[0])); i++) {
        wifiMulti.addAP(wifiNetworks[i][0], wifiNetworks[i][1]);
        // Serial.printf("WiFi %d: SSID: \"%s\" ; PASS: \"%s\"\r\n", i, wifiNetworks[i][0], wifiNetworks[i][1]);
    }

    // Husarnet VPN configuration 
    Husarnet.selfHostedSetup(dashboardURL);
    Husarnet.join(husarnetJoinCode, hostname);

    // A dummy web server (see index.html)
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(200, "text/html", Send_HTML);
    });

    // Send a GET request to <IP>/led/<number>/state/<0 or 1>
    server.on("^\\/led\\/([0-9]+)\\/state\\/([0-9]+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String ledNumber = request->pathArg(0); // currently unused - we use only a predefined LED number
        String state = request->pathArg(1);

        // digitalWrite(LED_PIN, state.toInt());
        request->send(200, "text/plain", "LED: " + ledNumber + ", with state: " + state);
    });
    // Send a GET request to <IP>/var/address/value
    server.on("^\\/var\\/(.+)\\/(.*+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String address = request->pathArg(0); // currently unused - we use only a predefined LED number
        String value = request->pathArg(1);
        Husarnet_read += (address + "=" + value + terminator);
        // request->send(200, "text/plain", "Var: " + address + ", with value: " + value);
    });
    // Send a GET request to <IP>/var/address/value
    server.on("^\\/web\\/(.+)\\/(.*+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String address = request->pathArg(0); // currently unused - we use only a predefined LED number
        String value = request->pathArg(1);
        Husarnetweb_read += (address + "=" + value + terminator);
        updateWebpage(bool(value.toInt()));
        request->send(200, "text/html", Send_HTML);
        // request->send(200, "text/plain", "Var: " + address + ", with value: " + value);
    });

}

void Cloud() {
  for (auto const &host : Husarnet.listPeers()) {
    IPv6Address peerAddr = host.first;
    if(host.second == "master") {
      ;
    } else {
      AsyncClient* client_tcp = new AsyncClient;
      
      client_tcp->onConnect([](void *arg, AsyncClient *client) {
        String requestURL = "/var/" + CommAddress + "/" + CommValue;
        String GETreq = String("GET ") + requestURL + " HTTP/1.1\r\n" + "Host: esp32\r\n" + "Connection: close\r\n\r\n";

        if ( client->canSend() && (client->space() > GETreq.length())){
          client->add(GETreq.c_str(), strlen(GETreq.c_str()));
	        client->send();
        } else {
          // Serial.printf("\r\nSENDING ERROR!\r\n");
        }
      }, client_tcp);

      client_tcp->onData([](void *arg, AsyncClient *client, void *data, size_t len) {
        // Serial.printf("\r\nResponse from %s\r\n", client->remoteIP().toString().c_str());
	      Serial.write((uint8_t *)data, len);
        client->close();
      }, client_tcp);

      client_tcp->onDisconnect([](void* arg, AsyncClient* client) {
        // Serial.println("[CALLBACK] discconnected");
        delete client;
      }, client_tcp);
      
      client_tcp->onError([](void* arg, AsyncClient* client, int8_t error) {
        // Serial.printf("[CALLBACK] error: %d\r\n", error);
      }, NULL);

      client_tcp->onTimeout([](void* arg, AsyncClient* client, uint32_t time) {
        // Serial.println("[CALLBACK] ACK timeout");
      }, NULL);
      
      client_tcp->connect(peerAddr, PORT);

      // LOG("Sending HTTP req to:\r\n%s:\r\n%s\r\n\r\n", host.second.c_str(), host.first.toString().c_str());
    }
  }
}

void updateWebpage(bool in)
{
  Send_HTML = GarageHTML[0];
  if(in)
  {
    Send_HTML+=GarageHTML[1];
  }
  else
  {
    Send_HTML+=GarageHTML[2];
  }
  Send_HTML+=GarageHTML[3];
  if(!in)
  {
    Send_HTML+=GarageHTML[4];
  }
  else
  {
    Send_HTML+=GarageHTML[5];
  }
  Send_HTML+=GarageHTML[6];
}

#endif