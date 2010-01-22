#ifndef _ADC_HPP
#define _ADC_HPP

#include "PE_Types.h"
#include "IAdc.hpp"
#include "Timer/MethodTimer/MethodTimer.hpp"


class Adc : public IAdc {
  public:
  
    unsigned char pin;
    
    Adc(int pin);
    
    bool isNewVal();

    static AD_State getState();

    int getVal();

    void print(OutputStream& os);
    
     int getTemperaturaAmbiente();
  private:
   // unsigned char pin;
    static bool init;
    static MethodTimer *timerPeriodo;
    static const struct Method onPeriodo;
    //static void Adc::start(void * a);
};

#endif
