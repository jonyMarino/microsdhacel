#ifndef _IADC_HPP
#define _IADC_HPP


#include "Getter.hpp"
#include "PE_Types.h"
#pragma DATA_SEG IADC_DATA                                            
#pragma CODE_SEG IADC_CODE                     
#pragma CONST_SEG DEFAULT            /* Constant section for this module */


class IAdc : public Getter {
  public:
    virtual bool isNewVal()=0;
    virtual int getTemperaturaAmbiente()=0;
    enum AD_State {
        AD_CONVERTING,
        AD_WAITING

      };
   // virtual AD_State getState()=0;

};
#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT                     
#pragma CONST_SEG DEFAULT            /* Constant section for this module */


#endif


