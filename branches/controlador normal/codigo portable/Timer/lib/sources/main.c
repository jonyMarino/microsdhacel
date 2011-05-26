#include "Cpu.h"
#include "Timer.hpp"
#include "LedTest.h"
#include "WDog1.h"
#include "timer_interrupt.h"
#include "BaseTimers_1ms_40ms.hpp"

void main (void){

  Timer::setBaseTimerDefault(*BaseTimers_1ms_40ms::getInstance()); 
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  Timer *t1= new Timer(1000); 
  Timer t2(2000);
  Timer t3(3000);
  Timer t4(5000);
  Timer t5(5000);
    
  for(;;){
    WDog1_Clear();
    
    if(t1 && t1->isFinished()){
      delete t1;
      t1= NULL; 
      set_Led(0);    
    }
    if(t2.isFinished())
      set_Led(1); 
    
    if(t3.isFinished())
      set_Led(2); 

    if(t4.isFinished()){
//      Timer_Restart(&t1);
      t2.restart();
      t3.restart();
      t4.restart();
      Clr_Led(0); 
      Clr_Led(1); 
      Clr_Led(2);  
    }
    
    if(t5.isFinished()){
      if(get_Led(3))
        Clr_Led(3);
      else
        set_Led(3);
      t5.setTime(t5.getTime()*2);
      if(t5.getTime()>60000)
        t5.setTime(5000);  
    }
     
  }
}