#include "Globals.h"
void setup() {
  The_Setup_Function();
  DB.Xinit();
}

void loop() {
  #ifdef XHusarnet
    updateWebpage(DB.Relay1.x);
  #endif
  while (1) {
    HMI_Comm.CommXchange(terminator);
    if(DB.P_Relay1!=DB.Relay1.x)
    {
      #ifdef XHusarnet
        updateWebpage(DB.Relay1.x);
      #endif
      digitalWrite(2,DB.Relay1.x);
      DB.P_Relay1=DB.Relay1.x;
    }
  }
}