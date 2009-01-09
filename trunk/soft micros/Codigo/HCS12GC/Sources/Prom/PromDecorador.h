#ifndef _PROM_DECORADOR_H
#define _PROM_DECORADOR_H

#include "PromBkp.h"


struct PromDecorador{
  struct PromBkp super;
  struct PromBkp * promBkp;
};



#endif