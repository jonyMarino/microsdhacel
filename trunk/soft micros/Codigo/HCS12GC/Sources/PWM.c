/*  MODULE: PWM_Class.c*/
#include <stddef.h>

#include "Salida.h"
#include "PWM.h"
#include "IFsh10.h"
#include "ManejadorMemoria.h"
#include "IPWM.h"

#pragma CONST_SEG DEFAULT

void PWM_DefConstruct(void* self,va_list *args );
void PWM_setDuty(struct PWM* self,uint Val);
void PWM_setTipoSalida(struct PWM* self,TipoSalida onoff);
TipoSalida PWM_tipoSalida(struct PWM* self);


const struct IPWMClass PWM={
    ISALIDA_CLASS_INITIALIZATION(ISalidaClass,
                            Salida,
                            ISalida,
                            Object_ctor,
                            Object_dtor,
                            Object_differ,
                            Object_puto,
                            Salida_getPotencia,
                            Salida_setPotencia,
                            NULL,
                            NULL,
                            NULL,
                            NULL
                            )  
};

extern struct ManejadorMemoria *const pFlash;

/*
** ===================================================================
**     Method     :  PWM_Construct 
**    Description : Metodo Construir el PWM
** ===================================================================
*/
void PWM_Construct(void * _self,TConfPWM * conf){
  struct PWM* self = (struct PWM*)_self;
  Salida_constructor(_self);
  self->conf=conf;
}
/*
** ===================================================================
**     Method      :  getPeriodo 
**    Description : Obtener el periodo del PWM
** ===================================================================
*/
int getPeriodo(void* self){
  struct IPWMClass ** classOf = (struct IPWMClass **)self;
  return (*classOf)->getPeriodo(self);
}

/*
** ===================================================================
**     Method      :  setPeriod 
**    Description : Cambia el periode del PWM, sin cambiar el valor de
**                  la configuracion
** ===================================================================
*/
TError setPeriodo(void* self,int periodo){
  struct IPWMClass ** classOf = (struct IPWMClass **)self;
  return (*classOf)->setPeriodo(self,periodo); 
}
/*
** ===================================================================
**     Method      :  PWM_setPeriod 
**    Description : Setear el periodo del PWM
** ===================================================================
*/
TError PWM_setPeriodo(void* _self,int period){
  struct PWM* self = (struct PWM*)_self;
  return _MANEJADOR_MEMORIA_SET_BYTE(pFlash,&self->conf->period,(uchar)period);
}

/*
** ===================================================================
**     Method      :  PWM_getPeriod 
**    Description : Setear el periodo del PWM
** ===================================================================
*/
int PWM_getPeriodo(void* _self){
    struct PWM* self = (struct PWM*)_self;
  return _MANEJADOR_MEMORIA_GET_BYTE(pFlash,&self->conf->period);
}

/*
** ===================================================================
**     Method      :  PWM_getLimSupPeriod
**    Description : Obtener el limite superior del periodo del PWM
** ===================================================================
*/
int PWM_getLimSupPeriodo(void* _self){
    struct PWM* self = (struct PWM*)_self;
  return PWM_MAX_VALUE_PERIODS;
}
