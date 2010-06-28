#include <stddef.h>
#include <stdarg.h>
#include <string.h> 

#include "PWMTpm4.h"
#include "Salida_protected.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "stdtypes.h"
#include "PWM.h"
#include "Salida.h"
#include "Errores.h"


void PWMTpm4_DefConstruct(void* self,va_list *args );

void PWMTpm4_setDuty(struct PWMTpm4* self,uint Val);

void PWMTpm4_setTipoSalida(struct PWMTpm4* self,TipoSalida onoff);

bool PWMTpm4_getTipoSalida(void);

TError PWMTpm4_setPeriodo(struct PWMTpm4* self,int periodo);

const struct IPWMClass PWMTpm4={
  IPWM_CLASS_INITIALIZATION(IPWMClass,
                            PWMTpm4,
                            PWM,
                            PWMTpm4_DefConstruct,
                            NULL,
                            NULL,
                            NULL,
                            Salida_getPotencia,
                            PWMTpm4_setDuty,
                            PWMTpm4_getTipoSalida,
                            PWMTpm4_setTipoSalida,
                            Salida_getConectada,
                            Salida_setConectada,
                            PWM_getPeriodo,
                            PWMTpm4_setPeriodo)
};

/*
** ===================================================================
**     Method     :  PWMTpm4_Construct 
**    Description : Metodo Construir el PWMTpm1
** ===================================================================
*/
void PWMTpm4_Construct(struct PWMTpm4* self,TConfPWM * conf){
  PWM_Construct(self,conf);
  
  /* Listo*/
  
   PWM4_Init();
   pwm4_setperiodo (conf->period);
 
  
}
/*
** ===================================================================
**     Method      :  PWMTpm4_DefConstruct 
**    Description : Constructor por defecto del PWMTpm1
** ===================================================================
*/
void PWMTpm4_DefConstruct(void* self,va_list *args ){
  PWMTpm4_Construct(self,va_arg(*args,void*));
}

/*
** ===================================================================
**     Method      :  PWMTpm4_setDuty 
**    Description : Setear duty del PWMTpm1
** ===================================================================
*/
void PWMTpm4_setDuty(struct PWMTpm4* self,uint duty){
  /*setear duty*/
  
   pwm4_setduty (duty); 
 
  Salida_setPotencia(self,duty);
}

/*
** ===================================================================
**     Method      :  PWMTpm4_setTipoSalida 
**    Description : Setear el PWMTpm1 en on-off o en PID
** ===================================================================
*/
void PWMTpm4_setTipoSalida(struct PWMTpm4* self,TipoSalida onoff){
    /*setear tipoSalida*/
    pwm4_ProporcionalOnoff(onoff);
}

/*
** ===================================================================
**     Method      :  PWMTpm4_setTipoSalida 
**    Description : verifica si el PWMTpm1 esta en on-off o en proporcional
** ===================================================================
*/
bool PWMTpm4_getTipoSalida(void){
  /*retornar tipoSalida*/
  
  return pwm4_getProporcionalOnOff (); 

}
/*
** ===================================================================
**     Method      :  PWMTpm4_setPeriod 
**    Description : Setear el periodo del PWMTpm1
** ===================================================================
*/
TError PWMTpm4_setPeriodo(struct PWMTpm4* self,int periodo){
  TError err;
  if(periodo<0 || periodo>PWM_MAX_VALUE_PERIODS)
    return ERR_VALUE; //error
  err= PWM_setPeriodo(self,periodo);
  if(!err){
    /*setear periodo*/
   pwm4_setperiodo (periodo); 
  }
  return err;
}


