/** ###################################################################
**     Filename  : PWMHard23.c
**     Project   : Controlador
**     Processor : MC9S12GC32CFU16
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 11/08/2008, 10:39
**     Abstract  :
**         Clase que encapsula el comportamiento del PWM23. 
**		 Ancestor  : PWM
**     Autor     : Jonathan Marino
**     mail      : jonymarino@gmail.com
** ###################################################################*/

#include <stddef.h>

#include "PWMHard23.h"
#include "PWMHard_protected.h"


void PWMHard23_DefConstruct(void* self,va_list *args );
void PWMHard23_setDuty(struct PWMHard23* self,uint Val);
void PWMHard23_setTipoSalida(struct PWMHard23* self,TipoSalida onoff);
TipoSalida PWMHard23_tipoSalida(struct PWMHard23* self);
TError PWMHard23_setPeriodo(struct PWMHard23* self,int periodo);

const struct IPWMClass PWMHard23={
  IPWM_CLASS_INITIALIZATION(IPWMClass,
                            PWMHard23,
                            PWM,
                            PWMHard23_DefConstruct,
                            NULL,
                            NULL,
                            NULL,
                            Salida_getPotencia,
                            PWMHard23_setDuty,
                            PWMHard23_tipoSalida,
                            PWMHard23_setTipoSalida,
                            Salida_getConectada,
                            Salida_setConectada,
                            PWM_getPeriodo,
                            PWMHard23_setPeriodo)
};

static const int periodos[]={   
  25000,											//100 ms
  50000,											//200 ms
  1250 ,											//500 ms
  2500 ,											//1s
  5000 ,											//2s
  12500,											//5s
  25000, 											//10s
  50000,											//20s
  31250,											//50s
  1250   											//5ms
};
/*
** ===================================================================
**     Method     :  PWMHard23_Construct 
**    Description : Metodo Construir el PWMHard23
** ===================================================================
*/
void PWMHard23_Construct(struct PWMHard23* self,TConfPWM * conf){
  PWM_Construct(self,conf);
  
  CONTROLADOR_PWM_INIT(2,3);
  													 
  PWMPRCLK_PCKB = 6; 		// dividido 64
   
  
  setReg8Bits(MODRR, 8);  //cablear al puerto T 
  setReg8Bits(DDRT, 8);
}
/*
** ===================================================================
**     Method      :  PWMHard23_DefConstruct 
**    Description : Constructor por defecto del PWMHard23
** ===================================================================
*/
void PWMHard23_DefConstruct(void* self,va_list *args ){
  PWMHard23_Construct(self,va_arg(*args,void*));
}

/*
** ===================================================================
**     Method      :  PWMHard23_setDuty 
**    Description : Setear duty del PWMHard23
** ===================================================================
*/
void PWMHard23_setDuty(struct PWMHard23* self,uint duty){
  if(PWME_PWME3){		 /* PWM?*/    
    PWMHard_setDuty(RefPWM23,duty);
  }
  else{
    if(duty==0)
      clrReg8Bits(PTT, 8);               /* PTT3=0 */
    else
      setReg8Bits(PTT, 8);               /* PTT3=1 */ 
  }
  Salida_setPotencia(self,duty);
}

/*
** ===================================================================
**     Method      :  PWMHard23_setTipoSalida 
**    Description : Setear el PWMHard23 en on-off o en PID
** ===================================================================
*/
void PWMHard23_setTipoSalida(struct PWMHard23* self,TipoSalida onoff){
    PWME_PWME3 = (onoff==SALIDA_ONOFF)?0:1;
}

/*
** ===================================================================
**     Method      :  PWMHard23_setTipoSalida 
**    Description : verifica si el PWMHard23 esta en on-off o en proporcional
** ===================================================================
*/
TipoSalida PWMHard23_tipoSalida(struct PWMHard23* self){
  return (PWME_PWME3)?SALIDA_PROPORCIONAL:SALIDA_ONOFF;
}

/*
** ===================================================================
**     Method      :  PWMHard23_setPeriod 
**    Description : Setear el periodo del PWMHard23
** ===================================================================
*/
TError PWMHard23_setPeriodo(struct PWMHard23* self,int periodo){
  TError err;
  if(periodo<0 || periodo>PWM_MAX_VALUE_PERIODS)
    return ERR_VALUE; //error
  err= PWM_setPeriodo(self,periodo);
  if(!err){
    TPeriod tperiodo = periodo;
    switch(tperiodo){
      case PWM_100ms:
      case PWM_200ms:
      case PWM_Anl:
        PWMCLK_PCLK3 = 0;
        break;
      default:
        PWMCLK_PCLK3 = 1; 
        if(tperiodo == PWM_50sec)
          PWMSCLB = 200;
        else
          PWMSCLB = 50;    
    }
    
      
    
    PWMPER23 = periodos[periodo];
  }
  return err;
}



