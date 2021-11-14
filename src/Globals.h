#ifndef GLOBALS_H
#define  GLOBALS_H
#define XSerial
// #define XBluetooth
// #define WifiAP
// #define XHWSerial
// #define XSerial_Nextion
// #define XHWSerial_Nextion
// #define XHusarnet
///////////////
// Includes
///////////////
#include <Arduino.h>
#include <stdio.h>
#include <math.h>
#include <Preferences.h>
#include <String.h>
#include "CommHusarnet.h"
#include "WifiAP.h"
#include "BT.h"
#include "Setup.h"
#include "LinkedPointerList.h"        //Install this library for it to work
#include "Comm.h"
#include "DB.h"
#if defined XHWSerial || defined XHWSerial_Nextion
    #define HWSERIAL Serial2
#endif
#ifdef XHusarnet
    extern String Husarnet_read;
    extern String Husarnetweb_read;
    extern String CommAddress;
    extern String CommValue;
    extern const String GarageHTML[];
    extern String Send_HTML;
#endif
/* create an instance of Preferences library to save variables*/
extern Preferences preferences;
extern DB_Comm DB;//create settings DB
#endif  //GLOBALS_H