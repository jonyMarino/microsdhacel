#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Object.h"
#include "Grabacion.h"
#include "PWMTimer.h"
#include "FlashBkpEnFlash.h"
#include "timer_interrupt.h"
#include "PWMHard01.h"
#include "PWMHard23.h"
#include "PWMManager01_45.h"

#pragma CONST_SEG PARAMETERS_PAGE
volatile const TConfPWM pwmconf[3];
#pragma CONST_SEG DEFAULT

struct Timer * timer;
struct PWM * pwm[3];


NEW_FLASH_BKP_EN_FLASH(flash,0x4400);


void on1ms(void  * a){
  if(PromBkp_listoParaGrabarOBorrar(&flash))
       PromBkp_grabarOBorrar(&flash);
  
}


void setearPWM(struct PWM * pwm){
   	setConectada(pwm,TRUE);
   	setPeriodo(pwm,PWM_100ms);  
   	setTipoSalida(pwm,SALIDA_PROPORCIONAL);
   	setPotenciaSalida(pwm,500);
}

void main (void){  
//  timer= newObj(Timer,(ulong)500);
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  Teclas_Init();
  Display_Init(); // Inicializacion del display

  add1msListener(on1ms,0);
  //add40msListener(on);

  
  pwm[1]= new(&PWMHard01,&pwmconf[1]);
  setearPWM(pwm[1]);
 // pwm[0]= PWMManager01_45_get01(&pwmconf[0]);// newObj(PWMHard01Depend45,&pwmconf[0]);
//  pwm[2]= PWMManager01_45_get45(&pwmconf[2]);  														 
  for(;;){
    WDog1_Clear();				

  }
}