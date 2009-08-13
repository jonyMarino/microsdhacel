
#include "DecoradorSalida.h"
#include "Salida_protected.h"

const struct ISalidaClass DecoradorSalida={
  ISALIDA_CLASS_INITIALIZATION(ISalidaClass,DecoradorSalida,Salida,Object_ctor,Object_dtor,Object_differ,Object_puto,getPotencia,NULL,NULL,NULL,NULL,NULL)
}; 

void DecoradorSalida_constructor(void * _self,struct ISalida * decorado){
  struct DecoradorSalida * self = (struct DecoradorSalida *) _self;
  self->decorado = decorado;  
}

void DecoradorSalida_defConstructor(void * _self,va_list *args){
  DecoradorSalida_constructor(_self,va_arg(*args,struct ISalida *));      
}


uint DecoradorSalida_getPotencia(void * _self){
  struct DecoradorSalida * self = (struct DecoradorSalida *)_self;
  return getPotencia(self->decorado);
}


void DecoradorSalida_setPotencia(void * _self,uint potencia){
  struct DecoradorSalida * self = (struct DecoradorSalida *)_self;
  setPotencia(self->decorado,potencia);
}

TipoSalida DecoradorSalida_getTipoSalida(void * _self){
    struct DecoradorSalida * self = (struct DecoradorSalida *)_self;
    return getTipoSalida(self->decorado);  
}

void DecoradorSalida_setTipoSalida(void * _self,TipoSalida tipoSalida){
    struct DecoradorSalida * self = (struct DecoradorSalida *)_self;
    setTipoSalida(self->decorado,tipoSalida);  
}

struct ISalida * DecoradorSalida_getDecorado(void * _self){
  struct DecoradorSalida * self = (struct DecoradorSalida *)_self;
  return self->decorado;
}

bool DecoradorSalida_getConectada(void * _self){
    struct DecoradorSalida * self = (struct DecoradorSalida *)_self;
    return getConectada(self->decorado);  
}

void DecoradorSalida_setConectada(void * _self,bool conectar){
    struct DecoradorSalida * self = (struct DecoradorSalida *)_self;
    setConectada(self->decorado,conectar);  
}



