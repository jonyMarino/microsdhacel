#ifndef _PWM_TPM2_H
#define _PWM_TPM2_H
#include "PWM.h"

struct PWMTpm2{
  struct PWM super;
};

extern const struct IPWMClass PWMTpm2;  
					
#endif