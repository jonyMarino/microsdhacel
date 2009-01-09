/** ###################################################################
**     Filename  : PWMSoft.c
**     Project   : Controlador
**     Processor : MC9S12GC32CFU16
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 11/08/2008, 10:39
**     Abstract  :
**         Clase que encapsula el comportamiento del PWM01,
**      NO DEBE USARSE CON PWM45. 
**		 Ancestor  : PWM
**     Autor     : Jonathan Marino
**     mail      : jonymarino@gmail.com
** ###################################################################*/

#include <stddef.h>

#include "PWMSoft.h"
#include "Salida_protected.h"

void PWMSoft_DefConstruct(void* self,va_list *args );
void PWMSoft_setDuty(struct PWMSoft* self,uint Val);
void PWMSoft_setTipoSalida(struct PWMSoft* self,TipoSalida onoff);
TipoSalida PWMSoft_tipoSalida(struct PWMSoft* self);
TError PWMSoft_setPeriodo(struct PWMSoft* self,int periodo);

const struct IPWMClass PWMSoft={
  IPWM_CLASS_INITIALIZATION(IPWMClass,
                            PWMSoft,
                            PWM,
                            PWMSoft_DefConstruct,
                            NULL,
                            NULL,
                            NULL,
                            Salida_getPotencia,
                            PWMSoft_setDuty,
                            PWMSoft_tipoSalida,
                            PWMSoft_setTipoSalida,
                            Salida_getConectada,
                            Salida_setConectada,
                            PWM_getPeriodo,
                            PWMSoft_setPeriodo)
};

void PWMSoft_onCambio(struct PWMSoft* self);

static const ulong periodos[]={   
  100,											//100 ms
  200,											//200 ms
  500 ,											//500 ms
  1000 ,											//1s
  2000 ,											//2s
  5000, 											//5s
  10000, 											//10s
  20000,											//20s
  50000,											//50s
  5   											  //5ms
};
/*
** ===================================================================
**     Method     :  PWMSoft_Construct 
**    Description : Metodo Construir el PWMSoft
** ===================================================================
*/
void PWMSoft_Construct(struct PWMSoft* self,TConfPWM * conf,byte * salida,int bit){
  PWM_Construct(self,conf);
  self->salida = salida;
  self->mask=1<<bit;
  newAlloced(&self->timer,&MethodTimer,(ulong)periodos[PWM_getPeriodo(self)],PWMSoft_onCambio,self);
  Timer_Stop(&self->timer);													 
}
/*
** ===================================================================
**     Method      :  PWMSoft_DefConstruct 
**    Description : Constructor por defecto del PWMSoft
** ===================================================================
*/
void PWMSoft_DefConstruct(void* self,va_list *args ){
  PWMSoft_Construct(self,va_arg(*args,void*),va_arg(*args,byte*),va_arg(*args,int));
}

/*
** ===================================================================
**     Method      :  PWMSoft_setDuty 
**    Description : Setear duty del PWMSoft
** ===================================================================
*/
void PWMSoft_setDuty(struct PWMSoft* self,uint duty){
  if(PWMSoft_tipoSalida(self)==SALIDA_ONOFF){		    
    if(duty==0)
      clrReg8Bits(*self->salida, self->mask);             
    else
      setReg8Bits(*self->salida, self->mask);            
  }
  Salida_setPotencia(self,duty);
}

/*
** ===================================================================
**     Method      :  PWMSoft_setDuty 
**    Description : Setear duty del PWMSoft
** ===================================================================
*/
void PWMSoft_setDutyProp(struct PWMSoft* self){
    int pot = Salida_getPotencia(self);
    Timer_Stop(&self->timer);
    if(pot!=0){
      setReg8Bits(*self->salida, self->mask);  
      Timer_setTime(&self->timer,periodos[PWM_getPeriodo(self)]* Salida_getPotencia(self)/1000);
    }else{
      clrReg8Bits(*self->salida, self->mask);  
      Timer_setTime(&self->timer,periodos[PWM_getPeriodo(self)]);
    }  
}

/*
** ===================================================================
**     Method      :  PWMSoft_setTipoSalida 
**    Description : Setear el PWMSoft en on-off o en PID
** ===================================================================
*/
void PWMSoft_setTipoSalida(struct PWMSoft* self,TipoSalida onoff){
   if(onoff==SALIDA_ONOFF){
    Timer_Stop(&self->timer);
   }else{
     PWMSoft_setDutyProp(self);
   }
}

/*
** ===================================================================
**     Method      :  PWMSoft_setTipoSalida 
**    Description : verifica si el PWMSoft esta en on-off o en proporcional
** ===================================================================
*/
TipoSalida PWMSoft_tipoSalida(struct PWMSoft* self){
  return (Timer_isfinish(&self->timer))?SALIDA_ONOFF:SALIDA_PROPORCIONAL;
}

/*
** ===================================================================
**     Method      :  PWMSoft_setPeriod 
**    Description : Setear el periodo del PWMSoft
** ===================================================================
*/
TError PWMSoft_setPeriodo(struct PWMSoft* self,int periodo){
  TError err;
  if(periodo<0 || periodo>PWM_MAX_VALUE_PERIODS)
    return ERR_VALUE; //error
  err= PWM_setPeriodo(self,periodo);
  if(!err){
    if(PWMSoft_tipoSalida(self)==SALIDA_PROPORCIONAL)
      PWMSoft_setDutyProp(self);
  }
  return err;
}

/*
** ===================================================================
**     Method      :  PWMSoft_onCambio 
**    Description : 
** ===================================================================
*/
void PWMSoft_onCambio(struct PWMSoft* self){
  int pot = Salida_getPotencia(self);
  if(testReg8Bits(*self->salida, self->mask)){    
    if( pot == 1000 )
      return;
    else{
      int tiempo = (periodos[PWM_getPeriodo(self)]* (1000-pot))/1000;
      if(!tiempo)  //no alcanzo la resolucion
        return;
      clrReg8Bits(*self->salida, self->mask);
      Timer_setTime(&self->timer,tiempo);
    }
  }else{
    if( pot == 0 )
      return;
    else{
      int tiempo = (periodos[PWM_getPeriodo(self)]* pot)/1000;
      if(!tiempo) //no alcanzo la resolucion
        return;
      setReg8Bits(*(self->salida), self->mask);
      Timer_setTime(&self->timer,tiempo);
    }
  }
  
}



