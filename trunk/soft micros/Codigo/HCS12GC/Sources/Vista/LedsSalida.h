#ifndef _LEDS_SALIDA_H
#define _LEDS_SALIDA_H

#include "PE_Types.h"

typedef struct{
  byte * addr;
  byte mask;
  byte ledNum;
}LedConfig;

struct LedsSalida{
  LedConfig * ledsConfig;
  int count; 
  void * thread; 
};


void LedsSalida_init(struct LedsSalida * self);

#define NEW_LEDS_SALIDA(nombre,ledsConfig)  \
  void * nombre##_thread;                   \
  const struct LedsSalida nombre = {        \
    ledsConfig,                             \
    sizeof(ledsConfig)/sizeof(LedConfig),   \
    &nombre##_thread                        \
  }

#endif