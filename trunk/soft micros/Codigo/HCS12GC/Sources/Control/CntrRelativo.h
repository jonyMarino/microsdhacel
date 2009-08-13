#ifndef _CNTR_RELATIVO_H
#define _CNTR_RELATIVO_H

#include "ValorControl.h"

struct CntrRelativo{
  struct  ValorControl super;
  struct Getter * valControl2;
};

extern const struct ValorControlClass CntrRelativo;


#endif
