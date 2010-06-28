 /** ###################################################################
**     Filename  : PWMTpm1.c
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
#include <stdarg.h>
#include <string.h> 

#include "PWMTpm2.h"
#include "Salida_protected.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "stdtypes.h"
#include "PWM.h"
#include "Salida.h"
#include "Errores.h"


void PWMTpm2_DefConstruct(void* self,va_list *args );

void PWMTpm2_setDuty(struct PWMTpm2* self,uint Val);

void PWMTpm2_setTipoSalida(struct PWMTpm2* self,TipoSalida onoff);

bool PWMTpm2_getTipoSalida(void);

TError PWMTpm2_setPeriodo(struct PWMTpm2* self,int periodo);

const struct IPWMClass PWMTpm2={
  IPWM_CLASS_INITIALIZATION(IPWMClass,
                            PWMTpm2,
                            PWM,
                            PWMTpm2_DefConstruct,
                            NULL,
                            NULL,
                            NULL,
                            Salida_getPotencia,
                            PWMTpm2_setDuty,
                            PWMTpm2_getTipoSalida,
                            PWMTpm2_setTipoSalida,
                            Salida_getConectada,
                            Salida_setConectada,
                            PWM_getPeriodo,
                            PWMTpm2_setPeriodo)
};

/*
** ===================================================================
**     Method     :  PWMTpm2_Construct 
**    Description : Metodo Construir el PWMTpm1
** ===================================================================
*/
void PWMTpm2_Construct(struct PWMTpm2* self,TConfPWM * conf){
  PWM_Construct(self,conf);
  
  /* Listo*/
  
   PWM2_Init();
   pwm2_setperiodo (conf->period);
 
  
}
/*
** ===================================================================
**     Method      :  PWMTpm2_DefConstruct 
**    Description : Constructor por defecto del PWMTpm1
** ===================================================================
*/
void PWMTpm2_DefConstruct(void* self,va_list *args ){
  PWMTpm2_Construct(self,va_arg(*args,void*));
}

/*
** ===================================================================
**     Method      :  PWMTpm2_setDuty 
**    Description : Setear duty del PWMTpm1
** ===================================================================
*/
void PWMTpm2_setDuty(struct PWMTpm2* self,uint duty){
  /*setear duty*/
  
   pwm2_setduty (duty); 
 
  Salida_setPotencia(self,duty);
}

/*
** ===================================================================
**     Method      :  PWMTpm2_setTipoSalida 
**    Description : Setear el PWMTpm1 en on-off o en PID
** ===================================================================
*/
void PWMTpm2_setTipoSalida(struct PWMTpm2* self,TipoSalida onoff){
    /*setear tipoSalida*/
    pwm2_proporcionalOnOff(onoff);
}

/*
** ===================================================================
**     Method      :  PWMTpm2_setTipoSalida 
**    Description : verifica si el PWMTpm1 esta en on-off o en proporcional
** ===================================================================
*/
bool PWMTpm2_getTipoSalida(void){
  
 return pwm2_getProporcionalOnOff (); 
}

/*
** ===================================================================
**     Method      :  PWMTpm2_setPeriod 
**    Description : Setear el periodo del PWMTpm1
** ===================================================================
*/
TError PWMTpm2_setPeriodo(struct PWMTpm2* self,int periodo){
  TError err;
  if(periodo<0 || periodo>PWM_MAX_VALUE_PERIODS)
    return ERR_VALUE; //error
  err= PWM_setPeriodo(self,periodo);
  if(!err){
    /*setear periodo*/
   pwm2_setperiodo (periodo); 
  }
  return err;
}



