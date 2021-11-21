#ifndef DI_h
#define DI_h

class Inputs
{
  public:
  bool P_State;
  bool State;
  int PinNr;
  bool* Connector;
  Inputs(int Pin, bool* Source);
  void Read();
};

#endif
