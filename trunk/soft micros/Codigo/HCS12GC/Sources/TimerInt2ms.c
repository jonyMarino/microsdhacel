#include "TimerInt2ms.h"
#include "timer_interrupt_2ms.h"
#include "ManejadorInterrupcion.h"

struct TimerInt2ms{
  struct ManejadorInterrupcion super;  
};

void TimerInt2ms_enable(void * _self);
void TimerInt2ms_disable(void * _self);

const struct ManejadorInterrupcionClass TimerInt2ms={
  CLASS_INITIALIZATION(ManejadorInterrupcionClass,
                       TimerInt2ms,
                       ManejadorInterrupcion,
                       ManejadorInterrupcion_defConstructor,
                       Object_dtor,
                       Object_differ,
                       Object_puto),
                       TimerInt2ms_enable,
                       TimerInt2ms_disable  
};

static void * instance=NULL;
static struct TimerInt2ms allocedInstance;

void * TimerInt2ms_getInstance(void){
  if(!instance){
    instance = &allocedInstance;
    newAlloced(&allocedInstance,&TimerInt2ms);
  }
  return instance;
}

void TimerInt2ms_enable(void * _self){
  timer_interrupt_2ms_Enable();  
}

void TimerInt2ms_disable(void * _self){
  timer_interrupt_2ms_Disable();  
}

void TimerInt2ms_OnInterrupt(void){
  onInterrupt(instance);
}