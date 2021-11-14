String terminator = "*";
ArrayList<Xint> Xintlist = new ArrayList<Xint>();
ArrayList<Xstring> Xstringlist = new ArrayList<Xstring>();
ArrayList<Xbool> Xboollist = new ArrayList<Xbool>();

void Comm_Cmd_String(String nxt_cmd, String terminator)//method
{
  if(HMI_Comm.AllowWrite)
  {
    try{
      myPort.write(nxt_cmd);
      myPort.write(terminator);
    } catch(Exception e){println(e);}
    if(useClient)
    {
      try{
        c.write(nxt_cmd);
        c.write(terminator);
      } catch(Exception e){}
    }
  }
}

class Comm_Recv
{
int Expr;
boolean Cmd_Received = false;
String uart_string = "";
String uart_read = "";
boolean AllowWrite = true;
boolean AllowRead = true;

Comm_Recv()
{
  Cmd_Received=false;
  Expr=0;
}

void SerialXchange(String terminator)
{

    int index;
      try{
      for(Xint ob : Xintlist)
      {
        ob.Xupdate();
      }
      for(Xstring ob : Xstringlist)
      {
        ob.Xupdate();
      }
      for(Xbool ob : Xboollist)
      {
        ob.Xupdate();
      }
      }
      catch(Exception e){}
      try
      {
      CleanString(terminator);//if nobody picked up the received command, clean it
      } catch(Exception e){}
      if(AllowRead)
      {
      try
      {
        if ((myPort.available() > 0)&(!Cmd_Received))
        {
            uart_read += myPort.readString();
            myPort.clear(); //clear buffer port
        }
      } catch(Exception e){}
      try
      {
        if ((c.available() > 0)&(!Cmd_Received)) {    // If there's incoming data from the client...
            uart_read += c.readString();
        }
      } catch(Exception e){}
      if (uart_read.length() > 0)
      {
          index = uart_read.indexOf(terminator);
          if (index != -1)
          {
            uart_string = uart_read.substring(0, index+1);
            if(uart_read.length() > index+1)
            {
              uart_read = uart_read.substring(index+1);
            }
            else
            {
              uart_read = "";  
            }
              Cmd_Received=true;
          }
      }
    }
  }
void CleanString(String terminator)
{
  int x;
  String Message;
  x = uart_string.length();
  if(Cmd_Received)
  {
    if(uart_string.substring(x-1).equals(terminator))// throw away thrash
    {
      Message = "Debug.processing=clean: ";
      Message += uart_string.substring(0, uart_string.length() - 1);
      println(Message);
      uart_string="";
      Cmd_Received=false;
    }
  }
}
};

class Xbool
{
    boolean DB_Bool_Old;
    boolean x;
    String HMI_Name;
    Xbool(String HMI_Name)
    {
      DB_Bool_Old = false;
      x = false;
      this.HMI_Name = HMI_Name;
      Xboollist.add(this);
    }
    void Xupdate()//exchange method for booleans
    {
      String temp_cmd;
      if(x!= DB_Bool_Old)
      {
        temp_cmd=HMI_Name;
        temp_cmd+="=";
        temp_cmd+=str(int(x));
        Comm_Cmd_String(temp_cmd, terminator);
      }
      int start_index = HMI_Name.length();
      int end_index = HMI_Comm.uart_string.length();
      if (HMI_Comm.Cmd_Received) 
      {
        if (HMI_Comm.uart_string.substring(0,start_index).equals(HMI_Name))
        {
          x = boolean((int(HMI_Comm.uart_string.substring(start_index+1,end_index-1))));
          HMI_Comm.uart_string="";
          HMI_Comm.Cmd_Received=false;
        }
      }
      DB_Bool_Old=x;
    }
};
class Xstring
{
    String DB_String_Old; 
    String txt;
    String HMI_Name;
    Xstring(String HMI_Name)
    {
      DB_String_Old = "";
      txt = "";
      this.HMI_Name = HMI_Name;
      Xstringlist.add(this);
    }
    void Xupdate()
    {
        String temp_cmd;
        if(!txt.equals(DB_String_Old))
        {
          temp_cmd=HMI_Name;
          temp_cmd+="=";
          temp_cmd+=txt;
          DB_String_Old=txt;
          Comm_Cmd_String(temp_cmd, terminator);
        }
      int start_index = HMI_Name.length();
      int end_index = HMI_Comm.uart_string.length();
        if (HMI_Comm.Cmd_Received) 
        {
          if (HMI_Comm.uart_string.substring(0,start_index).equals(HMI_Name))
          {
            txt = HMI_Comm.uart_string.substring(start_index+1,end_index-1);
            HMI_Comm.uart_string="";
            HMI_Comm.Cmd_Received=false;
          }
        }
        DB_String_Old=txt;
    }   
};

class Xint
{
    int DB_Int_Old; 
    int val;
    String HMI_Name;
    Xint(String HMI_Name)
    {
        DB_Int_Old=0;
        val=0;
        this.HMI_Name = HMI_Name;
        Xintlist.add(this);
    }
    void Xupdate()
    {
      String temp_cmd;
      if(val!=DB_Int_Old)
      {
        temp_cmd=HMI_Name;
        temp_cmd+="=";
        temp_cmd+=str(val);
        Comm_Cmd_String(temp_cmd, terminator);
      }
      int start_index = HMI_Name.length();
      int end_index = HMI_Comm.uart_string.length();
      if(HMI_Comm.Cmd_Received) 
      {
        if(HMI_Comm.uart_string.substring(0,start_index).equals(HMI_Name))
        {
          val = int(HMI_Comm.uart_string.substring(start_index+1,end_index-1));
          HMI_Comm.uart_string="";
          HMI_Comm.Cmd_Received=false;
        }
      }
      DB_Int_Old=val;
    }
};
