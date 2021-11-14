#ifndef DB_h
#define DB_h

class DB_Comm//define status DB
{
  public:
    Xstring Message;
    Xbool DigitalInput1;
    Xbool DigitalInput2;
    Xbool DigitalInput3;
    Xbool DigitalInput4;
    Xbool DigitalInput5;
    Xbool DigitalInput6;
    Xbool DigitalInput7;
    Xbool DigitalInput8;
    
    Xbool Relay1;
    Xbool Relay2;
    Xbool Relay3;
    Xbool Relay4;
    Xbool Relay5;
    Xbool Relay6;
    Xbool Relay7;
    Xbool Relay8;
    Xint AnalogInput1;
    Xint AnalogInput2;
    Xint AnalogInput3;
    Xint AnalogInput4;
    Xint AnalogOutput1;
    Xint AnalogOutput2;
    bool P_Relay1;
    
    void Xinit();//define constructor

};

#endif