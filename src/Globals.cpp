#include "Globals.h"
/* create an instance of Preferences library to save variables*/
Preferences preferences;
DB_Comm DB;//create settings DB
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