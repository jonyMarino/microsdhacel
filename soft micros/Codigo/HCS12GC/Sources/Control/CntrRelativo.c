#include "CntrRelativo.h"
#include "stddef.h"

void CntrRelativo_defConstructor(void * _self,va_list * args);
int CntrRelativo_getValorControl(void * _self);

const struct ValorControlClass CntrRelativo={
  CLASS_INITIALIZATION(Class,CntrRelativo,Object,CntrRelativo_defConstructor,Object_dtor,Object_differ,Object_puto),
  CntrRelativo_getValorControl
};


void CntrRelativo_constructor(void * _self,struct ValorControlConf * configuracion, struct Sensor * sensor,struct Getter * valorControl2){
  struct CntrRelativo * self = (struct CntrRelativo *)_self;  
  ValorControl_constructor(_self,configuracion,sensor);
  self->valControl2 = valorControl2;
}

void CntrRelativo_defConstructor(void * _self,va_list * args){
  CntrRelativo_constructor(_self,va_arg(*args,struct ValorControlConf *),va_arg(*args,struct Sensor *),va_arg(*args,struct Getter *));  
}


int CntrRelativo_getValorControl(void * _self){
  struct CntrRelativo * self = (struct CntrRelativo *)_self;
  int valControl1 = ValorControl_getValorControlador(_self);
  int valControl2 = _Getter_getVal(self->valControl2);
  int valorSensor = _Getter_getVal( ValorControl_getSensor(_self) );
  
  return valorSensor - (valControl1+ valControl2);    
}
