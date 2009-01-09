#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Class.h"
#include "ClassADC.h"
#include "Grabacion.h"
#include "PWMTimer.h"
#include "FlashBkpEnFlash.h"
#include "timer_interrupt.h"


#pragma CONST_SEG PARAMETERS_PAGE
volatile const TConfPWM pwmconf;
#pragma CONST_SEG DEFAULT

struct Timer * timer;
struct PWM * pwm[2];


NEW_FLASH_BKP_EN_FLASH(flash,0x4400);


void on1ms(void  * a){
  if(PromBkp_listoParaGrabarOBorrar(&flash))
       PromBkp_grabarOBorrar(&flash);
  DpyAndSwitch();
}


void main (void){  
//  timer= newObj(Timer,(ulong)500);
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  Teclas_Init();
  Display_Init(); // Inicializacion del display

  PasarASCII("tESt",0);
  
  add1msListener(on1ms,0);
  //add40msListener(on);

  pwm[0]= newObj(PWMTimer,&pwmconf,1);
  pwm[1]= newObj(PWMTimer,&pwmconf,0);
 	Salida_conectar(pwm[0],TRUE);
 	Salida_conectar(pwm[1],TRUE);
 
 	setPeriodo(pwm[0],PWM_1sec);
 	setPeriodo(pwm[1],PWM_1sec);
 	
 	_Salida_OnOff(pwm[0],FALSE);
 	_Salida_OnOff(pwm[1],FALSE);
 	
 	setPotenciaSalida(pwm[0],500);
  setPotenciaSalida(pwm[1],750);
  	
	
													 
  for(;;){
    WDog1_Clear();				

  }
}