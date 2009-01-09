#ifndef _INTEGRADOR_H
#define _INTEGRADOR_H

#include "Getter.h"
#include "Sensor.h"
  

typedef enum{
   OK,
   OF,
   UF
}t_state;

struct Integrador{
  struct Getter super;
  struct Sensor * sensor;
  ulong acumulador;
  int valorPrevio;
  uint constanteDeIntegracion;
  struct Method onNuevaMedicion;
  int limiteSuperior;
  int limiteInferior;
  t_state state;
};


extern const struct GetterClass Integrador;

int Integrador_getLimiteSuperior(void * _self);

void Integrador_setLimiteSuperior(void * _self, int valor);

int Integrador_getLimiteInferior(void * _self);

void Integrador_setLimiteInferior(void * _self, int valor);

void Integrador_resetAcumulador(void * _self);

int Integrador_getConstanteIntegracion(void * _self);

void Integrador_setConstanteIntegracion(void * _self,int valor);

#endif