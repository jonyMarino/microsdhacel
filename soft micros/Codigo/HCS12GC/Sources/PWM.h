#ifndef _PWM_CLASS_H
#define _PWM_CLASS_H

#include "stdtypes.h"
#include "Errores.h"
#include "IPWM.h"
#include "Salida.h"
#include "IFshMem.h"
#include "FshTypeSizes.h"



typedef struct{
  fbyte period;//(TPeriod)
}TConfPWM;

struct PWM{
  struct Salida base;
  TConfPWM * conf;          //Configuracion en FLASH
};

extern const struct IPWMClass PWM;


void PWM_Construct(void* _self,TConfPWM * conf);
/*
** ===================================================================
**     Method      :  PWM_setPeriodo 
**    Description : Setear el periodo del PWM
** ===================================================================
*/
TError PWM_setPeriodo(void* _self,int period);
/*
** ===================================================================
**     Method      :  PWM_getPeriodo 
**    Description : Obtener el periodo del PWM
** ===================================================================
*/
int PWM_getPeriodo(void* _self);

/*
** ===================================================================
**     Method      :  PWM_getLimSupPeriod
**    Description : Obtener el limite superior del periodo del PWM
** ===================================================================
*/
int PWM_getLimSupPeriodo(void* _self);

#endif