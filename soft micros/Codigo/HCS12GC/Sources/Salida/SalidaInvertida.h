#ifndef _SALIDA_INVERTIDA_H
#define _SALIDA_INVERTIDA_H

#include "DecoradorSalida.h"


struct SalidaInvertida {
  struct DecoradorSalida super;
  bool invertida;
};

extern const struct ISalidaClass SalidaInvertida;

bool SalidaInvertida_getInvertida(void * _self);

void SalidaInvertida_setInvertida(void * _self,bool polaridad);


#endif
