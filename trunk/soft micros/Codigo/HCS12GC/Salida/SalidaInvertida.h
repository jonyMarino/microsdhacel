#ifndef _SALIDA_INVERTIDA_H
#define _SALIDA_INVERTIDA_H

#include "DecoradorSalida.h"


struct SalidaInvertida {
  struct DecoradorSalida super;
  bool invertida;
};

extern const struct ISalidaClass SalidaInvertida;

bool SalidaInvertida_getInvertida(struct SalidaConPolaridad * _self);

void SalidaInvertida_setInvertida(struct SalidaConPolaridad * _self,bool polaridad);


#endif
