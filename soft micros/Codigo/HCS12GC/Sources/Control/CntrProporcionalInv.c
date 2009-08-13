#include "CntrProporcionalInv.h"
#include "stddef.h"

int CntrProporcionalInv_getValorControl(void * _self);

const struct ValorControlClass CntrProporcionalInv={
  CLASS_INITIALIZATION(Class,CntrProporcionalInv,Object,ValorControl_defConstructor,Object_dtor,Object_differ,Object_puto),
  CntrProporcionalInv_getValorControl
};


int CntrProporcionalInv_getValorControl(void * _self){
  int val = ValorControl_getValorControlador(_self);
  int valorSensor = _Getter_getVal( ValorControl_getSensor(_self) );
  
  return valorSensor-val;    
}
