#ifndef _PWM_SOFT_H
#define _PWM_SOFT_H

#include "PWM.h"
#include "MethodTimer.h"


struct PWMSoft{
  struct PWM super;
  struct MethodTimer timer;
  byte * salida;
  byte mask;
};

extern const struct IPWMClass PWMSoft;  
					
#endif