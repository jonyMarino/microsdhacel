#ifndef _SALIDARETENIDA_H
#define _SALIDARETENIDA_H


#include "AdaptacionSalida.h"

struct SalidaRetenida  {
  struct AdaptacionSalida super; 
  bool retenida;
};

extern const struct AdaptacionSalidaClass SalidaRetenida;

void SalidaRetenida_liberar(void * _self);

bool SalidaRetenida_getRetenida(void * _self);


#endif
