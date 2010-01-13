#include "BaseTimers_1ms_40ms.hpp"
#include "timer_interrupt.h"
#include "TI1.h"



BaseTimers_1ms_40ms* BaseTimers_1ms_40ms::instance=NULL;



BaseTimers_1ms_40ms::BaseTimers_1ms_40ms(){
  on1ms.pmethod= inc1;
  on1ms.obj=this;
  on40ms.pmethod= inc40;
  on40ms.obj=this;
  add1msListener(&on1ms);
  add40msListener(&on40ms);
}

BaseTimers_1ms_40ms *BaseTimers_1ms_40ms::getInstance(void){
  if(!instance)
    instance = new BaseTimers_1ms_40ms();
  return instance;
}

void BaseTimers_1ms_40ms::lockInc(){
  TI1_Disable();
}

void BaseTimers_1ms_40ms::unlockInc(){
  TI1_Enable();
}

void BaseTimers_1ms_40ms::inc1(void * _self){
  BaseTimers_1ms_40ms * self=(BaseTimers_1ms_40ms *)_self;
  self->incrementar(1);
  self->actualizarTimers();
}

void BaseTimers_1ms_40ms::inc40(void * _self){
  BaseTimers_1ms_40ms * self=(BaseTimers_1ms_40ms *)_self;
  self->incrementar(TIEMPO_GRABACION);
  self->actualizarTimers();
}


