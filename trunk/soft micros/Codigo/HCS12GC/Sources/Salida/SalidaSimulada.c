#include "stddef.h"
#include "SalidaSimulada.h"
#include "Salida_protected.h"

//void SalidaSimulada_defCtor(void *,va_list *);
uint SalidaSimulada_getDuty(void*);
void SalidaSimulada_setDuty(void*,uint);
void SalidaSimulada_setTipo(void*,TipoSalida);			
TipoSalida SalidaSimulada_getTipo(void*);	
  
const struct ISalidaClass SalidaSimulada={
  ISALIDA_CLASS_INITIALIZATION(ISalidaClass,
                                SalidaSimulada,
                                Salida,
                                NULL,
                                NULL,
                                NULL,
                                NULL,
                                SalidaSimulada_getDuty,
                                SalidaSimulada_setDuty,
                                SalidaSimulada_getTipo,
                                SalidaSimulada_setTipo,
                                Salida_getConectada,
                                Salida_setConectada) 
};


uint SalidaSimulada_getDuty(void* self ){
  struct SalidaSimulada * _self = self; 
  return _self->duty;
}

void SalidaSimulada_setDuty(void*self ,uint duty){
  struct SalidaSimulada * _self = self;
  _self->duty = duty;
}

void SalidaSimulada_setTipo(void* self,TipoSalida tipo){
  struct SalidaSimulada * _self = self;
  _self->tipoSalida= tipo;
}

TipoSalida SalidaSimulada_getTipo(void*self){
  struct SalidaSimulada * _self = self;
  return _self->tipoSalida;
}
