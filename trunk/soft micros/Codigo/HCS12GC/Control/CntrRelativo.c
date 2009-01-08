#include "CntrRelativo.h"
#include "stddef.h"

void CntrRelativo_defConstructor(void * _self,va_list * args);
int CntrRelativo_getValorControl(void * _self);

const struct ValorControlClass CntrRelativoClass={
    &Class,
  "",
  &Object,
  sizeof(struct CntrRelativo),
  CntrRelativo_defConstructor,
  NULL,
    NULL, // differ
  NULL, // puto
  CntrRelativo_getValorControl
};


void CntrRelativo_constructor(void * _self,struct ValorControlConf * configuracion, struct Sensor * sensor,struct getter * valorControl2){
  struct CntrRelativo * self = _self;  
  ValorControl_constructor(_self,configuracion,sensor);
  self->valControl2 = valorControl2;
}

void CntrRelativo_defConstructor(void * _self,va_list * args){
  CntrRelativo_constructor(_self,va_arg(*args,void*),va_arg(*args,void*),va_arg(*args,void*));  
}


int CntrRelativo_getValorControl(void * _self){
  struct CntrRelativo * self = _self;
  int valControl1 = ValorControl_getValorControlador(_self);
  int valControl2 = _Getter_getVal(self->valControl2);
  int valorSensor = _Getter_getVal( ValorControl_getSensor(_self) );
  
  return valorSensor - (valControl1+ valControl2);    
}
