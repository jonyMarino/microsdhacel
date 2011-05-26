#include "Cpu.h"
//#include "Timer.hpp"
//#include "LedTest.h"
#include "WDog1.h"
//#include "timer_interrupt.h"

void main (void){

   
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
 for(;;){
  WDog1_Clear();
 }
}