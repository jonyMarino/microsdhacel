#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Object.h"
#include "Grabacion.h"
#include "PWMTimer.h"
#include "FlashBkpEnFlash.h"
#include "timer_interrupt.h"
#include "PWMSoft.h"

#pragma CONST_SEG PARAMETERS_PAGE
volatile const TConfPWM pwmconf[3];
#pragma CONST_SEG DEFAULT

struct Timer * timer;
struct PWM * pwm[3];


NEW_FLASH_BKP_EN_FLASH(flash,0x4400);


void on1ms(void  * a){
  IncTimers(1);
  if(PromBkp_listoParaGrabarOBorrar(&flash))
       PromBkp_grabarOBorrar(&flash);
  
}


void setearPWM(struct PWM * pwm){
   	setConectada(pwm,TRUE);
   	setPeriodo(pwm,PWM_100ms);
   	setTipoSalida(pwm,SALIDA_PROPORCIONAL);
   	setPotenciaSalida(pwm,0);
}

void main (void){  
  bool inc =TRUE;
  timer= new(&Timer,(ulong)100);
  
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  Teclas_Init();
  Display_Init(); // Inicializacion del display

  add1msListener(on1ms,0);
  //add40msListener(on);

  
  pwm[1]= new(&PWMSoft,&pwmconf[1],&PTT,1);
  setearPWM(pwm[1]);
														 
  for(;;){
    WDog1_Clear();				
    if(Timer_isfinish(timer)){
      Timer_Restart(timer);
      if(inc){
        
        setPotenciaSalida(pwm[1],getPotencia(pwm[1])+1);
        if(getPotencia(pwm[1])==1000)
          inc=FALSE;
      }else{                  
        setPotenciaSalida(pwm[1],getPotencia(pwm[1])-1);
        if(getPotencia(pwm[1])==0)
          inc=TRUE;    
      }
    }
  }
}