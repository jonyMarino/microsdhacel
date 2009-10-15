#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "IPWM.hpp"
#include "PWMHard.hpp"
#include "PWMHard23.hpp"
#include "PWMManager01_45.hpp"
#include "Method.h"
#include "AS1.h"
#include "RamSimulaFlash.h"
#include "cpu.h"

void testPwmHard45 (PWMHard &pwm);
void testPwmHard01 (PWMHard &pwm);
void print (char *msj);
unsigned int potencia=700;
unsigned int potencia1=500;

void main(void) {
  /* put your own code here */
  PE_low_level_init();
  struct RamSimulaFlash ram;
  struct RamSimulaFlash ram1;
  newAlloced(&ram,&RamSimulaFlash);
  newAlloced(&ram1,&RamSimulaFlash);
  TConfPWM conf;
  TConfPWM conf1;
  PWMManager01_45::PWMHard01 test(*(struct ManejadorMemoria*)&ram,conf);
  PWMHard23 test1(*(struct ManejadorMemoria*)&ram1,conf1);
  //testPwmHard01 (test);
  testPwmHard45 (test1);	
 

	EnableInterrupts;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */

}

void testPwmHard01 (PWMHard &pwm){

// pwm.setConectada(TRUE);
 pwm.setPeriodo(PWM_200ms);
 pwm.setTipoSalida((TipoSalida)SALIDA_PROPORCIONAL);
 pwm.setPotencia(potencia);
 print("testing... periodo:200ms'\n'");
     
}


void testPwmHard45 (PWMHard &pwm){

// pwm.setConectada(TRUE);
 pwm.setPeriodo(PWM_100ms);
 pwm.setTipoSalida((TipoSalida)SALIDA_PROPORCIONAL);
 pwm.setPotencia(potencia1);
 print("testing... periodo:100ms'\n'");
     
}

void print (char *msj){
  char i;
  bool f=FALSE;  
  AS1_Enable();
  for(i=0;msj[i]!='\0';){
    while (!(SCISR1 & 0x80));  /* wait for output buffer empty */
    if(msj[i] == '\n'){
      SCIDRL = 0x0a;
      while (!(SCISR1 & 0x80));
      SCIDRL = 0xd;
      i++;
    }else{
      SCIDRL = msj[i];
      i++;
    }
    
  }
  AS1_Disable();
}