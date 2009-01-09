#include "Cpu.h"
#include "Timer.h"
#include "LedTest.h"
#include "WDog1.h"
#include "timer_interrupt.h"

void main (void){
  struct Timer *t1=new(&Timer,(ulong)1000); 
  struct Timer t2;
  struct Timer t3;
  struct Timer t4;
  struct Timer t5;
   
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
 
  newAlloced(&t2,&Timer,(ulong)2000);
  newAlloced(&t3,&Timer,(ulong)3000);
  newAlloced(&t4,&Timer,(ulong)5000);
  newAlloced(&t5,&Timer,(ulong)5000);
    
  for(;;){
    WDog1_Clear();
    
    if(t1 && Timer_isfinish(t1)){
      deleteAndNil(&t1);
      set_Led(0);    
    }
    if(Timer_isfinish(&t2))
      set_Led(1); 
    
    if(Timer_isfinish(&t3))
      set_Led(2); 

    if(Timer_isfinish(&t4)){
//      Timer_Restart(&t1);
      Timer_Restart(&t2);
      Timer_Restart(&t3);
      Timer_Restart(&t4);
      Clr_Led(0); 
      Clr_Led(1); 
      Clr_Led(2);  
    }
    
    if(Timer_isfinish(&t5)){
      if(get_Led(3))
        Clr_Led(3);
      else
        set_Led(3);
      Timer_setTime(&t5,Timer_getTime(&t5)*2);
      if(Timer_getTime(&t5)>60000)
        Timer_setTime(&t5,5000);  
    }
     
  }
}