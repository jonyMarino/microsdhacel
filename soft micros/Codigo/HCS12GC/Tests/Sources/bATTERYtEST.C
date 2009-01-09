/*
PROGRAMA DE TEST PARA BATERIA
*/

#include "Cpu.h"
#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "Object.h"
#include "RTI.h"
#include "bits2ULN.h"
#include "bits5ULN.h"
#include "Display1.h"
#include "timer_interrupt.h"

#define TEST1


void battery_on1ms(void * a){
  IncTimers(1);
  DpyAndSwitch();
}

#ifdef TEST1
void main (void){
  struct Timer * t1=new(&Timer,(ulong)1000); 
  static int registro=0;
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/

  Display_Init(); // Inicializacion del display
  add1msListener(battery_on1ms,NULL);
  PutValLed(1,2);  
  RTI_Init();
  
  while(t1){
    WDog1_Clear();
    if(Timer_isfinish(t1)){
  //    PasarASCII("Ok88",0); //texto fijo
      deleteAndNil(&t1);
    }
  }
  
    RTI_Enable();
    do{
      Cpu_SetStopMode();
      registro++;
    }while(registro<20);
    
    RTI_Disable();
    PLLCTL = 116;
    while(!CRGFLG_LOCK) {};              /* Wait */
    CLKSEL_PLLSEL = 1;                   /* Select clock source from PLL */

  
  for(;;){
    static unsigned long a=0;
    
    a++;
    
    if(a==-1)
      while(1); 
  
  }
}

#else

void main(void){
  struct Timer * t1=new(&Timer,(ulong)1000); 
  static unsigned int registro=0;
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
 
 Display_Init(); // Inicializacion del display
 add1msListener(battery_on1ms,NULL);
 RTI_Init();
 
 PutValLed(1,2); 
 
 while(t1){
  WDog1_Clear();
  if(Timer_isfinish(t1)){
//    PasarASCII("Ok88",0); //texto fijo
    deleteAndNil(&t1);
  }
 }
  
  Display1_PutVal(0);	  //PTA
  bits2ULN_PutVal(0);		// PTJ
	bits5ULN_PutVal(0); 	 //PTM

 RTI_Enable();
    
  do{
    Cpu_SetStopMode();
    registro++;
  }while(registro<65535);
  RTI_Disable();
  
  for(;;);
}

#endif