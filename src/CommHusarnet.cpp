#include "Globals.h"
#ifdef XHusarnet
#include <AsyncElegantOTA.h>

#define HTTP_PORT 8001

#if __has_include("credentials.h")

// For local development (rename credenials-template.h and type your WiFi and Husarnet credentials there)
#include "credentials.h"  

#else

// For GitHub Actions OTA deploment

// WiFi credentials
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASS;

// Husarnet credentials
const char *hostName = HUSARNET_HOSTNAME;
const char *husarnetJoinCode = HUSARNET_JOINCODE; // find at app.husarnet.com
const char *dashboardURL = "default";

#endif
unsigned long ms = 0;
unsigned long ms2 = 0;
AsyncWebServer server(HTTP_PORT);
const String GarageHTML[] = {"<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"><style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}.button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}.button2 {background-color: #555555;}</style></head><body><h1>&#9734&#9734&#9734 Famous Portal &#9734&#9734&#9734</h1><p>Open the portal</p>"
                           ,"<p><a href=\"/web/O1/1\"><button class=\"button\">Open</button></a></p>"
                           ,"<p><a href=\"/web/O1/1\"><button class=\"button button2\">Open</button></a></p>"
                           ,"<p>Close the portal</p>"
                           ,"<p><a href=\"/web/O1/0\"><button class=\"button\">Close</button></a></p>"
                           ,"<p><a href=\"/web/O1/0\"><button class=\"button button2\">Close</button></a></p>"
                           ,"</body></html>"};
String Send_HTML;
String Husarnet_read;
String Husarnet_write;
String Husarnet_writebuffer;
String Husarnetweb_read;
String CommAddress;
String CommValue;
AsyncClient* client_tcp_list[10];
int listindex;

void Start_Husarnet()
{
  // ===============================================
  // Wi-Fi, OTA and Husarnet VPN configuration
  // ===============================================

  // Serial.begin(115200,SERIAL_8N1, 16, 17); // remap default Serial (used by Husarnet logs) from P3 & P1 to P16 & P17
  // Serial.end();
  // Serial1.begin(115200,SERIAL_8N1, 3, 1); // remap Serial1 from P9 & P10 to P3 & P1

  // Serial1.println("\r\n**************************************");
  // Serial1.println("GitHub Actions OTA example");
  // Serial1.println("**************************************\r\n");

  // Init Wi-Fi 
  // Serial1.printf("📻 1. Connecting to: %s Wi-Fi network ", ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    static int cnt = 0;
    delay(500);
    // Serial1.print(".");
    cnt++;
    if(cnt > 10) {
      ESP.restart();
    }
  }
  
  // Serial1.println(" done\r\n");

  // Init Husarnet P2P VPN service
  Husarnet.selfHostedSetup(dashboardURL);
  Husarnet.join(husarnetJoinCode, hostName);
  Husarnet.start();

  // Serial1.printf("⌛ 2. Waiting for Husarnet to be ready ... ");
  delay(15000); // TODO: check connection status instead
  // Serial1.println("done\r\n");

  // define HTTP API for remote reset
  server.on("/reset", HTTP_POST, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Reseting ESP32 after 1s ...");
    // Serial1.println("Software reset on POST request");
    delay(1000);
    ESP.restart();
  });

  // Init OTA webserver (available under /update path)
  AsyncElegantOTA.begin(&server);
  server.begin();
  
  // ===============================================
  // PLACE YOUR APPLICATION CODE BELOW
  // ===============================================

  // Example webserver hosting table with known Husarnet Hosts
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
      request->send(200, "text/html", Send_HTML);
  });
// Send a GET request to <IP>/var/address/value
  server.on("^\\/var\\/(.+)\\/(.*+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
      String address = request->pathArg(0); //address
      String value = request->pathArg(1); //value
      Husarnet_read += (address + "=" + value + terminator);
      request->send(200, "text/plain", "Address: " + address + ", with value: " + value);
  });
  // Send a GET request to <IP>/var/data
  server.on("^\\/var\\/data$", HTTP_GET, [] (AsyncWebServerRequest *request) {
      // Serial1.println("request received");
      String message = "cmd::" + Husarnet_write + "::end";
      request->send(200, "text/plain", message);//dump data
      Husarnet_write="";

  });
  // Send a GET request to <IP>/var/address/value
  server.on("^\\/web\\/(.+)\\/(.*+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
      String address = request->pathArg(0); // address
      String value = request->pathArg(1); //value
      Husarnetweb_read += (address + "=" + value + terminator);
      updateWebpage(bool(value.toInt()));// update and send modified webpage, currently only supports the open and close button
      request->send(200, "text/html", Send_HTML);
  });
}

void Cloud(String commAddress, String commValue, char* char_cmd, int cmd_length) {
  CommAddress = commAddress;
  CommValue = commValue;
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
            // Serial1.printf("\r\nSENDING ERROR!\r\n");
          }
        }, client_tcp);

        client_tcp->onData([](void *arg, AsyncClient *client, void *data, size_t len) {
          // Serial1.printf("\r\nResponse from %s\r\n", client->remoteIP().toString().c_str());
          // Serial1.write((uint8_t *)data, len);
          client->close();
        }, client_tcp);

        client_tcp->onDisconnect([](void* arg, AsyncClient* client) {
          // Serial1.println("[CALLBACK] discconnected");
          delete client;
        }, client_tcp);
        
        client_tcp->onError([](void* arg, AsyncClient* client, int8_t error) {
          // Serial1.printf("[CALLBACK] error: %d\r\n", error);
        }, NULL);

        client_tcp->onTimeout([](void* arg, AsyncClient* client, uint32_t time) {
          // Serial1.println("[CALLBACK] ACK timeout");
        }, NULL);
        
        client_tcp->connect(peerAddr, HTTP_PORT);
      // LOG("Sending HTTP req to:\r\n%s:\r\n%s\r\n\r\n", host.second.c_str(), host.first.toString().c_str());
    }
  }
}
void Husarnet_Print(String cmd)
{
  if(Husarnet_write.length()+cmd.length()<250)
  {
    Husarnet_write += cmd;
  }
}

void RequestData() {
  listindex=0;
  String hostname = String(hostName);
  hostname.toLowerCase();
  for (auto const &host : Husarnet.listPeers()) {
    IPv6Address peerAddr = host.first;
    if(host.second == "master") {
      ;
    } 
    else if (host.second == hostName||host.second == hostname.c_str())
    {
      ;
    }
    else {
      if(listindex<10)
      {
        if(!client_tcp_list[listindex])
        {
          client_tcp_list[listindex]= new AsyncClient;
          if(client_tcp_list[listindex])
          {
                client_tcp_list[listindex]->onConnect([](void *arg, AsyncClient *client) {
                  String requestURL = "/var/data";
                  String GETreq = String("GET ") + requestURL + " HTTP/1.1\r\n" + "Host: esp32\r\n" + "Connection: close\r\n\r\n";
                  if ( client->canSend() && (client->space() > GETreq.length())){
                    client->add(GETreq.c_str(), strlen(GETreq.c_str()));
                    client->send();
                  } else {
                    // Serial1.printf("\r\nSENDING ERROR!\r\n");
                  }
                }, client_tcp_list[listindex]);

                client_tcp_list[listindex]->onData([](void *arg, AsyncClient *client, void *data, size_t len) {
                  String filter1 = (char*)data;
                  int index1 = filter1.indexOf("cmd::")+5;
                  int index2 = filter1.indexOf("::end");
                  if(index1<len&&index2<len&&index1>0&&index2>0)
                  {
                    String filter2 = filter1.substring(index1, index2);
                    Husarnet_read += filter2;
                  }
                    client->close();
                  // 
                }, client_tcp_list[listindex]);

                client_tcp_list[listindex]->onDisconnect([](void* arg, AsyncClient* client) {
                  // Serial1.println("[CALLBACK] discconnected");
                  // delete client;
                }, client_tcp_list[listindex]);
                
                client_tcp_list[listindex]->onError([](void* arg, AsyncClient* client, int8_t error) {
                  // Serial1.printf("[CALLBACK] error: %d\r\n", error);
                }, NULL);

                client_tcp_list[listindex]->onTimeout([](void* arg, AsyncClient* client, uint32_t time) {
                  // Serial1.println("[CALLBACK] ACK timeout");
                }, NULL);
                
                client_tcp_list[listindex]->connect(peerAddr, HTTP_PORT);
                // Serial1.printf("Sending HTTP req to:\r\n%s:\r\n%s\r\n\r\n", host.second.c_str(), host.first.toString().c_str());
          }
        }
        if(client_tcp_list[listindex])
        {
          if(millis()>ms+1000||millis()<ms-1000)
          {
            if(client_tcp_list[listindex]->disconnected())
            {
              client_tcp_list[listindex]->connect(peerAddr, HTTP_PORT);
            }
          }
        }
      }
    }
    listindex++;
  }
  if(millis()>ms+1000||millis()<ms-1000)
  {
    ms=millis();
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
String Husarnet_Read()
{
  String temp = Husarnet_read;
  Husarnet_read = "";
  return temp;
}
String Husarnet_Web_Read()
{
  String temp = Husarnetweb_read;
  Husarnetweb_read = "";
  return temp;
}

#endif