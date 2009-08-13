#include "AdaptacionSalida.h"

const struct Class AdaptacionSalidaClass={
    CLASS_INITIALIZATION(Class,AdaptacionSalidaClass,Class,AdaptacionSalida_defConstructor,Object_dtor,Object_differ,Object_puto)

};


void AdaptacionSalida_constructor(void* _self,struct AdaptSalidaConf *configuracion,struct ISalida * salida){
  struct AdaptacionSalida * self = (struct AdaptacionSalida *)_self;
  self->configuracion = configuracion;
  self->salida = salida;
  setTipoSalida(self->salida,configuracion->tipoSalida);
}


void AdaptacionSalida_defConstructor(void * _self,va_list * args){
  AdaptacionSalida_constructor(_self,va_arg(*args,struct AdaptSalidaConf *),va_arg(*args,struct ISalida *));  
}

int calcularPotencia(void * _self,int valorDeControl){
  struct AdaptacionSalidaClass ** vTable = (struct AdaptacionSalidaClass **)_self;
  
  return (**vTable).calcularPotencia(_self,valorDeControl);
}


void AdaptacionSalida_setPotenciaSalida(void* _self,int valorDeControl){
  struct AdaptacionSalida * self = (struct AdaptacionSalida *)_self;
  int duty = calcularPotencia(_self,valorDeControl);
  
  setPotenciaSalida(self->salida,duty);  
}


int getHisteresis(void * _self){
   return AdaptacionSalida_getHisteresis(_self);
}
byte setHisteresis(void * _self, int histeresis){
  return AdaptacionSalida_setHisteresis(_self,histeresis);
}

/**/
TipoSalida getTipoSalidaAdaptador(void * _self){
  struct AdaptacionSalidaClass ** vTable = (struct AdaptacionSalidaClass **)_self;
  
  return (**vTable).getTipoSalidaAdaptador(_self);  
}
/**/
byte setTipoSalidaAdaptador(void * _self, TipoSalida tipoSalida){
  struct AdaptacionSalidaClass ** vTable = (struct AdaptacionSalidaClass **)_self;
  
  return (**vTable).setTipoSalidaAdaptador(_self,tipoSalida);
}

/**/
TipoSalida AdaptacionSalida_getTipoSalidaAdaptador(void * _self){
  struct AdaptacionSalida * self = (struct AdaptacionSalida *)_self;
  return AdaptSalidaConf_getTipoSalida(self->configuracion);  
}
/**/
byte AdaptacionSalida_setTipoSalidaAdaptador(void * _self, TipoSalida tipoSalida){
  struct AdaptacionSalida * self = (struct AdaptacionSalida *) _self;
  setTipoSalida(self->salida,tipoSalida);
  return AdaptSalidaConf_setTipoSalida(self->configuracion,tipoSalida); 
}
