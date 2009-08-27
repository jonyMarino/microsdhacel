#ifndef _PWMPERIODOEVENT_H
#define _PWMPERIODOEVENT_H


#include "DecoradorPWM.h"
#include "MethodContainer.h"

/**
 * PWM con evento al cambiar el periodo.
 */
struct  PWMPeriodoEvent {//: public DecoradorPWM {
  struct DecoradorPWM super;
//%-
  struct MethodContainer listeners;

};

extern const struct IPWMClass PWMPeriodoEvent;

void PWMPeriodoEvent_addPeriodoListener(void * _self,struct Method * metodo);
void PWMPeriodoEvent_deletePeriodoListener(void * _self,struct Method * metodo);


#endif
