#ifndef _IPWM_H
#define _IPWM_H

#include "Salida.h"
#include "pwm_periodos.h"
#include "PE_Types.h"

struct IPWMClass{            
  struct ISalidaClass super;
  int (*getPeriodo)(void * self);
  byte (*setPeriodo)(void * self,int);
};






struct IPWM{
  struct ISalida super;
};

extern const struct Class IPWMClass;
extern const struct IPWMClass IPWM;

#define IPWM_CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto,getPotencia,setPotencia,getTipoSalida,setTipoSalida,getConectada,setConectada,getPeriodo,setPeriodo)\
  ISALIDA_CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto,getPotencia,setPotencia,getTipoSalida,setTipoSalida,getConectada,setConectada),\
  getPeriodo, \
  setPeriodo
/*
** ===================================================================
**     Method      :  getPeriodo 
**    Description : Obtener el periodo del PWM
** ===================================================================
*/
int getPeriodo(void* self);
/*
** ===================================================================
**     Method     : setPeriodo 
**    Description : Cambia el periodo del PWM
** ===================================================================
*/
byte setPeriodo(void* self,int period);


#endif