#include <stdlib.h>

#include "CntrBanda.h"
#include "stddef.h"

#pragma DATA_SEG CNTR_BANDA_DATA                                            
#pragma CODE_SEG CNTR_BANDA_CODE 
#pragma CONST_SEG DEFAULT

void CntrBanda_defConstructor(void * _self,va_list * args);
int CntrBanda_getValorControl(void * _self);

const struct ValorControlClass CntrBandaClass={
    &Class,
  "",
  &Object,
  sizeof(struct CntrBanda),
  CntrBanda_defConstructor,
  NULL,
  NULL, // differ
  NULL, // puto
  CntrBanda_getValorControl
};


void CntrBanda_constructor(void * _self,struct ValorControlConf * configuracion, struct Sensor * sensor,struct getter * valorControl2){
  struct CntrBanda * self = _self;  
  ValorControl_constructor(_self,configuracion,sensor);
  self->valControl2 = valorControl2;
}

void CntrBanda_defConstructor(void * _self,va_list * args){
  CntrBanda_constructor(_self,va_arg(*args,void*),va_arg(*args,void*),va_arg(*args,void*));  
}


int CntrBanda_getValorControl(void * _self){
  struct CntrBanda * self = _self;
  int valControl1 = ValorControl_getValorControlador(_self);
  int valControl2 = _Getter_getVal(self->valControl2);
  int valorSensor = _Getter_getVal( ValorControl_getSensor(_self) );
  
  return abs(valorSensor-valControl2)-(valControl1/2);   
}
