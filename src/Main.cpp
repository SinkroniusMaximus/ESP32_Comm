#include "Globals.h"
void setup() {
  The_Setup_Function();
  DB.Xinit();
  #ifdef XHusarnet
    updateWebpage(DB.Relay1.x);
  #endif
}

void loop() {
    HMI_Comm.CommXchange(terminator);
    if(DB.P_Relay1!=DB.Relay1.x)
    {
      #ifdef XHusarnet
        updateWebpage(DB.Relay1.x);
      #endif
      DB.P_Relay1=DB.Relay1.x;
    }
    delay(1);
    IO_Refresh();
    // DB.Message.txt = "Esp32 Universal Controller";
    DB.AnalogOutput1.val = DB.AnalogInput2.val;
    //Analog Inputs
    ADCRead(&An1.analogIn, &An2.analogIn, &An3.analogIn, &An4.analogIn);
    An1.Update();
    An2.Update();
    An3.Update();
    An4.Update();
}