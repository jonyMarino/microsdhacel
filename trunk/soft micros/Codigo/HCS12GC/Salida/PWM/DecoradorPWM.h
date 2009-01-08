#ifndef _DECORADORPWM_H
#define _DECORADORPWM_H


#include "DecoradorSalida.h"
#include "IPWM.h"

struct DecoradorPWM { //: public DecoradorSalida, public IPWM {
  struct  DecoradorSalida super;

};

extern const struct IPWMClass DecoradorPWM;

int DecoradorPWM_getPeriodo(void * _self);

#endif
