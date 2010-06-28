#ifndef _PWM_TPM1_H
#define _PWM_TPM1_H
#include "PWM.h"

struct PWMTpm1{
  struct PWM super;
};

extern const struct IPWMClass PWMTpm1;  
					
#endif