#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Class.h"
#include "ClassADC.h"
#include "Grabacion.h"
#include "PWMTimer.h"
#include "RamSimulaFlash.h"
#include "timer_interrupt.h"


#pragma CONST_SEG PARAMETERS_PAGE
volatile const TConfPWM pwmconf;
#pragma CONST_SEG DEFAULT

struct Timer * timer;
struct PWM * pwm[2];


NEW_RAM_SIMULA_FLASH(flash);


void on1ms(void  * a){
  if(PromBkp_listoParaGrabarOBorrar(&flash))
       PromBkp_grabarOBorrar(&flash);
  DpyAndSwitch();
}


void main (void){  
//  timer= newObj(Timer,(ulong)500);
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  struct Method * m = _new(&Method,on1ms,0);
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  Teclas_Init();
  Display_Init(); // Inicializacion del display

  PasarASCII("tESt",0);
  
  add1msListener(m);
  //add40msListener(on);

  pwm[0]= _new(&PWMTimer,&pwmconf,1);
  pwm[1]= _new(&PWMTimer,&pwmconf,0);
 	setConectada(pwm[0],TRUE);
 	setConectada(pwm[1],TRUE);
 
 	setPeriodo(pwm[0],PWM_1sec);
 	setPeriodo(pwm[1],PWM_1sec);
 	
 	setTipoSalida(pwm[0],FALSE);
 	setTipoSalida(pwm[1],FALSE);
 	
 	setPotenciaSalida(pwm[0],500);
  setPotenciaSalida(pwm[1],750);
  	
	
													 
  for(;;){
    WDog1_Clear();				

  }
}