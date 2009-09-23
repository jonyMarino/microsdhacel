#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "IPWM.hpp"
#include "PWMTimer.hpp"
#include "Method.h"
#include "AS1.h"
#include "FC321.h"
#include "RamSimulaFlash.h"
#include "cpu.h"

void testPwm (PWM &pwm);
void onToggle(void * self);
void print(char *msj);
unsigned int potencia=500;
TPeriod period= PWM_100ms;
bool pasoEnable=FALSE;
char j=0;

void main(void) {
  PE_low_level_init();
  
  /* put your own code here */
  struct RamSimulaFlash ram;
  newAlloced(&ram,&RamSimulaFlash);
  TConfPWM conf;
  PWMTimer test(*(struct ManejadorMemoria*)&ram,conf,1);
  
  
  //FC321_Init();
  //AS1_Init();
	EnableInterrupts;
  testPwm (test);	
 

  for(;;) {
    _FEED_COP(); /* feeds the dog */
    
    
    
  } /* loop forever */
  /* please make sure that you never leave main */
}



void testPwm (PWM &pwm){
 struct Method* m=(struct Method*)(_new(&Method,onToggle,NULL));
 
 
 pwm.setPeriodo(period);
 pwm.setPotencia(potencia);
 pwm.setTipoSalida((TipoSalida)SALIDA_PROPORCIONAL);
// pwm.setPotencia(potencia);
 pwm.addOnToggleListener(m);
 print("testing... periodo:100ms'\n'");
 
    
}

void onToggle(void * self){
 bool state;
 word * time;
 state=((IPWM*)self)->getEstadoSalida();
 if(state==TRUE){
  pasoEnable = TRUE;
  FC321_Enable();
 }else if(pasoEnable == TRUE){
   pasoEnable = FALSE; 
   FC321_Reset(); 
   FC321_Disable();
   FC321_GetTimeMS(time);
 }
 
 if((*time==(potencia*period)/1000) && *time!=0){
  j++;
  if(j>10){
    j=0;
    print("test OK '\n'");
 }else
    return;    
}else
  print("test FAIL '\n'");
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
  
