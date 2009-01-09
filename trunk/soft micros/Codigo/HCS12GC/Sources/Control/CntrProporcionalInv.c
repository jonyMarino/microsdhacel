#include "CntrProporcionalInv.h"
#include "stddef.h"

int CntrProporcionalInv_getValorControl(void * _self);

const struct ValorControlClass CntrProporcionalInvClass={
    &Class,
  "",
  &Object,
  sizeof(struct CntrProporcionalInv),
  ValorControl_defConstructor,
  NULL,
    NULL, // differ
  NULL, // puto
  CntrProporcionalInv_getValorControl
};


int CntrProporcionalInv_getValorControl(void * _self){
  int val = ValorControl_getValorControlador(_self);
  int valorSensor = _Getter_getVal( ValorControl_getSensor(_self) );
  
  return valorSensor-val;    
}
