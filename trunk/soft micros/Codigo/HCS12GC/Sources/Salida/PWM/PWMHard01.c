/** ###################################################################
**     Filename  : PWMHard01.c
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

#include "PWMHard01.h"
#include "PWMHard_protected.h"


void PWMHard01_DefConstruct(void* self,va_list *args );
void PWMHard01_setDuty(struct PWMHard01* self,uint Val);
void PWMHard01_setTipoSalida(struct PWMHard01* self,TipoSalida onoff);
TipoSalida PWMHard01_tipoSalida(struct PWMHard01* self);
TError PWMHard01_setPeriodo(struct PWMHard01* self,int periodo);

const struct IPWMClass PWMHard01={
  IPWM_CLASS_INITIALIZATION(IPWMClass,
                            PWMHard01,
                            PWM,
                            PWMHard01_DefConstruct,
                            NULL,
                            NULL,
                            NULL,
                            Salida_getPotencia,
                            PWMHard01_setDuty,
                            PWMHard01_tipoSalida,
                            PWMHard01_setTipoSalida,
                            Salida_getConectada,
                            Salida_setConectada,
                            PWM_getPeriodo,
                            PWMHard01_setPeriodo)
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
**     Method     :  PWMHard01_Construct 
**    Description : Metodo Construir el PWMHard01
** ===================================================================
*/
void PWMHard01_Construct(struct PWMHard01* self,TConfPWM * conf){
  PWM_Construct(self,conf);
  
  CONTROLADOR_PWM_INIT(0,1);
  													 
  PWMPRCLK_PCKA = 6; 		// dividido 64
   
  
  setReg8Bits(MODRR, 2);  //cablear al puerto T 
  setReg8Bits(DDRT, 2);
}
/*
** ===================================================================
**     Method      :  PWMHard01_DefConstruct 
**    Description : Constructor por defecto del PWMHard01
** ===================================================================
*/
void PWMHard01_DefConstruct(void* self,va_list *args ){
  PWMHard01_Construct(self,va_arg(*args,void*));
}

/*
** ===================================================================
**     Method      :  PWMHard01_setDuty 
**    Description : Setear duty del PWMHard01
** ===================================================================
*/
void PWMHard01_setDuty(struct PWMHard01* self,uint duty){
  if(PWME_PWME1){		 /* PWM?*/    
    PWMHard_setDuty(RefPWM01,duty);
  }
  else{
    if(duty==0)
      clrReg8Bits(PTT, 2);               /* PTT1=0 */
    else
      setReg8Bits(PTT, 2);               /* PTT1=1 */ 
  }
  Salida_setPotencia(self,duty);
}

/*
** ===================================================================
**     Method      :  PWMHard01_setTipoSalida 
**    Description : Setear el PWMHard01 en on-off o en PID
** ===================================================================
*/
void PWMHard01_setTipoSalida(struct PWMHard01* self,TipoSalida onoff){
    PWME_PWME1 = (onoff==SALIDA_ONOFF)?0:1;
}

/*
** ===================================================================
**     Method      :  PWMHard01_setTipoSalida 
**    Description : verifica si el PWMHard01 esta en on-off o en proporcional
** ===================================================================
*/
TipoSalida PWMHard01_tipoSalida(struct PWMHard01* self){
  return (PWME_PWME1)?SALIDA_PROPORCIONAL:SALIDA_ONOFF;
}

/*
** ===================================================================
**     Method      :  PWMHard01_setPeriod 
**    Description : Setear el periodo del PWMHard01
** ===================================================================
*/
TError PWMHard01_setPeriodo(struct PWMHard01* self,int periodo){
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
        PWMCLK_PCLK1 = 0;
        break;
      default:
        PWMCLK_PCLK1 = 1; 
        if(tperiodo == PWM_50sec)
          PWMSCLA = 200;
        else
          PWMSCLA = 50;    
    }
    
      
    
    PWMPER01 = periodos[periodo];
  }
  return err;
}



