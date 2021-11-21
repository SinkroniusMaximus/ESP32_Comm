#include "Globals.h"
String terminator = String("*");
String nextion_terminator = String(char(0xff)) + String(char(0xff)) + String(char(0xff));
LinkedPointerList<Xint> Xintlist;
LinkedPointerList<Xstring> Xstringlist;
LinkedPointerList<Xbool> Xboollist;

void Comm_Cmd(String Address, String Value, String NexType, byte signature)//method
{
  #if defined XSerial || defined XBluetooth || defined WifiAP || defined XHWSerial || defined XHusarnet
    String cmd = Address + "=" + Value + terminator;
  #endif
  #if defined XSerial || defined XSerial_Nextion
  bool ENSerial = (signature & 0b00000010) > 0;
  #endif
  #ifdef XBluetooth
    bool ENBT = (signature & 0b00000100) > 0;
  #endif
  #ifdef WifiAP
    bool ENWifi = (signature & 0b00001000) > 0;
  #endif
  #if defined WifiAP || defined XHWSerial || defined XHusarnet
    int cmd_length = cmd.length();
    char char_cmd[cmd_length+1]; 
    cmd.toCharArray(char_cmd, cmd_length+1);
  #endif
  #if defined XSerial_Nextion || defined XHWSerial_Nextion
    String nexcmd = Address + "." + NexType + "=";
    if(NexType == "txt")
    {
     nexcmd += "\"" + Value + "\"" + nextion_terminator;
    }
    else
    {
      nexcmd += Value + nextion_terminator;
    }
  #endif
  #if defined XHWSerial || defined XHWSerial_Nextion
    bool ENHWSerial = (signature & 0b00000001) > 0;
  #endif
  #ifdef XHWSerial_Nextion
    int nexcmd_length = nexcmd.length();
    char char_nexcmd[nexcmd_length+1]; 
    nexcmd.toCharArray(char_nexcmd, nexcmd_length+1);
  #endif

  #ifdef XSerial
    if(ENSerial)
    {
      Serial1.print(cmd);
    }
  #endif
  #ifdef XSerial_Nextion
    if(ENSerial)
    {
      Serial1.print(nexcmd);
    }  
  #endif

  #ifdef XBluetooth
    if(ENBT)
    {
      SerialBT.print(cmd);
    }
  #endif
  #ifdef WifiAP
    if(ENWifi)
    {
      if(client.connected())
      {
        // Serial.print(char_cmd);
        client.write(char_cmd, cmd_length);
      }
    }
  #endif
  #ifdef XHWSerial
    if(ENHWSerial)
    {
      HWSERIAL.flush();
      HWSERIAL.print(char_cmd);
    }
  #endif
  #ifdef XHWSerial_Nextion
    if(ENHWSerial)
    {
      HWSERIAL.flush();
      HWSERIAL.print(char_nexcmd);
    }
  #endif
  #ifdef XHusarnet   
    if((signature & 0b00010000) > 0)
    {
      Husarnet_Print(cmd);
      // Cloud(Address, Value, char_cmd, cmd_length); //push HTTP request
    }
  #endif
}

Comm::Comm() // constructor, initialize values while comm server is setup
{
  Cmd_Received=false;
  Expr=0;
}

void Comm::CommXchange(String terminator) // read data input, a method inside comm class
{
  String Message;
  int i;
  for (i = 0; i < Xintlist.size(); i=i+1)
  {
      Xintlist.get(i)->Xupdate();
  }
  for (i = 0; i < Xboollist.size(); i=i+1)
  {
      Xboollist.get(i)->Xupdate();
  }
  for (i = 0; i < Xstringlist.size(); i=i+1)
  {
      Xstringlist.get(i)->Xupdate();
  }
  CleanString(terminator);//looks like nobody pickup the received command, clean it
  #if defined XHWSerial || defined XHWSerial_Nextion 
  if ((HWSERIAL.available() > 0)&(!Cmd_Received))
  {
      HWSerial_read += String(char(HWSERIAL.read()));//Serial.readString();
  }
  #endif  
  #if defined XSerial || defined XSerial_Nextion
  if ((Serial1.available() > 0)&(!Cmd_Received))
  {
      Serial_read += String(char(Serial1.read()));//Serial.readString();
  }
  #endif
  #ifdef XBluetooth
  if ((SerialBT.available() > 0)&(!Cmd_Received))
  {
      SerialBT_read += String(char(SerialBT.read()));//Serial.readString();
  }
  #endif
  #ifdef WifiAP
    if(!client.connected())
    {
      if (client = server.available()) {                             // if you get a client,
        Serial.println("New Client.");           // print a message out the serial port
        String currentLine = "";                // make a String to hold incoming data from the client
      }
    }
    if(client.connected())
    {
      if(!Cmd_Received)
      {
        while(client.available())
        {
          char c = client.read();
          WifiAP_read += c; 
        }
      }
    }
  #endif
  #ifdef XHusarnet
      RequestData();
      Husarnet_read += Husarnet_Read();
      Husarnetweb_read += Husarnet_Web_Read();
  #endif
  #if defined XHWSerial || defined XHWSerial_Nextion
    SeekCmdIn(&Buffer_string, &SignatureList, &HWSerial_read, char(0b00000001));
  #endif
  #if defined XSerial || defined XSerial_Nextion
    SeekCmdIn(&Buffer_string, &SignatureList, &Serial_read, char(0b00000010));
  #endif
  #ifdef XBluetooth
    SeekCmdIn(&Buffer_string, &SignatureList, &SerialBT_read, char(0b00000100));
  #endif
  #ifdef WifiAP
    SeekCmdIn(&Buffer_string, &SignatureList, &WifiAP_read, char(0b00001000));
  #endif
  #ifdef XHusarnet
    SeekCmdIn(&Buffer_string, &SignatureList, &Husarnet_read, char(0b00010000));
    SeekCmdIn(&Buffer_string, &SignatureList, &Husarnetweb_read, char(0b00100000));
  #endif
  SeekCmdOut(&Xchange_string, &SignatureList, &Buffer_string, &Cmd_Received, &Signature);
  // if (Xchange_string.length() > 0)
  // {
  //   if(Xchange_string.substring(Xchange_string.length() - 1) == terminator)
  //   {
  //     Cmd_Received=true;
  //   }
  //   #if defined XSerial_Nextion || defined XHWSerial_Nextion
  //     if(Xchange_string.substring(Xchange_string.length() - 1) == nextion_terminator)
  //     {
  //       Cmd_Received=true;
  //     }      
  //   #endif
  // }
    
}

void Comm::CleanString(String terminator)
{
  int x;
  String Message;
  x = Xchange_string.length();
  if(Cmd_Received)
  {
    if(Xchange_string.substring(x-1) == terminator)// throw away thrash
    {
      Message = "Debug.txt=\"clean: ";
      Message += Xchange_string.substring(0, Xchange_string.length() - 1);
      Message += "\"";
      Serial1.println(Message);
      Xchange_string="";
      Cmd_Received=false;
    }
    #if defined XSerial_Nextion || defined XHWSerial_Nextion
    int nextermlen = nextion_terminator.length(); 
    if (Xchange_string.length() >= nextermlen)
    {
      if(Xchange_string.substring(x-nextermlen) == nextion_terminator)// throw away thrash
      {
        Xchange_string="";
        Cmd_Received=false;
      }
    }
    #endif
  }
}

void Comm::SeekCmd(String* Destination, String* Source, bool* found, bool Overwrite)
{
  int index;
  String Source_Copy;
  String Clean_String = "";
  Source_Copy = *Source;
  if (Source_Copy.length() > 0)
  {
      index = Source_Copy.indexOf(terminator);
      #if defined XSerial_Nextion || defined XHWSerial_Nextion
        if (index == -1)
        {
          index = Source_Copy.indexOf(nextion_terminator);
        }
      #endif
      if (index != -1)
      {
        int start_index = 0;
        if(Overwrite)
        {
          *Destination = Source_Copy.substring(start_index, index+1);
        }
        else
        {
          //skip erratic carriage return and linefeed from serial monitors
          if(Source_Copy.substring(0,2).equals("\r\n"))
          {
            start_index = 2;
          }
          else if(Source_Copy.substring(0,2).equals("\n\r"))
          {
            start_index = 2;
          }
          else if(Source_Copy.substring(0,1).equals("\r"))
          {
            start_index = 1;
          }
          if(Source_Copy.substring(0,1).equals("\n"))
          {
            start_index = 1;
          }
          *Destination += Source_Copy.substring(start_index, index+1);
        }
        if(Source_Copy.length() > index+1)
        {
          if(Source_Copy.substring(index+1)!="\n")
          {
            *Source = Source_Copy.substring(index+1);
          }
          else
          {
            *Source = "";
          }
        }
        else
        {
          *Source = "";
        }
        *found = true;
      }
  }
}

void Comm::SeekCmdIn(String* Destination, String* SignatureList, String* Source, char signature)
{
  bool rcv = false;
  SeekCmd(Destination, Source, &rcv, false);
  if(rcv)
  {
    *SignatureList += signature;
  }
}

void Comm::SeekCmdOut(String* Destination, String* SignatureList, String* Source, bool* Received, char* Signature)
{
  bool rcv = false;
  String ListCopy;
  ListCopy = *SignatureList;
  SeekCmd(Destination, Source, &rcv, true);
  if(rcv)
  {
    *Signature = ListCopy.charAt(0);
    *SignatureList = ListCopy.substring(1);
  }
  *Received = rcv;
}

Comm HMI_Comm;

void Xint::Xinit(String Name)//sort of constructor
{
  DB_Int_Old=0;
  val=0;
  HMI_Name = Name;
  Xintlist.add(this);
}

void Xint::Xupdate()
{
  String temp_cmd;
  if(val!= DB_Int_Old)
  {
    // Comm_Addr = HMI_Name;
    // Comm_Value = String(val);
    // temp_cmd=HMI_Name;
    // temp_cmd+=".val=";
    // temp_cmd+=Comm_Value;
    // Comm_Cmd_String(temp_cmd, terminator);
    Comm_Cmd(HMI_Name,String(val), "val", byte(0Xff));
  }
  if (HMI_Comm.Cmd_Received) 
  {
    int cmd_index = HMI_Comm.Xchange_string.indexOf("=");//equals
    if(cmd_index == -1)
    {
      cmd_index = HMI_Comm.Xchange_string.indexOf(char(32));//space
    }
    int start_index = HMI_Name.length();
    int end_index = HMI_Comm.Xchange_string.length();
    if (HMI_Comm.Xchange_string.substring(0,cmd_index) == HMI_Name)
    {
////      Serial.println(HMI_Comm.Xchange_string);
      String Number = HMI_Comm.Xchange_string.substring(start_index+1,end_index-1);
      val = Number.toInt();
      Comm_Cmd(HMI_Name,String(val), "val", ~(byte(HMI_Comm.Signature)));
      HMI_Comm.Xchange_string="";
      HMI_Comm.Cmd_Received=false;
    }
  }
  DB_Int_Old=val;
}

// Xbool::Xbool()
// {
//   DB_Bool_Old=false;
//   x=false;
// }

void Xbool::Xinit(String Name)//constructor
{
  DB_Bool_Old=false;
  x=false;
  HMI_Name = Name;
  Xboollist.add(this);
}

void Xbool::Xupdate()
{
  String temp_cmd;
  if(x!= DB_Bool_Old)
  {
    // Comm_Addr = HMI_Name;
    // Comm_Value = String(x);
    // temp_cmd=HMI_Name;
    // temp_cmd+=".val=";
    // temp_cmd+=Comm_Value;
    // Comm_Cmd_String(temp_cmd, terminator);
    Comm_Cmd(HMI_Name,String(x), "val",byte(0Xff));
  }
  if (HMI_Comm.Cmd_Received) 
  {
    int cmd_index = HMI_Comm.Xchange_string.indexOf("=");//equals
    if(cmd_index == -1)
    {
      cmd_index = HMI_Comm.Xchange_string.indexOf(char(32));//space
    }
    int start_index = HMI_Name.length();
    int end_index = HMI_Comm.Xchange_string.length();
    if (HMI_Comm.Xchange_string.substring(0,cmd_index) == HMI_Name)
    {
//      Serial.println(HMI_Comm.Xchange_string);
      String Bit = HMI_Comm.Xchange_string.substring(start_index+1,end_index-1); 
      x = (bool)(Bit.toInt());
      Comm_Cmd(HMI_Name,String(x), "val", ~(byte(HMI_Comm.Signature)));
      HMI_Comm.Xchange_string="";
      HMI_Comm.Cmd_Received=false;
    }
  }
  DB_Bool_Old=x;
}

void Xstring::Xinit(String Name)//constructor
{
  DB_String_Old="";
  txt="";
  HMI_Name = Name;
  Xstringlist.add(this);
}

void Xstring::Xupdate()
{
  String temp_cmd;
  if(txt!= DB_String_Old)
  {
    // Comm_Addr = HMI_Name;
    // Comm_Value = txt;
    // temp_cmd=HMI_Name;
    // temp_cmd+=".txt=\"";
    // temp_cmd+=txt;
    // temp_cmd+="\"";
    // Serial.println(temp_cmd);
    // Comm_Cmd_String(temp_cmd, terminator);
    Comm_Cmd(HMI_Name,txt, "txt",byte(0Xff));
    
  }
  if (HMI_Comm.Cmd_Received) 
  {
    int cmd_index = HMI_Comm.Xchange_string.indexOf("=");//equals
    if(cmd_index == -1)
    {
      cmd_index = HMI_Comm.Xchange_string.indexOf(char(32));//space
    }
    int start_index = HMI_Name.length();
    int end_index = HMI_Comm.Xchange_string.length();
    if (HMI_Comm.Xchange_string.substring(0,start_index) == HMI_Name)
    {
      txt = HMI_Comm.Xchange_string.substring(start_index+1,end_index-1);
      Comm_Cmd(HMI_Name,txt, "txt", ~(byte(HMI_Comm.Signature)));
      HMI_Comm.Xchange_string="";
      HMI_Comm.Cmd_Received=false;
    }
  }
  DB_String_Old=txt;
}