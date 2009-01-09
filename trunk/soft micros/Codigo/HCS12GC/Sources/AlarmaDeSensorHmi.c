/*MODULE: AlarmaDeSensorHmi
**     Filename  : AlarmaDeSensorHmi.C
**     Project   : Controlador
**     Processor : MC9S12GC32CFU16
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 30/04/2008, 15:47
*/
#include "PropWithInc.h"
#include "PropNumerica.h"
#include "PropNumPV.h"
#include "PropTextual.h"

#include "DiagramaNavegacion.h"
#include "ClassBoxLineal.h"
#include "BoxProp.h"
#include "BoxCondicional.h"
#include "DataBox.h"
#include "BoxPropVarName.h"

#include "com_events.h"

#include "AlarmaDeSensor.h"

#include "AlarmaDeSensorHmi.h"

/*****************************/
/********PROPIEDADES**********/
/*****************************/

  /*Histeresis*/
  const struct ConstPropNumPV ParHA={
    AlarmaDeSensor_getHisteresis, AlarmaDeSensor_setHisteresis, NULL, NULL,PropNumPV,"HA ",AlarmaDeSensor_decimales
  };
  /*Valor de alarma*/
  const struct ConstPropNumPV ParAl={
    AlarmaDeSensor_getValor, AlarmaDeSensor_setValor, AlarmaDeSensor_limInf, AlarmaDeSensor_limSup,PropNumPV,"A  ",AlarmaDeSensor_decimales
  };

  /*Tipo de Alarma1*/
    const struct ConstPropTxt ParTAlar1={
    AlarmaDeSensor_getTipoAlarma, AlarmaDeSensor_setTipoAlarma, get_0, AlarmaDeSensor_tipoAlarmaLimSup,PropTxt,"AL ",AlarmaDeSensor_tipoAlarmaMsj
  };
    
  /*Retransmision Low*/
  const struct ConstPropNumPV ParRetLow={
    AlarmaDeSensor_getRetLow, AlarmaDeSensor_setRetLow, NULL, AlarmaDeSensor_retLowLimSup,PropNumPV,"r.L ",AlarmaDeSensor_decimales
  };

  /*Retransmision Hi*/
  const struct ConstPropNumPV ParRetHi={
    AlarmaDeSensor_getRetHi, AlarmaDeSensor_setRetHi, AlarmaDeSensor_retHiLimInf, NULL,PropNumPV,"r.H ",AlarmaDeSensor_decimales
  };


  const struct ClassPropiedad *const AlProps[]={
    &ParHA,
    &ParAl,
    &ParTAlar1,
    &ParRetLow,
    &ParRetHi,
  };
  

/*
** ===================================================================
**     Function      :  AlarmasHmi_ComuAdd 
**     Description :  Agrega la alarma a la comunicacion
** ===================================================================
*/

word AlarmaDeSensorHmi_ComuAdd(const struct AlarmaMult * al,word dir_ini){
  word cant = sizeof(AlProps)/sizeof(struct ClassPropiedad *)-1;
  com_AddProps(AlProps,al,dir_ini,dir_ini+cant);
  return cant;
}


const struct BlockConstBoxPropBase CBox_AlarmaDeSensorVal;
const struct BlockConstBoxPropVarName CBox_H_AlarmaDeSensor;
const struct BlockConstBoxCondl CBox_TAlarmaDeSensor1;

const struct  BlockCnstrBoxLin CBox_RET;
/*
** ===================================================================
**     Function    :  AlarmasHmi_AddBoxes 
**     Description :  Agrega la alarma a los boxes 
** ===================================================================
*/
#ifdef _PWM
extern const struct BlockConstBoxPropBase CBox_PeriodoAlarmaDeSensor;
#endif

void AlarmaDeSensorHmi_AddBoxes(const struct AlarmaMult * al,uchar num_obj){
  DN_AddBox(0,"op",&CBox_AlarmaDeSensorVal,al,num_obj); 
  DN_AddBox(0,"tun ",&CBox_H_AlarmaDeSensor,al,num_obj); 
  DN_AddBox(0,"Set ",&CBox_TAlarmaDeSensor1,al,num_obj);
}


/*Operador*/	
const struct BlockConstBoxPropBase CBox_AlarmaDeSensorVal=
      {
      BoxPropBase,						                  /* funcion que procesa al box*/
			&ParAl											/* direccion en la E2Prom - el EEProm Start, if FAlarmaDeSensorSE no guarda valor*/
			};

/*  tun */
char * AlarmasHmi_getHDesc(struct PropWInc * prop){
  if(PropWInc_getValorTmp(prop)>0)
    return "AbA";
  return "HA";
}

const struct BlockConstBoxPropVarName CBox_H_AlarmaDeSensor=
      {
      BoxPropVarName,						                  /* funcion que procesa al box*/
			&ParHA,											/* direccion en la E2Prom - el EEProm Start, if FAlarmaDeSensorSE no guarda valor*/
      NULL,
      AlarmasHmi_getHDesc  
			};
			
/*Set*/
void * Box_TAlarmaDeSensor1(void * prop,uchar tecla){
  if(tecla=='r'){
    if(_Getter_getVal(prop)==_RET)
      return &CBox_RET;
  }
  return NULL;
}

const struct BlockConstBoxCondl CBox_TAlarmaDeSensor1=	{
  			  BoxCondl,
  			  &ParTAlar1,											/* direccion en la E2Prom - el EEProm Start, if FAlarmaDeSensorSE no guarda valor*/
          Box_TAlarmaDeSensor1
};

const struct ConstructorPropWInc*const Props_RET[]=	{
  			  &ParRetLow,											/* direccion en la E2Prom - el EEProm Start, if FAlarmaDeSensorSE no guarda valor*/
  			  &ParRetHi,
  			  NULL
};

const struct  BlockCnstrBoxLin CBox_RET={
  				BoxLineal,
  			  &Props_RET,
  			  NULL
};

