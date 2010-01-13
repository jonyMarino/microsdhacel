#ifndef _IADC_HPP
#define _IADC_HPP


#include "Getter.hpp"
#include "PE_Types.h"
class IAdc : public Getter {
  public:
    virtual bool isNewVal()=0;
    virtual int getTemperaturaAmbiente()=0;
    enum AD_State {
        AD_CONVERTING,
        AD_WAITING

      };
    virtual AD_State getState()=0;

};
#endif
