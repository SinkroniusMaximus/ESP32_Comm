//Clipping.h
#ifndef ADC_H
#define  ADC_H
//#include <Adafruit_ADS1015.h>
#include "Rubio_ADS1015.h"
extern Rubio_ADS1115 ads;
void ADCRead(int* An0, int* An1, int* An2, int* An3);
class AnalogValue
{
  public:
    uint32_t mnIn;
    uint32_t mxIn;
    uint32_t mnOut;
    uint32_t mxOut;
    int analogIn;
    uint16_t val;
    int* destination;
    uint16_t analogOld;
    bool isChanged;
    //constructors;
    AnalogValue(int* destination, uint32_t mxIn, uint32_t mxOut);
    AnalogValue(int* destination, uint32_t mnIn, uint32_t mxIn, uint32_t mnOut, uint32_t mxOut);
    //methods
    void AnalogScale();
    void SimpleAnalogScale();
    void LimitAnalog();
    void AnalogOnChange();
    void Update();
  private:
  bool  useSimpleScale;
};
#endif  //ADC_H
