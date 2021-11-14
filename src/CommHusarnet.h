#ifndef COMMHUSARNET_H
#define  COMMHUSARNET_H
#ifdef XHusarnet
#include <WiFi.h>
#include <WiFiMulti.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Husarnet.h>
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
extern const char *husarnetJoinCode;
extern const char *dashboardURL;

// WiFi credentials
 extern const char* wifiNetworks[2][2];

extern const char *hostname;

#endif
/* =============== config section end =============== */

extern const int PORT;

// you can provide credentials to multiple WiFi networks
extern WiFiMulti wifiMulti;
extern AsyncWebServer server;

// Task functions
extern void taskWifi(void *parameter);
#endif  //COMMHUSARNET_H
#endif