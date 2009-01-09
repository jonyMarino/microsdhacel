#ifndef _SALIDA_SIMULADA_H
#define _SALIDA_SIMULADA_H

#include "Salida.h"

struct SalidaSimulada{
  struct Salida super;
  TipoSalida tipoSalida;
  int duty;
};

extern const struct ISalidaClass SalidaSimulada;

#endif