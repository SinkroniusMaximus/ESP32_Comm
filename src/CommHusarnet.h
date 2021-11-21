#ifndef COMMHUSARNET_H
#define  COMMHUSARNET_H
#ifdef XHusarnet
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Husarnet.h>

void Start_Husarnet();
void Husarnet_Print(String cmd);
void RequestData();
void Cloud(String commAddress, String commValue, char* char_cmd, int cmd_length);
void updateWebpage(bool in);
String Husarnet_Read();
String Husarnet_Web_Read();

#endif
#endif  //COMMHUSARNET_H