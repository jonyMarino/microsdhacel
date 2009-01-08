#include "DecoradorPWM.h"

const struct IPWMClass DecoradorPWM;

int DecoradorPWM_getPeriodo(void * _self){
  return getPeriodo((struct IPWM *)DecoradorSalida_getDecorado(_self));
}

