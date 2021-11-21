#ifndef GLOBALS_H
#define  GLOBALS_H
#define XSerial
// #define XBluetooth
// #define WifiAP
// #define XHWSerial
// #define XSerial_Nextion
// #define XHWSerial_Nextion
#define XHusarnet
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

///////////////
// Pin assignments
///////////////

#define DI1_Pin 36
#define DI2_Pin 39
#define DI3_Pin 34
#define DI4_Pin 35
#define DI5_Pin 32
#define DI6_Pin 33
#define DI7_Pin 27
#define DI8_Pin 14

#define DO1_Pin 23
#define DO2_Pin 19
#define DO3_Pin 18
#define DO4_Pin 17
#define DO5_Pin 16
#define DO6_Pin 4
#define DO7_Pin 2
#define DO8_Pin 15

#define AO1_Pin 25
#define AO2_Pin 26

#define Latch_Pin 12
#define DataIn_Pin 13
#define DataOut_Pin 5
#define Clock_Pin 0

#define SCL_Pin 22
#define SDA_Pin 21

#include "ADC.h"
#include "DI.h"
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

///////////////
// Variables
///////////////

extern bool Always_Off;
extern bool Always_On;

///////////////
// Input Connectors
///////////////

extern AnalogValue An1;
extern AnalogValue An2;
extern AnalogValue An3;
extern AnalogValue An4;

extern Inputs DI1;
extern Inputs DI2;
extern Inputs DI3;
extern Inputs DI4;
extern Inputs DI5;
extern Inputs DI6;
extern Inputs DI7;
extern Inputs DI8;
#endif  //GLOBALS_H