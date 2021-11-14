#ifndef WifiAP_h
#define WifiAP_h
    #ifdef WifiAP
        #include <WiFi.h>
        #include <WiFiClient.h>
        #include <WiFiAP.h>
        extern WiFiServer server;
        extern WiFiClient client;
        void Start_WifiAP();
    #endif
#endif