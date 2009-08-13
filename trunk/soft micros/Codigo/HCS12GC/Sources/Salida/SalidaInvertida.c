#include "SalidaInvertida.h"
#include "stddef.h"

void SalidaInvertida_setPotencia(void * _self,uint potencia);

const struct ISalidaClass SalidaInvertida={
  ISALIDA_CLASS_INITIALIZATION(ISalidaClass,
                               SalidaInvertida,
                               DecoradorSalida,
                               DecoradorSalida_defConstructor,
                               NULL,
                               NULL,
                               NULL,
                               DecoradorSalida_getPotencia,
                               SalidaInvertida_setPotencia,         
                               DecoradorSalida_getTipoSalida,
                               DecoradorSalida_setTipoSalida,
                               DecoradorSalida_getConectada,
                               DecoradorSalida_setConectada)  				
};



bool SalidaInvertida_getInvertida(struct SalidaInvertida * self){
  return self->invertida;   
}

void SalidaInvertida_setInvertida(void * _self,bool invertida){
  struct SalidaInvertida * self = (struct SalidaInvertida *)_self;
  self->invertida = invertida; 
}


void SalidaInvertida_setPotencia(void * _self,uint potencia){
  struct SalidaInvertida * self = (struct SalidaInvertida *)_self;
  if(self->invertida)
    potencia = 1000 - potencia;
  DecoradorSalida_setPotencia(_self,potencia);
}




