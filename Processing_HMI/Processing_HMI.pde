import processing.serial.*;
//import processing.net.*; 
import controlP5.*;
import java.util.*;
void setup() {
  clear();
  frameRate(1200);
  size(770, 768);
  grid.Resize(14,25);
  grid.Begin();
  TheSetupFunction();
  surface.setResizable(true);
  background(color(9,105,121));
  HMI_Comm.AllowRead=true;//allows reading from external devices
  useClient = false;//enables client for a wifi connection for example
}
void draw() {
    if(useClient)
    {
    try{
      if(!c.active())
      {
         c = new Client(this, "192.168.4.1", 80);  // Connect to server on port 80  
      }
      } catch(Exception e){}
    }
    background(color(9,105,121));
    HMI_Comm.SerialXchange(terminator);//receive the data
    Main_Page();
    for(ListInterface ob : Interfacelist)
    {
        ob.update();
    }  
}
