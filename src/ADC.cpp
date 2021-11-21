#include "Globals.h"
/* create an instance of Adafruit_ADS1115 library */
Rubio_ADS1115 ads;
uint8_t ADC_turns;

void ADCRead(int* An1, int* An2, int* An3, int* An4)
{
  uint16_t tempRead;
  int16_t tempRead2;
  bool done = false;
        switch (ADC_turns)
        {
          case 0:
           ads.readADC_SingleEnded(0, &tempRead, &done);
           if(done)
           {
             tempRead2 = int16_t(tempRead);
             if(tempRead2 > 32768){tempRead2 -= 65535;}
             *An1 = (tempRead2);
           }
          break;
          case 1:
             ads.readADC_SingleEnded(1, &tempRead, &done);
             if(done)
             {
               tempRead2 = int16_t(tempRead);
               if(tempRead2 > 32768){tempRead2 -= 65535;}
               *An2 = (tempRead2);
             }
          break;
          case 2:
             ads.readADC_SingleEnded(2, &tempRead, &done);
             if(done)
             {
               tempRead2 = int16_t(tempRead);
               if(tempRead2 > 32768){tempRead2 -= 65535;}
               *An3 = (tempRead2);
             }
          break;
          case 3:
             ads.readADC_SingleEnded(3, &tempRead, &done);
             if(done)
             {
               tempRead2 = int16_t(tempRead);
               if(tempRead2 > 32768){tempRead2 -= 65535;}
               *An4 = (tempRead2);
             }
          break;
        }
        if(done)
        {
          ADC_turns=ADC_turns+1;
        }
        if (ADC_turns > 3)
        {
          ADC_turns=0;
        }
}

AnalogValue::AnalogValue(int* destination, uint32_t mxIn, uint32_t mxOut)
{
  this->destination = destination;
  this->mnIn = 0;
  this->mxIn = mxIn;
  this->mnOut = 0;
  this->mxOut = mxOut;
  useSimpleScale=true;
}

AnalogValue::AnalogValue(int* destination, uint32_t mnIn, uint32_t mxIn, uint32_t mnOut, uint32_t mxOut)
{
  this->destination = destination;
  this->mnIn = mnIn;
  this->mxIn = mxIn;
  this->mnOut = mnOut;
  this->mxOut = mxOut;
  useSimpleScale=false;
}


void AnalogValue::AnalogScale()
{
  float In = float(analogIn);
  float temp = ((float(In - mnIn) / float(mxIn - mnIn)) * float(mxOut - mnOut) + float(mnOut) + 0.5);
  val = uint16_t(temp);
}

void AnalogValue::SimpleAnalogScale()
{
  float In = float(analogIn);
  float temp =  (In / mxIn) * float(mxOut + 1);
  val = uint16_t(temp);
}
void AnalogValue::LimitAnalog()
{
  if(val > mxOut){val = mxOut;}
  else if(val < mnOut){val = mnOut;}
}
void AnalogValue::AnalogOnChange()
{
  if(val != analogOld)
  {
    *destination = (int)val;
    analogOld = val;
    isChanged =  true;
  }
  else
  {
    isChanged = false;
  }
}

void AnalogValue::Update()
{
  if(useSimpleScale)
  {
    SimpleAnalogScale();
  }
  else
  {
    AnalogScale();
  }
  LimitAnalog();
  AnalogOnChange();
}
