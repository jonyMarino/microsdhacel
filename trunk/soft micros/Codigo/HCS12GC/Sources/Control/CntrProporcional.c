#include "CntrProporcional.h"
#include "stddef.h"

int CntrProporcional_getValorControl(void * _self);

const struct ValorControlClass CntrProporcional={
  CLASS_INITIALIZATION(Class,CntrProporcional,Object,ValorControl_defConstructor,Object_dtor,Object_differ,Object_puto),
  CntrProporcional_getValorControl
};


int CntrProporcional_getValorControl(void * _self){
  int val = ValorControl_getValorControlador(_self);
  int valorSensor = _Getter_getVal( ValorControl_getSensor(_self) );
  
  return val - valorSensor;    
}
