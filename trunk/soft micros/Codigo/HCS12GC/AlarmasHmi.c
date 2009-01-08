/*MODULE: AlarmasHmi
**     Filename  : AlarmasHmi.C
**     Project   : Controlador
**     Processor : MC9S12GC32CFU16
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 22/01/2008, 11:00
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

#include "Alarmas.h"

#include "AlarmasHmi.h"

/*****************************/
/********PROPIEDADES**********/
/*****************************/

  /*Histeresis*/
  const struct ConstPropNumPV ParHA={
    AL_getHisteresis, set_H_Alarma, NULL, NULL,PropNumPV,"HA ",AL_getDec
  };
  /*Valor de alarma*/
  const struct ConstPropNumPV ParAl={
    get_AL, set_AL, get_LimInf_AL, get_LimSup_AL,PropNumPV,"A  ",AL_getDec
  };

  /*Tipo de Alarma1*/
    const struct ConstPropTxt ParTAlar1={
    get_TipoAlarma1, set_TipoAlarma1, get_0, get_LimSup_TipoAlarma1,PropTxt,"AL ",AL_getTAL1str
  };
  
  /*Tipo de Alarma2*/
  const struct ConstPropTxt ParTAlar2={
    get_TipoAlarma2, set_TipoAlarma2, get_0, get_LimSup_TipoAlarma2,PropTxt,"AL ",AL_getTAL2str
  };
  
  /*Retransmision Low*/
  const struct ConstructorPropWInc ParRetLow={
    get_RetLow, set_RetLow, NULL, get_LimSup_RetLow,PropWInc,"REtL"
  };

  /*Retransmision Hi*/
  const struct ConstructorPropWInc ParRetHi={
    get_RetHi, set_RetHi, get_LimInf_RetHi, NULL,PropWInc,"REtH"
  };


  const struct ClassPropiedad *const AlProps[]={
    &ParHA,
    &ParAl,
    &ParTAlar1,
    &ParTAlar2,
    &ParRetLow,
    &ParRetHi,
  };
  

/*
** ===================================================================
**     Function      :  AlarmasHmi_ComuAdd 
**     Description :  Agrega la alarma a la comunicacion
** ===================================================================
*/

word AlarmasHmi_ComuAdd(const struct AlarmaMult * al,word dir_ini){
  word cant = sizeof(AlProps)/sizeof(struct ClassPropiedad *)-1;
  com_AddProps(AlProps,al,dir_ini,dir_ini+cant);
  return cant;
}


const struct BlockConstBoxPropBase CBox_ALVal;
const struct BlockConstBoxPropVarName CBox_H_AL;
const struct BlockConstBoxCondl CBox_TAL1;
const struct  BlockCnstrBoxLin CBox_RET;
const struct BlockConstBoxProp CBox_TAL2;
/*
** ===================================================================
**     Function    :  AlarmasHmi_AddBoxes 
**     Description :  Agrega la alarma a los boxes 
** ===================================================================
*/
#ifdef _PWM
extern const struct BlockConstBoxPropBase CBox_PeriodoAL;
#endif

void AlarmasHmi_AddBoxes(const struct AlarmaMult * al,uchar num_obj){
  DN_AddBox(0,"op",&CBox_ALVal,al,num_obj); 
//  #ifdef _PWM
//  DN_AddBox(0,"tun ",&CBox_PeriodoAL,al->salida,num_obj);
//  #endif
  DN_AddBox(0,"tun ",&CBox_H_AL,al,num_obj); 
  DN_AddBox(0,"Set ",&CBox_TAL1,al,num_obj);
}


/*Operador*/	
const struct BlockConstBoxPropBase CBox_ALVal=
      {
      BoxPropBase,						                  /* funcion que procesa al box*/
			&ParAl											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			};

/*  tun */
char * AlarmasHmi_getHDesc(struct PropWInc * prop){
  if(PropWInc_getValorTmp(prop)>0)
    return "AbA";
  return "HA";
}

const struct BlockConstBoxPropVarName CBox_H_AL=
      {
      BoxPropVarName,						                  /* funcion que procesa al box*/
			&ParHA,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
      NULL,
      AlarmasHmi_getHDesc  
			};
			
/*Set*/
void * Box_TAL1(void * prop,uchar tecla){
  if(tecla=='r'){
    if(_Getter_getVal(prop)==_RET)
      return &CBox_RET;
    return &CBox_TAL2;
  }
  return NULL;
}

const struct BlockConstBoxCondl CBox_TAL1=	{
  			  BoxCondl,
  			  &ParTAlar1,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
          Box_TAL1
};

const struct ConstructorPropWInc*const Props_RET[]=	{
  			  &ParRetLow,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
  			  &ParRetHi,
  			  NULL
};

const struct  BlockCnstrBoxLin CBox_RET={
  				BoxLineal,
  			  &Props_RET,
  			  &CBox_TAL2
};

const struct BlockConstBoxProp CBox_TAL2={
      BoxProp,
      &ParTAlar2,
			NULL
};

