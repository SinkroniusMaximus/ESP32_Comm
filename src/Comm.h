#ifndef Comms_h
#define Comms_h
extern String terminator;
void Comm_Cmd(String Address, String Value, String NexType);

class Comm
{
public:
int Expr;
bool Cmd_Received;
String Xchange_string;
String SignatureList;
char Signature;
String Serial_read;
String HWSerial_read;
String SerialBT_read;
String WifiAP_read;
String Buffer_string;
Comm();
void CommXchange(String terminator);
void CleanString(String terminator);
void SeekCmd(String* Destination, String* Source, bool* found, bool Overwrite);
void SeekCmdIn(String* Destination, String* SignatureList, String* Source, char signature);
void SeekCmdOut(String* Destination, String* SignatureList, String* Source, bool* Received, char* Signature);
};
extern Comm HMI_Comm;

class Xbool
{
  public:
    bool x;
    String HMI_Name;
    // Xbool();
    void Xupdate();
    void Xinit(String Name);//not possible to define string as param of constructor, so a method is used
  private:
    bool DB_Bool_Old;
};
class Xstring
{
  public:
    String txt;
    String HMI_Name;
    void Xinit(String Name);
    void Xupdate();
  private:  
    String DB_String_Old;  
};

class Xint
{
  public: 
    int val;
    String HMI_Name;
    void Xinit(String Name);
    void Xupdate();
  private:
    int DB_Int_Old; 
};
extern LinkedPointerList<Xint> Xintlist;
extern LinkedPointerList<Xstring> Xstringlist;
extern LinkedPointerList<Xbool> Xboollist;
#endif