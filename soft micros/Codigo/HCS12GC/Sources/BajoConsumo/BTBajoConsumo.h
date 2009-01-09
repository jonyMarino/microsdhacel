#ifndef _BT_BAJO_CONSUMO_H
#define _BT_BAJO_CONSUMO_H


#include "BaseTiempo.h"
#include "Method.h"

struct BTBajoConsumo{
  struct BaseTiempo super;
  struct Method onRTI;
  ulong interrupciones;
  uint microsegundos;
  uint milisegundos;
};

struct BTBajoConsumoClass{
  struct BaseTiempoClass super;
  void(*onRTI)(void*);
};

extern const struct BTBajoConsumoClass BTBajoConsumo;


#endif
