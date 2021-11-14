#include "Globals.h"


void DB_Comm::Xinit()//constructor
{   
    Message.Xinit("S1");
    DigitalInput1.Xinit("I1");
    DigitalInput2.Xinit("I2");
    DigitalInput3.Xinit("I3");
    DigitalInput4.Xinit("I4");
    DigitalInput5.Xinit("I5");
    DigitalInput6.Xinit("I6");
    DigitalInput7.Xinit("I7");
    DigitalInput8.Xinit("I8");
    
    Relay1.Xinit("O1");
    Relay2.Xinit("O2");
    Relay3.Xinit("O3");
    Relay4.Xinit("O4");
    Relay5.Xinit("O5");
    Relay6.Xinit("O6");
    Relay7.Xinit("O7");
    Relay8.Xinit("O8");
    AnalogInput1.Xinit("X1");
    AnalogInput2.Xinit("X2");
    AnalogInput3.Xinit("X3");
    AnalogInput4.Xinit("X4");
    AnalogOutput1.Xinit("Y1");
    AnalogOutput2.Xinit("Y2");  
    P_Relay1 = false;
}
