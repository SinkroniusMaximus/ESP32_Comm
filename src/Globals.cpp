#include "Globals.h"
/* create an instance of Preferences library to save variables*/
Preferences preferences;
DB_Comm DB;//create settings DB
///////////////
// Variables
///////////////

bool Always_Off = false;
bool Always_On = true;

///////////////
// Input Connectors
///////////////

AnalogValue An1(&DB.AnalogInput1.val,1588, 26544, 0, 100);
AnalogValue An2(&DB.AnalogInput2.val,1588, 26544, 0, 100);
AnalogValue An3(&DB.AnalogInput3.val,1588, 26544, 0, 100);
AnalogValue An4(&DB.AnalogInput4.val,1588, 26544, 0, 100);

Inputs DI1(DI1_Pin, &DB.DigitalInput1.x);
Inputs DI2(DI2_Pin, &DB.DigitalInput2.x);
Inputs DI3(DI3_Pin, &DB.DigitalInput3.x);
Inputs DI4(DI4_Pin, &DB.DigitalInput4.x);
Inputs DI5(DI5_Pin, &DB.DigitalInput5.x);
Inputs DI6(DI6_Pin, &DB.DigitalInput6.x);
Inputs DI7(DI7_Pin, &DB.DigitalInput7.x);
Inputs DI8(DI8_Pin, &DB.DigitalInput8.x);