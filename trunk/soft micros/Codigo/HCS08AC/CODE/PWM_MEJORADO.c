/** ###################################################################
**     Filename  : PWM_MEJORADO.C
**     Project   : PWM_MEJORADO
**     Processor : MC9S08AC128CLK
**     Version   : Driver 01.11
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 11/12/2008, 9:36
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2008
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/
/* MODULE PWM_MEJORADO */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Salida.h"
#include "PWM_Periodos.h"
#include "PWM.h"
#include "ManejadorMemoria.h"
#include "RamSimulaFlash.h"
#include "PWMTpm1.h"

TConfPWM  prueba;
NEW_RAM_SIMULA_FLASH(flash);

struct ManejadorMemoria *const pFlash = &flash;

void main(void)
{
  /* Write your local variable definition here */
   void * pwm;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
 
  
  pwm = new(&PWMTpm1,&prueba);
  
  PWMTpm1_setPeriodo(pwm,0);
  PWMTpm1_setDuty(pwm,0);
  PWMTpm1_setTipoSalida(pwm,SALIDA_ONOFF);
  

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END PWM_MEJORADO */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 3.03 [04.07]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
