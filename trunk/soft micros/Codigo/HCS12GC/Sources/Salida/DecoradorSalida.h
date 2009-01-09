#ifndef _DECORADOR_SALIDA_H
#define _DECORADOR_SALIDA_H

#include "Salida.h"

struct DecoradorSalida{
  struct ISalida super;
  struct ISalida * decorado;
};

extern const struct ISalidaClass DecoradorSalida; 

void DecoradorSalida_constructor(void * _self,struct ISalida * decorado);
void DecoradorSalida_defConstructor(void * _self,va_list *args);


struct ISalida * DecoradorSalida_getDecorado(void * _self);

uint DecoradorSalida_getPotencia(void * _self);
void DecoradorSalida_setPotencia(void * _self,uint potencia);
TipoSalida DecoradorSalida_getTipoSalida(void * _self);
void DecoradorSalida_setTipoSalida(void * _self,TipoSalida tipoSalida);
bool DecoradorSalida_getConectada(void * _self);  
void DecoradorSalida_setConectada(void * _self,bool conectar);
#endif
