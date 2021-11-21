#include "Globals.h"
Inputs::Inputs(int Pin, bool* Source)
{
  PinNr = Pin;
  Connector = Source;
}

void Inputs::Read()
{
  State = digitalRead(PinNr);
  *Connector=!State;
}
