#include "Globals.h"
/* create an instance of Preferences library to save variables*/
Preferences preferences;
DB_Comm DB;//create settings DB
<<<<<<< HEAD
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
=======
#ifdef XHusarnet
    String Husarnet_read;
    String Husarnetweb_read;
    String CommAddress;
    String CommValue;
    const String GarageHTML[] = {"<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"><style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}.button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}.button2 {background-color: #555555;}</style></head><body><h1>Garagedoor</h1><p>Open the door</p>"
                                ,"<p><a href=\"/web/O1/1\"><button class=\"button\">Open</button></a></p>"
                                ,"<p><a href=\"/web/O1/1\"><button class=\"button button2\">Open</button></a></p>"
                                ,"<p>Close the door</p>"
                                ,"<p><a href=\"/web/O1/0\"><button class=\"button\">Close</button></a></p>"
                                ,"<p><a href=\"/web/O1/0\"><button class=\"button button2\">Close</button></a></p>"
                                ,"</body></html>"};
    String Send_HTML;
#endif
>>>>>>> 8057c6cc97a52b975d8769149de8a3764bd42259
