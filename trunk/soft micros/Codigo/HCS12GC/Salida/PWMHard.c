#include "PWMHard_protected.h"


void PWMHard_setDuty(ReferenciaPWM pwm,uint duty){
    uint periodo = (&PWMPER01)[pwm];
    uint * pwm_duty =  &(&PWMDTY01)[pwm];
    *pwm_duty = (periodo * (dword)duty + 500) / 1000;
   /* asm {														 
      LDY    periodo				 
      LDD    duty										 
      EMUL													 
      ADDD   #500										 
      EXG    D,Y										 
      ADCB   #0											 
      ADCA   #0											 
      LDX    #1000									 
      EXG    D,Y										 
      EDIV													 
      STY    pwm_duty				
    }
    */  
}


void PWMHard_setPrescaler(ReferenciaPWM pwm,byte valor){
  if(pwm == RefPWM23)
    PWMPRCLK_PCKB = valor;
  else
    PWMPRCLK_PCKA = valor;
}