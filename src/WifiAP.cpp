#include "Globals.h"
#ifdef WifiAP
    const char *ssid = "yourAP";
    const char *password = "yourPassword";
    WiFiServer server(80);
    WiFiClient client = server.available();   // listen for incoming clients
    void Start_WifiAP()
    {
        // You can remove the password parameter if you want the AP to be open.
        WiFi.softAP(ssid, password);
        IPAddress myIP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(myIP);
        server.begin();
    }
#endif