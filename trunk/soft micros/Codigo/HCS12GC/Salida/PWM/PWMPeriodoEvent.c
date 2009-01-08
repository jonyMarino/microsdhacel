
#include "PWMPeriodoEvent.h"
void PWMPeriodoEvent_defConstructor(void * _self,va_list * args);
byte PWMPeriodoEvent_setPeriodo(void * _self,int periodo);

const struct IPWMClass PWMPeriodoEvent={
    IPWM_CLASS_INITIALIZATION(IPWMClass,
                            PWMPeriodoEvent,
                            DecoradorPWM,
                            PWMPeriodoEvent_defConstructor,
                            NULL,
                            NULL,
                            NULL,
                            DecoradorSalida_getPotencia,
                            DecoradorSalida_setPotencia,
                            DecoradorSalida_getTipoSalida,
                            DecoradorSalida_setTipoSalida,
                            DecoradorSalida_getConectada,
                            DecoradorSalida_setConectada,
                            DecoradorPWM_getPeriodo,
                            PWMPeriodoEvent_setPeriodo)				
};

void PWMPeriodoEvent_constructor(void*_self,struct IPWM * decorado){
  struct PWMPeriodoEvent * self = _self;
  DecoradorSalida_constructor(_self,decorado);
  newAlloced(&self->listeners,&MethodContainer);    
}

void PWMPeriodoEvent_defConstructor(void * _self,va_list * args){
  PWMPeriodoEvent_constructor(_self,va_arg(*args,struct IPWM *));  
}

void PWMPeriodoEvent_addPeriodoListener(void * _self,struct Method * metodo){
  struct PWMPeriodoEvent * self = _self;
  MethodContainer_add( &self->listeners , metodo);
}

void PWMPeriodoEvent_deletePeriodoListener(void * _self,struct Method * metodo){
  struct PWMPeriodoEvent * self = _self;
  MethodContainer_delete( &self->listeners , metodo);
}


byte PWMPeriodoEvent_setPeriodo(void * _self,int periodo){
  struct PWMPeriodoEvent * self = _self;
  byte err= setPeriodo((struct IPWM *)DecoradorSalida_getDecorado(_self),periodo);
  MethodContainer_execute(&self->listeners);
  return err;
}
