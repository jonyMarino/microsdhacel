#include <stdlib.h>

#include "CntrBanda.h"
#include "stddef.h"

#pragma DATA_SEG CNTR_BANDA_DATA                                            
#pragma CODE_SEG CNTR_BANDA_CODE 
#pragma CONST_SEG DEFAULT

void CntrBanda_defConstructor(void * _self,va_list * args);
int CntrBanda_getValorControl(void * _self);

const struct ValorControlClass CntrBanda={
  CLASS_INITIALIZATION(Class,CntrBanda,Object,CntrBanda_defConstructor,Object_dtor,Object_differ,Object_puto),
  CntrBanda_getValorControl
};


void CntrBanda_constructor(void * _self,struct ValorControlConf * configuracion, struct Sensor * sensor,struct Getter * valorControl2){
  struct CntrBanda * self = (struct CntrBanda *)_self;  
  ValorControl_constructor(_self,configuracion,sensor);
  self->valControl2 = valorControl2;
}

void CntrBanda_defConstructor(void * _self,va_list * args){
  CntrBanda_constructor(_self,va_arg(*args,struct ValorControlConf *),va_arg(*args,struct Sensor *),va_arg(*args,struct Getter *));  
}


int CntrBanda_getValorControl(void * _self){
  struct CntrBanda * self = (struct CntrBanda *)_self;
  int valControl1 = ValorControl_getValorControlador(_self);
  int valControl2 = _Getter_getVal(self->valControl2);
  int valorSensor = _Getter_getVal( ValorControl_getSensor(_self) );
  
  return abs(valorSensor-valControl2)-(valControl1/2);   
}
