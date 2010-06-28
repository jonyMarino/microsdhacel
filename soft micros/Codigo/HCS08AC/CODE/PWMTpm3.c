#include <stddef.h>
#include <stdarg.h>
#include <string.h> 

#include "PWMTpm3.h"
#include "Salida_protected.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "stdtypes.h"
#include "PWM.h"
#include "Salida.h"
#include "Errores.h"


void PWMTpm3_DefConstruct(void* self,va_list *args );

void PWMTpm3_setDuty(struct PWMTpm3* self,uint Val);

void PWMTpm3_setTipoSalida(struct PWMTpm3* self,TipoSalida onoff);

bool PWMTpm3_getTipoSalida(void);

TError PWMTpm3_setPeriodo(struct PWMTpm3* self,int periodo);

const struct IPWMClass PWMTpm3={
  IPWM_CLASS_INITIALIZATION(IPWMClass,
                            PWMTpm3,
                            PWM,
                            PWMTpm3_DefConstruct,
                            NULL,
                            NULL,
                            NULL,
                            Salida_getPotencia,
                            PWMTpm3_setDuty,
                            PWMTpm3_getTipoSalida,
                            PWMTpm3_setTipoSalida,
                            Salida_getConectada,
                            Salida_setConectada,
                            PWM_getPeriodo,
                            PWMTpm3_setPeriodo)
};

/*
** ===================================================================
**     Method     :  PWMTpm3_Construct 
**    Description : Metodo Construir el PWMTpm1
** ===================================================================
*/
void PWMTpm3_Construct(struct PWMTpm3* self,TConfPWM * conf){
  PWM_Construct(self,conf);
  
  /* Listo*/
  
   PWM3_Init();
   pwm3_setperiodo (conf->period);
 
  
}
/*
** ===================================================================
**     Method      :  PWMTpm3_DefConstruct 
**    Description : Constructor por defecto del PWMTpm1
** ===================================================================
*/
void PWMTpm3_DefConstruct(void* self,va_list *args ){
  PWMTpm3_Construct(self,va_arg(*args,void*));
}

/*
** ===================================================================
**     Method      :  PWMTpm3_setDuty 
**    Description : Setear duty del PWMTpm1
** ===================================================================
*/
void PWMTpm3_setDuty(struct PWMTpm3* self,uint duty){
  /*setear duty*/
  
   pwm3_setduty (duty); 
 
  Salida_setPotencia(self,duty);
}

/*
** ===================================================================
**     Method      :  PWMTpm3_setTipoSalida 
**    Description : Setear el PWMTpm1 en on-off o en PID
** ===================================================================
*/
void PWMTpm3_setTipoSalida(struct PWMTpm3* self,TipoSalida onoff){
    /*setear tipoSalida*/
    Proporcional_Onoff3(onoff);
}

/*
** ===================================================================
**     Method      :  PWMTpm3_setTipoSalida 
**    Description : verifica si el PWMTpm1 esta en on-off o en proporcional
** ===================================================================
*/
bool PWMTpm3_getTipoSalida(void){
  
 return pwm2_getProporcionalOnOff (); 
}
/*
** ===================================================================
**     Method      :  PWMTpm3_setPeriod 
**    Description : Setear el periodo del PWMTpm1
** ===================================================================
*/
TError PWMTpm3_setPeriodo(struct PWMTpm3* self,int periodo){
  TError err;
  if(periodo<0 || periodo>PWM_MAX_VALUE_PERIODS)
    return ERR_VALUE; //error
  err= PWM_setPeriodo(self,periodo);
  if(!err){
    /*setear periodo*/
   pwm3_setperiodo (periodo); 
  }
  return err;
}


