#include "CntrProporcional.h"
#include "stddef.h"

int CntrProporcional_getValorControl(void * _self);

const struct ValorControlClass CntrProporcionalClass={
    &Class,
  "",
  &Object,
  sizeof(struct CntrProporcional),
  ValorControl_defConstructor,
  NULL,
    NULL, // differ
  NULL, // puto
  CntrProporcional_getValorControl
};


int CntrProporcional_getValorControl(void * _self){
  int val = ValorControl_getValorControlador(_self);
  int valorSensor = _Getter_getVal( ValorControl_getSensor(_self) );
  
  return val - valorSensor;    
}
