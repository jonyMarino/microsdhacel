#ifndef Base_TiempoBajo_Consumo_H
#define Base_TiempoBajo_Consumo_H

#include "BaseTimers.h"
#include "Method.h"

struct BaseTiempoBajoConsumo{
  struct BaseTimers super;
  struct Method onRTI;
  uint microSegAcumulados;
};

extern const struct BaseTimersClass BaseTiempoBajoConsumo;


#endif
