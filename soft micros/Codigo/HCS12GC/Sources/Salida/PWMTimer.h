#ifndef _PWM_TIMER_H
#define _PWM_TIMER_H 

#include "PWM.h"

struct PWMTimer{
  struct PWM _base;
  uchar  PinNum; 						// Pin de Salida
  ulong  ticksPeriodo;
  ulong  ticksDuty;
  ulong  ticksDutyFree;
};

extern const struct IPWMClass PWMTimer;

#endif