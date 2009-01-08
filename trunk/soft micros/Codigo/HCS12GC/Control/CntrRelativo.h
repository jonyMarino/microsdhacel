#ifndef _CNTR_RELATIVO_H
#define _CNTR_RELATIVO_H

#include "ValorControl.h"

struct CntrRelativo{
  struct  ValorControl super;
  struct getter * valControl2;
};

extern const struct TValorControlClass CntrRelativoClass;


#endif
