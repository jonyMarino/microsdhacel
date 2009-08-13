#ifndef _CNTR_BANDA_H
#define _CNTR_BANDA_H

#include "ValorControl.h"

#pragma DATA_SEG CNTR_BANDA_DATA                                            
#pragma CODE_SEG CNTR_BANDA_CODE 
#pragma CONST_SEG DEFAULT


struct CntrBanda {
  struct ValorControl super;
  struct Getter * valControl2;
};



extern const struct ValorControlClass CntrBanda;

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 
#pragma CONST_SEG DEFAULT


#endif
