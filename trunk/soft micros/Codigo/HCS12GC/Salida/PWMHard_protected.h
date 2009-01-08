#ifndef _PWM_HARD_PROTECTED_H
#define _PWM_HARD_PROTECTED_H

#include "Salida_protected.h"
#include "stdtypes.h"
#include "IO_Map.h"
 
typedef enum{			 //No cambiar el orden!
  RefPWM01,
  RefPWM23,
  RefPWM45
}ReferenciaPWM;

/**
**  @fn void PWMHard_setDuty(PWMReference,uint);
*/
void PWMHard_setDuty(ReferenciaPWM,uint);

/**
**  
*/
#define CONTROLADOR_PWM_INIT(PWM1,PWM2){\
  PWMCTL_CON##PWM1##PWM2 = 1; /*Concatenar  PWM1 y PWM2*/\
  PWMPOL_PPOL##PWM2 = 1; /*sin duty se queda en 0*/\
  PWME_PWME##PWM2 = 0;   /* Stop counter */				\
  PWMCNT##PWM1##PWM2 = 0;																\
}


#define PWMHard_setPeriodo(refPWM,periodo)  \
  (&PWMPER01)[refPWM]=periodo

#define PWMHard_noEscalar(pwm)  \
  PWMCLK&=~(1<<(pwm*2))  

#define PWMHard_escalar(pwm)  \
  PWMCLK|=(1<<(pwm*2))
  

#endif