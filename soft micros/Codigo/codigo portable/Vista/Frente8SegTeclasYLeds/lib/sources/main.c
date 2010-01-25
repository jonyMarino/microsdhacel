#include "Cpu.h"
#include "Timer.hpp"
#include "WDog1.h"
#include "timer_interrupt.h"
#include "FrenteDH.hpp"
#include "BaseTimers_1ms_40ms.hpp"


void main (void){
  
  Timer::setBaseTimerDefault(*BaseTimers_1ms_40ms::getInstance()); 
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  byte leds =0;
  FrenteDH::getInstancia()->getDisplay(0)->write("nico");
  //FrenteDH::getInstancia()->getDisplay(1)->write("t   ");
  //FrenteDH::getInstancia()->setLed(1,0);
  //FrenteDH::getInstancia()->setLed(1,2);
  for(;;){
    WDog1_Clear();
    /*byte tecla = FrenteDH::getInstancia()->getTecla();
    if(tecla){      
      if(tecla=='u')
        leds++;
      else if(tecla=='d')
        leds--;

      FrenteDH::getInstancia()->setLed((leds%4)==0,0);
      FrenteDH::getInstancia()->setLed((leds%4)==1,1);
      FrenteDH::getInstancia()->setLed((leds%4)==2,2);
      FrenteDH::getInstancia()->setLed((leds%4)==3,3);
    } */
    
  }
}