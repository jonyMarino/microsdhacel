#ifndef _SALIDA_BANDA_H
#define _SALIDA_BANDA_H

#include "AdaptacionSalida.h"

//Usada para accion por exceso y defecto
struct SalidaBanda{
  struct AdaptacionSalida super;
};

extern const struct AdaptacionSalidaClass SalidaBanda;

void SalidaBanda_constructor(void * _self,struct AdaptSalidaConf * configuracion);



#endif
