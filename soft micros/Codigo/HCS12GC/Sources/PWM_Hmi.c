/*  MODULE: PWM_Hmi.c*/


#include "GettersVisual.h"
#include "PropTextual.h"
#include "UpdatedBox.h"
#include "DiagramaNavegacion.h"
#include "BoxProp.h"
#include "ReadOnlyBox.h"

#include "com_events.h"

#include "utils_pwm_timer.h"
#include "PWM.h"

#include "PWM_Hmi.h"

#pragma MESSAGE DISABLE C1825          /* Disable warning C1825 "Indirection" */



/*****************************/
/********PROPIEDADES**********/
/*****************************/

  /*Periodo*/ 

  const struct ConstPropTxt ParPeriodo={
    &PropiedadGenerica,getPeriodo,setPeriodo,get_0,PWM_getLimSupPeriodo,&PropTxt,"PEr",PWM_getPeriodText
  };
  
  /*Periodo Alarma*/ 

  const struct ConstPropTxt ParPeriodoAL={
    &PropiedadGenerica,getPeriodo,setPeriodo,get_0,PWM_getLimSupPeriodo,&PropTxt,"PrA",PWM_getPeriodText
  };

  /* Potencia Actual */
  const struct ConstrGetterNum GetterPot={
    &GetterGenerico,getPotencia,&GetterNum,"Pot",1
  };
  
  const struct GetterGenerico *const PWMGetters[]={
    &ParPeriodo,
    &GetterPot
  };
  


  const NEW_ARRAY(arrayPWMGetters,PWMGetters);
  const NEW_ARRAY(arrayPWMGetterPot,PWMGetters+1);
/*
** ===================================================================
**     Function      :  PwmHmi_ComuAdd 
**     Description :  Agrega la salida a la comunicacion
** ===================================================================
*/

word PwmHmi_ComuAdd(const struct PWM * pwm,word dir_ini){
  word cant = sizeof(PWMGetters)/sizeof(struct GetterGenerico *)-1;
  com_Add(PWMGetters,pwm,dir_ini,dir_ini+cant);
  return cant;
}  
 /***********************/
 /****** BOXES  *********/
 /***********************/
const struct BlockConstBoxPropBase CBox_Periodo;
const struct BlockConstrUpdatedBox	 CBox_Potencia;
 
            
/*
** ===================================================================
**     Function      :  PWM_Hmi_Add 
**     Description :  Agrega a los boxes el pwm
** ===================================================================
*/

 void PWM_Hmi_Add(const struct PWM * pwm,uchar num_obj){
  DN_AddBox(0,"tun ",&CBox_Periodo,pwm,num_obj);
//  DN_AddBox(0,"op",&CBox_Potencia,pwm,num_obj);
 }
 
 /*
** ===================================================================
**     Function      :  PWMHmi_addIndexedPeriodo 
**     Description :  Agrega el periodo del pwm en una posicion específica
** ===================================================================
*/

 void PWMHmi_addIndexedPeriodo(const struct PWM * pwm,uchar access,const char * str,uchar num_obj,uchar index){
  DN_AddIndexedBox(access,str,&CBox_Periodo,pwm,num_obj,index);
//  DN_AddBox(0,"op",&CBox_Potencia,pwm,num_obj);
 }
 

/* Periodo */
const struct BlockConstBoxPropBase CBox_Periodo={
      &BoxPropBase,									/* funcion que procesa al box*/
      &ParPeriodo												
}; 

const struct BlockConstBoxPropBase CBox_PeriodoAL={
      &BoxPropBase,									/* funcion que procesa al box*/
      &ParPeriodoAL												
}; 

/* Potencia */

const struct BlockConstrUpBox	 CBox_Potencia={
  &UpdatedBox,
  &GetterPot,
  500
};


