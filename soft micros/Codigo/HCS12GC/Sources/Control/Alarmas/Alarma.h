#ifndef _ALARMA_H
#define _ALARMA_H

#include "Object.h"
#include "AlarmaConf.h"

struct Alarma {
  struct Object super;  
  struct AlarmaConf* configuracion;
};

typedef enum{
  ALARMA_CONTROL,
  ALARMA_RETRANSMISION   
}TTipoAlarma;


void Alarma_constructor(void * _self, struct AlarmaConf* configuracion);

byte setLazo(void*_self,fbyte);

fbyte getLazo(void*_self);

fbyte getAdaptadorSalida(void*_self);

byte   setAdaptadorSalida(void*_self,fbyte);
   
struct AlarmaConf* Alarma_getConfiguracion(void *_self);

int    Alarma_getRetLow(void*_self);
byte   Alarma_setRetLow(void*_self,int valor);


int    Alarma_getRetHi(void*_self);
byte   Alarma_setRetHi(void*_self,int valor);




#endif
