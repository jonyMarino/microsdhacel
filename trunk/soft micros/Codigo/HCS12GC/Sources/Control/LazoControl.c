#include "LazoControl_protected.h"

const struct LazoClass LazoControl={
  CLASS_INITIALIZATION(LazoClass,LazoControl,Lazo,LazoControl_defConstructor,Lazo_destructor,Object_differ,Object_puto) ,
  LazoControl_onNuevaMedicion,
  LazoControl_getSensor,
  LazoControl_getSalida
};



void LazoControl_constructor(void * _self, 
                             struct ValorControl * valorControl, 
                             struct AdaptacionSalida * adaptadorSalida)
{
  struct LazoControl * self = (struct LazoControl *)_self;
  Lazo_constructor(_self, ValorControl_getSensor(valorControl));
  self->valorControl= valorControl;
  self->adaptadorSalida = adaptadorSalida;
}

void LazoControl_defConstructor(void * _self,va_list * args){
  LazoControl_constructor(_self,va_arg(*args,struct ValorControl *),va_arg(*args,struct AdaptacionSalida *));  
}


void LazoControl_onNuevaMedicion(void * _self){
  struct LazoControl * self = (struct LazoControl *)_self;
  if( getConectada ( LazoControl_getSalida (self) ) ){
    int valControl = getValorControl( self->valorControl );
    AdaptacionSalida_setPotenciaSalida( self->adaptadorSalida , valControl );
  }
}

struct Sensor * LazoControl_getSensor(void * _self ){
  struct LazoControl * self = (struct LazoControl *)_self;
  return ValorControl_getSensor(self->valorControl);
}

struct ISalida * LazoControl_getSalida(void * _self ){
  struct LazoControl * self = (struct LazoControl *)_self;
  return AdaptacionSalida_getSalida( self->adaptadorSalida );
}

/* TipoSalida */
TipoSalida LazoControl_getTipoSalida(void * _self){
  struct LazoControl * self = (struct LazoControl *)_self;
  return getTipoSalidaAdaptador(self->adaptadorSalida);    
}

byte LazoControl_setTipoSalida(void * _self,TipoSalida tipoSalida){
  struct LazoControl * self = (struct LazoControl *)_self;
  return setTipoSalidaAdaptador(self->adaptadorSalida,tipoSalida);
}

