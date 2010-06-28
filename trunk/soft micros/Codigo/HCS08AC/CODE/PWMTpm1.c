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

#include "PWMTpm1.h"
#include "Salida_protected.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "stdtypes.h"
#include "PWM.h"
#include "Salida.h"
#include "Errores.h"


void PWMTpm1_DefConstruct(void* self,va_list *args );

void PWMTpm1_setDuty(struct PWMTpm1* self,uint Val);

void PWMTpm1_setTipoSalida(struct PWMTpm1* self,TipoSalida onoff);

bool PWMTpm1_getTipoSalida(void);

TError PWMTpm1_setPeriodo(struct PWMTpm1* self,int periodo);

const struct IPWMClass PWMTpm1={
  IPWM_CLASS_INITIALIZATION(IPWMClass,
                            PWMTpm1,
                            PWM,
                            PWMTpm1_DefConstruct,
                            NULL,
                            NULL,
                            NULL,
                            Salida_getPotencia,
                            PWMTpm1_setDuty,
                            PWMTpm1_getTipoSalida,
                            PWMTpm1_setTipoSalida,
                            Salida_getConectada,
                            Salida_setConectada,
                            PWM_getPeriodo,
                            PWMTpm1_setPeriodo)
};

/*
** ===================================================================
**     Method     :  PWMTpm1_Construct 
**    Description : Metodo Construir el PWMTpm1
** ===================================================================
*/
void PWMTpm1_Construct(struct PWMTpm1* self,TConfPWM * conf){
  PWM_Construct(self,conf);
  
  /* Listo*/
  
   PWM1_Init();
   pwm1_setperiodo (conf->period);
 
  
}
/*
** ===================================================================
**     Method      :  PWMTpm1_DefConstruct 
**    Description : Constructor por defecto del PWMTpm1
** ===================================================================
*/
void PWMTpm1_DefConstruct(void* self,va_list *args ){
  PWMTpm1_Construct(self,va_arg(*args,void*));
}

/*
** ===================================================================
**     Method      :  PWMTpm1_setDuty 
**    Description : Setear duty del PWMTpm1
** ===================================================================
*/
void PWMTpm1_setDuty(struct PWMTpm1* self,uint duty){
  /*setear duty*/
  
   pwm1_setduty (duty); 
 
  Salida_setPotencia(self,duty);
}

/*
** ===================================================================
**     Method      :  PWMTpm1_setTipoSalida 
**    Description : Setear el PWMTpm1 en on-off o en PID
** ===================================================================
*/
void PWMTpm1_setTipoSalida(struct PWMTpm1* self,TipoSalida onoff){
    /*setear tipoSalida*/
    pwm1_proporcionalOnOff(onoff);
}

/*
** ===================================================================
**     Method      :  PWMTpm1_setTipoSalida 
**    Description : verifica si el PWMTpm1 esta en on-off o en proporcional
**                  1-onoff 0-porporcional
** ===================================================================
*/
bool PWMTpm1_getTipoSalida(void){
  /*retornar tipoSalida*/
  
  return pwm1_getProporcionalOnOff (); 

}

/*
** ===================================================================
**     Method      :  PWMTpm1_setPeriod 
**    Description : Setear el periodo del PWMTpm1
** ===================================================================
*/
TError PWMTpm1_setPeriodo(struct PWMTpm1* self,int periodo){
  TError err;
  if(periodo<0 || periodo>PWM_MAX_VALUE_PERIODS)
    return ERR_VALUE; //error
  err= PWM_setPeriodo(self,periodo);
  if(!err){
    /*setear periodo*/
   pwm1_setperiodo (periodo); 
  }
  return err;
}



