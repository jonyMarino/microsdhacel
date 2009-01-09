#include "Cpu.h"
#include "Timer.h"
#include "FTimer.h"
#include "display.h"
#include "WDog1.h"

  struct FTimer t2;
  struct Timer t3;
  struct FTimer *t4;
  
void acc1(void){
   PasarASCII("Ft2 ",1);
   Timer_Destruct(&t2);  
}

void acc2(void){
  PasarASCII("Ft4",1);
  Timer_Destruct(t4); 
}



void main (void){
  struct Timer *t1=newObj(Timer,(ulong)1000); 
  t4=newObj(FTimer,(ulong)3000,acc2);
   
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  
  Display_Init();

  newAllocObj(&t2,FTimer,(ulong)1000,acc1);
  newAllocObj(&t3,Timer,(ulong)3000);
  
    
  for(;;){
    WDog1_Clear();
    
    if(t1 && Timer_isfinish(t1)){
      PasarASCII("t1  ",0);
      deleteObj(&t1);    
    }
    
    if(Timer_isfinish(&t3)){
      PasarASCII("t3  ",0);
      Timer_Destruct(&t3);    
    }

 /*   if(Timer_isfinish(&t4)){
//      Timer_Restart(&t1);
      Timer_Restart(&t2);
      Timer_Restart(&t3);
      Timer_Restart(&t4); 
    }
    
    if(Timer_isfinish(&t5)){
      Timer_setTime(&t5,Timer_getTime(&t5)*2);
      if(Timer_getTime(&t5)>60000)
        Timer_setTime(&t5,5000);  
    }
*/     
  }
}