#ifndef _PWM_TPM3_H
#define _PWM_TPM3_H
#include "PWM.h"

struct PWMTpm3{
  struct PWM super;
};

extern const struct IPWMClass PWMTpm3;  
					
#endif