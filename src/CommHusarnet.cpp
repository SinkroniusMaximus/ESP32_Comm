#include "Globals.h"
#ifdef XHusarnet
/* =============== config section start =============== */
#if __has_include("credentials.h")
#include "credentials.h"
#else
/* to get your join code go to https://app.husarnet.com
   -> select network
   -> click "Add element"
   -> select "join code" tab

   Keep it secret!
*/
const char *husarnetJoinCode = "fc94:b01d:1803:8dd8:b293:5c7d:7639:932a/xxxxxxxxxxxxxxxxxxxxxx";
const char *dashboardURL = "default";

// WiFi credentials
const char* wifiNetworks[2][2] = {
  {"wifi-ssid-one", "wifi-pass-one"},
  {"wifi-ssid-two", "wifi-pass-two"},
}; 

const char *hostname = "ESP32_UC";

#endif
/* =============== config section end =============== */

const int PORT = 8001;

// you can provide credentials to multiple WiFi networks
WiFiMulti wifiMulti;

// store index.html content in html constant variable (platformio feature)
AsyncWebServer server(PORT);

// Task functions
void taskWifi(void *parameter);

void taskWifi(void *parameter) {
  uint8_t stat = WL_DISCONNECTED;

  while (stat != WL_CONNECTED) {
    stat = wifiMulti.run();
    // Serial.printf("WiFi status: %d\r\n", (int)stat);
    delay(100);
  }

  // Serial.printf("WiFi connected\r\n", (int)stat);

  // Start Husarnet VPN Client
  Husarnet.start();

  // Start HTTP server
  server.begin();


  // LOG("READY!\r\n");

  while (1) {
    while (WiFi.status() == WL_CONNECTED) {
      delay(500);
    }
    // LOG("WiFi disconnected, reconnecting\r\n");
    delay(500);
    stat = wifiMulti.run();
    // LOG("WiFi status: %d\r\n", (int)stat);
  }
}
#endif