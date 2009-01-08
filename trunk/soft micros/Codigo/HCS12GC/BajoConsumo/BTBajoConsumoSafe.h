#ifndef _BT_BAJO_CONSUMO_SAFE_H
#define _BT_BAJO_CONSUMO_SAFE_H

#include "BTBajoConsumo.h"

struct BTBajoConsumoSafe{
  struct BTBajoConsumo super;
  dword segundos;   //126 anos
};


#define BT_BAJO_CONSUMO_SAFE_PAGES_START 0x4600

extern const struct BTBajoConsumoClass BTBajoConsumoSafe;

#endif