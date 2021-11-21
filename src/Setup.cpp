#include "Globals.h"
void The_Setup_Function()
{
              //Set the GPIO
    pinMode(DI1_Pin, INPUT);//Digital Input 1
    pinMode(DI2_Pin, INPUT);//Digital Input 2
    pinMode(DI3_Pin, INPUT);//Digital Input 3
    pinMode(DI4_Pin, INPUT);//Digital Input 4
    pinMode(DI5_Pin, INPUT_PULLUP);//Digital Input 5
    pinMode(DI6_Pin, INPUT_PULLUP);//Digital Input 6
    pinMode(DI7_Pin, INPUT_PULLUP);//Digital Input 7
    pinMode(DI8_Pin, INPUT_PULLUP);//Digital Input 8

    pinMode(DO1_Pin, OUTPUT);//Digital Output 1
    pinMode(DO2_Pin, OUTPUT);//Digital Output 2
    pinMode(DO3_Pin, OUTPUT);//Digital Output 3
    pinMode(DO4_Pin, OUTPUT);//Digital Output 4
    pinMode(DO5_Pin, OUTPUT);//Digital Output 5
    pinMode(DO6_Pin, OUTPUT);//Digital Output 6
    pinMode(DO7_Pin, OUTPUT);//Digital Output 7
    pinMode(DO8_Pin, OUTPUT);//Digital Output 8
    
    pinMode(AO1_Pin, OUTPUT);//Analog Output 1
    pinMode(AO2_Pin,OUTPUT);//Analog Output 2

    // Start I2C ADC for Analog Inputs
    ads.begin();
    IO_Refresh();
      // Serial.begin(256000);//to use serial for other purposes than communicating
      // Serial1.begin(256000,SERIAL_8N1, 3, 1);
    #if defined XSerial || defined XSerial_Nextion 
        // Serial1.begin(256000);
        Serial1.begin(256000,SERIAL_8N1, 3, 1);
    #endif
    #ifdef XBluetooth
      SerialBT.begin("ESP32_UC"); //Bluetooth device name
    #endif
    #ifdef WifiAP
      Start_WifiAP();
    #endif
    #ifdef XHusarnet
      Start_Husarnet();
    #endif
    #if defined XHWSerial || defined XHWSerial_Nextion
        HWSERIAL.begin(256000);
    #endif
}

void IO_Refresh()
{
  //Digital Inputs
  DI1.Read();
  DI2.Read();
  DI3.Read();
  DI4.Read();
  DI5.Read();
  DI6.Read();
  DI7.Read();
  DI8.Read();
//  //Analog Outputs
  dacWrite(AO1_Pin,DB.AnalogOutput1.val);
  dacWrite(AO2_Pin,DB.AnalogOutput2.val);
//  //Digital Outputs
  digitalWrite(DO1_Pin,DB.Relay1.x);
  digitalWrite(DO2_Pin,DB.Relay2.x);
  digitalWrite(DO3_Pin,DB.Relay3.x);
  digitalWrite(DO4_Pin,DB.Relay4.x);
  digitalWrite(DO5_Pin,DB.Relay5.x);
  digitalWrite(DO6_Pin,DB.Relay6.x);
  digitalWrite(DO7_Pin,DB.Relay7.x);
  digitalWrite(DO8_Pin,DB.Relay8.x);
}