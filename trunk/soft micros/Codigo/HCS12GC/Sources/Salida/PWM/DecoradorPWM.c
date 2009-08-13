#include "DecoradorPWM.h"

const struct IPWMClass DecoradorPWM={
  IPWM_CLASS_INITIALIZATION(IPWMClass,
                            DecoradorPWM,
                            IPWM,
                            Object_ctor,
                            NULL,
                            NULL,
                            NULL,
                            Salida_getPotencia,
                            Salida_setPotencia,
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            NULL)  
};

int DecoradorPWM_getPeriodo(void * _self){
  return getPeriodo((struct IPWM *)DecoradorSalida_getDecorado(_self));
}

