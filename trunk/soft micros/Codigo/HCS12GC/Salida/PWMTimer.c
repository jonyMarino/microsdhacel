/*  MODULE: PWMTimer.c*/
#include <stddef.h>

#include "Salida.h"
#include "PWMTimer.h"
#include "Salida_protected.h"
#include "IFsh10.h"
#include "ManejadorMemoria.h"
#include "utils_pwm_timer.h"

void PWMTimer_DefConstruct(void* self,va_list *args );
void PWMTimer_setDuty(struct PWMTimer* self,uint Val);
void PWMTimer_setTipoSalida(struct PWMTimer* self,TipoSalida onoff);
TipoSalida PWMTimer_tipoSalida(struct PWMTimer* self);
TError PWMTimer_setPeriodo(struct PWMTimer* self,int periodo);

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

extern struct FlashBkpEnFlash flash;
static struct ManejadorMemoria *const pFlash=&flash;


/*
** ===================================================================
**     Method     :  PWMTimer_Construct 
**    Description : Metodo Construir el PWMTimer
** ===================================================================
*/
void PWMTimer_Construct(struct PWMTimer* self,TConfPWM * conf, uchar pin_out){
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
void PWMTimer_DefConstruct(void* self,va_list *args ){
  PWMTimer_Construct(self,va_arg(*args,void*),(uchar)va_arg(*args,int));
}

/*
** ===================================================================
**     Method      :  PWMTimer_setDuty 
**    Description : Setear duty del PWMTimer
** ===================================================================
*/
void PWMTimer_setDuty(struct PWMTimer* self,uint duty){
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
void PWMTimer_setTipoSalida(struct PWMTimer* self,TipoSalida tipoSalida){
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
TipoSalida PWMTimer_tipoSalida(struct PWMTimer* self){
  return (pwm_timer_isEnable(self->PinNum))?SALIDA_PROPORCIONAL:SALIDA_ONOFF;
}

/*
** ===================================================================
**     Method      :  PWMTimer_setPeriod 
**    Description : Setear el periodo del PWMTimer
** ===================================================================
*/
TError PWMTimer_setPeriodo(struct PWMTimer* self,int periodo){
  TError err;
  if(periodo<0 || periodo>PWM_MAX_VALUE_PERIODS)
    return ERR_VALUE; //error
  err= PWM_setPeriodo(self,periodo);
  if(!err)
    setPWM_period(self,(uchar)periodo);
  return err;
}


