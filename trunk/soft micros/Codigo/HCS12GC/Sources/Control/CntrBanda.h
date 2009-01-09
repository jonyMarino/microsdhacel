#ifndef _CNTR_BANDA_H
#define _CNTR_BANDA_H

#include "ValorControl.h"


struct CntrBanda {
  struct ValorControl super;
  struct getter * valControl2;
};

#pragma DATA_SEG CNTR_BANDA_DATA                                            
#pragma CODE_SEG CNTR_BANDA_CODE 
#pragma CONST_SEG DEFAULT

extern const struct TValorControlClass CntrBandaClass;

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 
#pragma CONST_SEG DEFAULT


#endif
