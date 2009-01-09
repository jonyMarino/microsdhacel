#ifndef _SALIDA_BLOQUEDA_H
#define _SALIDA_BLOQUEDA_H


#include "AdaptacionSalida.h"

struct SalidaBloqueada {
  struct AdaptacionSalida super;    
  bool bloqueada;
};

extern const struct AdaptacionSalidaClass SalidaBloqueadaClass;


#endif
