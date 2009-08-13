/*  MODULE: PWMTimer.c*/
#include <stddef.h>

#include "Salida.h"
#include "PWMTimer.h"
#include "Salida_protected.h"
#include "IFsh10.h"
#include "ManejadorMemoria.h"
#include "utils_pwm_timer.h"

void PWMTimer_DefConstruct(void* self,va_list *args );
void PWMTimer_setDuty(void* self,uint Val);
void PWMTimer_setTipoSalida(void* self,TipoSalida onoff);
TipoSalida PWMTimer_tipoSalida(void* self);
TError PWMTimer_setPeriodo(void* self,int periodo);

const struct IPWMClass PWMTimer={
  IPWM_CLASS_INITIALIZATION(IPWMClass,
                            PWMTimer,
                            PWM,
                            PWMTimer_DefConstruct,
                            NULL,
                            NULL,
                            NULL,
                            Salida_getPotencia,
                            PWMTimer_setDuty,
                            PWMTimer_tipoSalida,
                            PWMTimer_setTipoSalida,
                            Salida_getConectada,
                            Salida_setConectada,
                            PWM_getPeriodo,
                            PWMTimer_setPeriodo)
};


extern struct ManejadorMemoria *const pFlash;


/*
** ===================================================================
**     Method     :  PWMTimer_Construct 
**    Description : Metodo Construir el PWMTimer
** ===================================================================
*/
void PWMTimer_Construct(void * _self,TConfPWM * conf, uchar pin_out){
  struct PWMTimer* self = (struct PWMTimer*)_self;
  PWM_Construct(self,conf);
  
  self->PinNum=pin_out;
  setPWM_period(self,conf->period);
  PWM_init(self,pin_out);
}
/*
** ===================================================================
**     Method      :  PWMTimer_DefConstruct 
**    Description : Constructor por defecto del PWMTimer
** ===================================================================
*/
void PWMTimer_DefConstruct(void * _self,va_list *args ){
  struct PWMTimer* self = (struct PWMTimer*)_self;
  PWMTimer_Construct(self,va_arg(*args,TConfPWM *),(uchar)va_arg(*args,int));
}

/*
** ===================================================================
**     Method      :  PWMTimer_setDuty 
**    Description : Setear duty del PWMTimer
** ===================================================================
*/
void PWMTimer_setDuty(void * _self,uint duty){
  struct PWMTimer* self = (struct PWMTimer*)_self;
  if(pwm_timer_isEnable(self->PinNum))			/* PID?*/
    PWM_SetRatio16(self,duty);
  else{
    if(duty==0)
      PWM_ClrValue(self->PinNum);
    else
      PWM_SetValue(self->PinNum); 
  }
  Salida_setPotencia(self,duty);
}

/*
** ===================================================================
**     Method      :  PWMTimer_setTipoSalida 
**    Description : Setear el PWMTimer en on-off o en PID
** ===================================================================
*/
void PWMTimer_setTipoSalida(void * _self,TipoSalida tipoSalida){
  struct PWMTimer* self = (struct PWMTimer*)_self;
  if(tipoSalida==SALIDA_ONOFF)
    PWM_Disable(self->PinNum); 
  else
    PWM_Enable(self->PinNum);
}

/*
** ===================================================================
**     Method      :  PWMTimer_setTipoSalida 
**    Description : verifica si el PWMTimer esta en on-off o en proporcional
** ===================================================================
*/
TipoSalida PWMTimer_tipoSalida(void * _self){
  struct PWMTimer* self = (struct PWMTimer*)_self;
  return (pwm_timer_isEnable(self->PinNum))?SALIDA_PROPORCIONAL:SALIDA_ONOFF;
}

/*
** ===================================================================
**     Method      :  PWMTimer_setPeriod 
**    Description : Setear el periodo del PWMTimer
** ===================================================================
*/
TError PWMTimer_setPeriodo(void * _self,int periodo){
  struct PWMTimer* self = (struct PWMTimer*)_self;
  TError err;
  if(periodo<0 || periodo>PWM_MAX_VALUE_PERIODS)
    return ERR_VALUE; //error
  err= PWM_setPeriodo(self,periodo);
  if(!err)
    setPWM_period(self,(uchar)periodo);
  return err;
}


