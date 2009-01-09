#include "Alarma.h"


void Alarma_constructor(void * _self, struct AlarmaConf* configuracion){
  struct Alarma * self = _self;
  
  self->configuracion = configuracion;  
}

struct AlarmaConf* Alarma_getConfiguracion(void * _self){
  struct Alarma * self = _self;
  
  return self->configuracion;   
}

 /*RetLow*/
 int Alarma_getRetLow(void * _self){
  struct Alarma * self = _self; 
  return _AlarmaConf_getRetLow(self->configuracion);
 }
 
 byte Alarma_setRetLow(void * _self,int retLow){
  struct Alarma * self = _self; 
  return _AlarmaConf_setRetLow(self->configuracion,retLow);
 }
 
 
 /*RetHi*/
 int Alarma_getRetHi(void * _self){
  struct Alarma * self = _self; 
  return _AlarmaConf_getRetHi(self->configuracion);
 }
 
 byte Alarma_setRetHi(void * _self,int retHi){
  struct Alarma * self = _self; 
  return _AlarmaConf_setRetHi(self->configuracion,retHi);
 }
 
 