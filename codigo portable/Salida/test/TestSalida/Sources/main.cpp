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
TPeriod period=PWM_100ms;
char j=0;
char flag;
bool paso=FALSE;
void main(void) {
  PE_low_level_init();
  
  /* put your own code here */
  struct RamSimulaFlash ram;
  newAlloced(&ram,&RamSimulaFlash);
  TConfPWM conf;
  PWMTimer test(*(struct ManejadorMemoria*)&ram,conf,1);
  
  
  //FC321_Init();
  //AS1_Init();
//	EnableInterrupts;
  testPwm (test);	
 

  for(;;) {
    _FEED_COP(); /* feeds the dog */
    
    
    
  } /* loop forever */
  /* please make sure that you never leave main */
}



void testPwm (PWM &pwm){
 struct Method* m=(struct Method*)(_new(&Method,onToggle,&pwm));
 //pwm.setConectada(TRUE);
 pwm.setPeriodo(PWM_100ms);
 pwm.setTipoSalida((TipoSalida)SALIDA_PROPORCIONAL);
 pwm.setPotencia(potencia);
 pwm.addOnToggleListener(m);
// EnableInterrupts;
 print("testing... periodo:100ms'\n'");
 
    
}

void onToggle(void * self){
 bool state;
 word  time;            
//return; 
 
 state=((IPWM*)self)->getEstadoSalida();
 if(state==TRUE && paso==FALSE){
  flag=1;
  paso=TRUE;
  FC321_Enable();
  return;
 }else if(flag == 1){
   //flag=2;
   //paso=~paso;
   
   FC321_GetTimeMS(&time);
   FC321_Reset();
    
 }
 
 if((time==(potencia*100)/1000) && time!=0){
  j++;
  if(j>10){
    j=0;
    print("test OK '\n'");
 }else
    return;    
}else //if(flag=2){
  print("test FAIL '\n'");
  //DisableInterrupts;
  //setReg8Bits(TSCR1,0);
//}
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
  
