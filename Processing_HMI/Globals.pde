            //rows, colums,x,y,width,height
Grid grid = new Grid(100,100);
String portName;
int serialListIndex;
int Baudrate = 256000;//500000;//250000;//115200;
ControlP5 cp5;
DropdownList d1;
Serial myPort;
Client c;
boolean d1isOpenOld;
boolean useClient = false;

class DB_HMI_Status//define status DB
{
    text_string Message;
    lamp_bool DigitalInput1;
    lamp_bool DigitalInput2;
    lamp_bool DigitalInput3;
    lamp_bool DigitalInput4;
    lamp_bool DigitalInput5;
    lamp_bool DigitalInput6;
    lamp_bool DigitalInput7;
    lamp_bool DigitalInput8;
    toggle_bool Relay1;
    toggle_bool Relay2;
    toggle_bool Relay3;
    toggle_bool Relay4;
    toggle_bool Relay5;
    toggle_bool Relay6;
    toggle_bool Relay7;
    toggle_bool Relay8;
    slider_int AnalogInput1;
    slider_int AnalogInput2;
    slider_int AnalogInput3;
    slider_int AnalogInput4;
    knob_int AnalogOutput1;
    knob_int AnalogOutput2;
    DB_HMI_Status()
    {
      Message = new text_string(7,20, "S1", "Message");
      DigitalInput1 = new lamp_bool(8, 2, "I1", "Digital Input 1");
      DigitalInput2 = new lamp_bool(8, 4, "I2", "Digital Input 2");
      DigitalInput3 = new lamp_bool(8, 6, "I3", "Digital Input 3");
      DigitalInput4 = new lamp_bool(8, 8, "I4", "Digital Input 4");
      DigitalInput5 = new lamp_bool(8, 10, "I5", "Digital Input 5");
      DigitalInput6 = new lamp_bool(8, 12, "I6", "Digital Input 6");
      DigitalInput7 = new lamp_bool(8, 14, "I7", "Digital Input 7");
      DigitalInput8 = new lamp_bool(8, 16, "I8", "Digital Input 8");
      Relay1 = new toggle_bool(5, 2, "O1", "Digital Output 1");
      Relay2 = new toggle_bool(5, 4, "O2", "Digital Output 2");
      Relay3 = new toggle_bool(5, 6, "O3", "Digital Output 3");
      Relay4 = new toggle_bool(5, 8, "O4", "Digital Output 4");
      Relay5 = new toggle_bool(5, 10, "O5", "Digital Output 5");
      Relay6 = new toggle_bool(5, 12, "O6", "Digital Output 6");
      Relay7 = new toggle_bool(5, 14, "O7", "Digital Output 7");
      Relay8 = new toggle_bool(5, 16, "O8", "Digital Output 8");
      AnalogInput1 = new slider_int(1 , 4, "X1", "Analog Input 1");
      AnalogInput2 = new slider_int(1 , 6, "X2", "Analog Input 2");
      AnalogInput3 = new slider_int(1 , 8, "X3", "Analog Input 3");
      AnalogInput4 = new slider_int(1 , 10, "X4", "Analog Input 4");
      AnalogOutput1 = new knob_int(2 , 12, "Y1", "Analog Output 1");
      AnalogOutput2 = new knob_int(2 , 18, "Y2", "Analog Output 2");
    }//define constructor   
};
DB_HMI_Status HMI_Status = new DB_HMI_Status();//create status DB and widgets
Comm_Recv HMI_Comm = new Comm_Recv(); //create comm server
