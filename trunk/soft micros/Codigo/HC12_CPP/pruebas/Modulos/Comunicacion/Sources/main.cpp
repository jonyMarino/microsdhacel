#include <hidef.h>      /* common defines and macros */
#include <assert.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "timer_interrupt.h"
#include "Termometro.hpp"
#include "OutputStream.hpp"
#include "Cpu.h"
#include "WDog1.h"
#include "Timer/Timer.hpp"
#include "Timer/interrup_1ms_40ms/BaseTimers_1ms_40ms.hpp"
#include "Memoria/Prom/Flash/FlashBkpMitad/FlashBkpMitad.hpp"
#include "PropNumLFPF.hpp"
#include "modbus.hpp"


#pragma CONST_SEG DEFAULT


//FlashBkpMitad flash((void*)0x4200);

class ConfModBus: public ConfiguracionModBus{
  public:
    virtual int getId(){
      return 1;
    }
}confModBus;

PlataformaEmbedded plataforma; 

class Init{
  public:
  Init(){  
    Timer::setBaseTimerDefault(*BaseTimers_1ms_40ms::getInstance());
  }
}ini;


 


int objetoInt;
int get(void * obj){
  assert(obj==&objetoInt);
  return objetoInt;
}

void set(void * obj,int val){
  assert(obj==&objetoInt);
  objetoInt=val;
}

const struct ConstructorPropNumLFPF cPropiedad={
    &propNumLFPFFactory,get,"test",set,-9999,9999,0
};

const void * costructores[] = {
  &cPropiedad
};

const NEW_ARRAY( arrayConstructores,costructores) ;

const GetsProps getProps={
  &arrayConstructores,
  TRUE
};

NodoICModBus nodo((void*)1000,getProps,&objetoInt);

const void* nodos[]={
  &nodo
};

const NEW_ARRAY(comProps,nodos);

ModBus modbus(confModBus,&comProps);

void main(void) {
  PE_low_level_init();
  
  for(;;){    
    plataforma.mainLoop();
    
  }
    
  
  /* please make sure that you never leave main */
}
 