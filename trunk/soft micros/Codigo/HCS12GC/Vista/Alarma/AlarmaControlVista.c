/*MODULE: AlarmaDeSensorHmi
**     Filename  : AlarmaControlVista.C
**     Project   : Controlador
**     Processor : MC9S12GC32CFU16
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 11/09/2008, 10:47
*/
#include <stdlib.h>
#include "Math.h"
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
#include "sensor_adapt_val.h"

#include "com_events.h"

#include "AlarmaControl.h"

#include "AlarmaControlVista.h"

const char * const strsAdaptSalida[]={  
  "E   ",
  "d   ",
  "ErEt",
  "drEt",
  "dbLo"
};  //TAdaptador

  
typedef enum{
  REL,
  ABS,
  BAN,
  RET
}TAlVisual;

const char * const strsTAl[]={ 
  "rEL ",
  "AbS ",
  "bAn ",
//  "rEFr",
  "rEt "
};

#define TIPO_ALARMA_VISTA_MAX_VALOR 3


char * AlarmaControlVista_adaptSalidaMsj(byte msj){
  return strsAdaptSalida[msj]; 
}

char *AlarmaControlVista_tipoAlarmaMsj(byte msj){
  return strsTAl[msj];
}


byte  AlarmaControlVista_decimales(void * _alarmaControl){
  struct AlarmaControl *alarmaControl = _alarmaControl;
  
  struct Sensor * sensor = AlarmaControl_getSensor(_alarmaControl); 
  return _getDec(sensor);
}

int AlarmaControlVista_getTipoAlarma(void * _alarmaControl){
  if(AlarmaControl_getTipo(_alarmaControl) == ALARMA_RETRANSMISION)  
    return RET;
  switch(AlarmaControl_getControl(_alarmaControl)){
    case CONTROL_PROPORCIONAL: return ABS;
    case CONTROL_RELATIVO: return REL;
    case CONTROL_BANDA: return BAN;
  }
}

byte AlarmaControlVista_setTipoAlarma(void * _alarmaControl,int tal){
  if(tal==RET)  
    return AlarmaControl_setTipo(_alarmaControl,ALARMA_RETRANSMISION);
  else{
    
    byte err = AlarmaControl_setTipo(_alarmaControl,ALARMA_CONTROL);
    if(err)
      return err;
      
    switch(tal){
      case ABS: return AlarmaControl_setControl(_alarmaControl,CONTROL_PROPORCIONAL);
      case REL: return AlarmaControl_setControl(_alarmaControl,CONTROL_RELATIVO);
      case BAN: return AlarmaControl_setControl(_alarmaControl,CONTROL_BANDA);
    }
  }
}

int AlarmaControlVista_tipoAlarmaLimSup(void * _alarmaControl){
  return TIPO_ALARMA_VISTA_MAX_VALOR;  
}

/*Manejo de la histeresis*/
int AlarmaControlVista_getHisteresis(void * _alarmaControl){
  int h = AlarmaControl_getHisteresis(_alarmaControl);
  h= (AlarmaControl_getTipoSalida(_alarmaControl)==SALIDA_ONOFF)?-h:h;
  return adaptValOut(AlarmaControl_getSensor(_alarmaControl),h);
}

byte AlarmaControlVista_setHisteresis(void * _alarmaControl,int h){
  long his = adaptValInLong(AlarmaControl_getSensor(_alarmaControl),h);
  if(his>INT_MAX)  //cambiar : por limite de sensor en ParHA
    his = INT_MAX;
  h = his;
  if(h>0){
    AlarmaControl_setTipoSalida(_alarmaControl,SALIDA_PROPORCIONAL);
    return AlarmaControl_setHisteresis(_alarmaControl, h);
  }else{
    AlarmaControl_setTipoSalida(_alarmaControl,SALIDA_ONOFF);
    return AlarmaControl_setHisteresis(_alarmaControl,-h); 
  }
}

/* Adaptador Salida*/
byte AlarmaControlVista_setAdaptadorSalida(void * _alarmaControl,int adaptSalida){
  return AlarmaControl_setAdaptadorSalida(_alarmaControl,(byte)adaptSalida);  
}

int AlarmaControlVista_getAdaptadorSalida(void * _alarmaControl){
  return AlarmaControl_getAdaptadorSalida(_alarmaControl);
}

/* Valor Alarma*/
byte AlarmaControlVista_setValor(void * _alarmaControl,int val){
  val = adaptValIn(AlarmaControl_getSensor(_alarmaControl),val);
  return AlarmaControl_setValor(_alarmaControl,val);  
}

int AlarmaControlVista_getValor(void * _alarmaControl){
  int val = AlarmaControl_getValor(_alarmaControl);
  return adaptValOut(AlarmaControl_getSensor(_alarmaControl),val);
}

/* Limites sensor*/
int AlarmaControlVista_getLimSupAlarma(void * _alarmaControl){
  void * sensor = getSensor(_alarmaControl);
  return max(abs(_Sensor_getLimSup(sensor)),abs(_Sensor_getLimInf(sensor)));
}

int AlarmaControlVista_getLimInfAlarma(void * _alarmaControl){
  return -AlarmaControlVista_getLimSupAlarma(_alarmaControl);
}



/*****************************/
/********PROPIEDADES**********/
/*****************************/

  /*Histeresis*/
  const struct ConstPropNumPV ParHA={
    &PropiedadGenerica,AlarmaControlVista_getHisteresis, AlarmaControlVista_setHisteresis, NULL, NULL,&PropNumPV,"HA ",AlarmaControlVista_decimales
  };
  /*Valor de alarma*/
  const struct ConstPropNumPV ParAl={
    &PropiedadGenerica,AlarmaControlVista_getValor, AlarmaControlVista_setValor, NULL, NULL,&PropNumPV,"A  ",AlarmaControlVista_decimales
  };
  
  /*Tipo de Alarma o valor de control*/
    const struct ConstPropTxt ParTAlar={
    &PropiedadGenerica,AlarmaControlVista_getTipoAlarma, AlarmaControlVista_setTipoAlarma, get_0, AlarmaControlVista_tipoAlarmaLimSup,&PropTxt,"AL ",AlarmaControlVista_tipoAlarmaMsj
  };  
  
  /*Tipo de adaptadorSalida*/
    const struct ConstPropTxt ParAdaptSalida={
    &PropiedadGenerica,AlarmaControlVista_getAdaptadorSalida, AlarmaControlVista_setAdaptadorSalida, get_0, AlarmaControl_adaptSalidaLimSup,&PropTxt,"S.AL",AlarmaControlVista_adaptSalidaMsj
  };
    
  /*Retransmision Low*/
  const struct ConstPropNumPV ParRetLow={
    &PropiedadGenerica,Alarma_getRetLow, Alarma_setRetLow, NULL, Alarma_getRetHi,&PropNumPV,"r.L ",AlarmaControlVista_decimales
  };

  /*Retransmision Hi*/
  const struct ConstPropNumPV ParRetHi={
    &PropiedadGenerica,Alarma_getRetHi, Alarma_setRetHi, Alarma_getRetLow, NULL,&PropNumPV,"r.H ",AlarmaControlVista_decimales
  };


  const struct GetterGenerico *const alGetters[]={
    &ParHA,
    &ParAl,
    &ParAdaptSalida,
    &ParRetLow,
    &ParRetHi,
    &ParTAlar
  };
  
  const NEW_ARRAY(arrayAlarmaGetters,alGetters);
  

/*
** ===================================================================
**     Function      :  AlarmasHmi_ComuAdd 
**     Description :  Agrega la alarma a la comunicacion
** ===================================================================
*/

word AlarmaControlVista_ComuAdd(const struct AlarmaControl * al,word dir_ini){
  word cant = sizeof(alGetters)/sizeof(struct GetterGenerico *)-1;
  com_Add(alGetters,al,dir_ini,dir_ini+cant);
  return cant;
}


const struct BlockConstBoxPropBase CBox_AlarmaDeSensorVal;
const struct BlockConstBoxPropVarName CBox_H_AlarmaDeSensor;
const struct BlockConstBoxCondicional CBox_TAlarmaDeSensor1;

const struct BlockConstBoxPropBase CBox_AdaptSalida;
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
      &BoxPropBase,						                  /* funcion que procesa al box*/
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
      &BoxPropVarName,						  /* funcion que procesa al box*/
			&ParHA,											/* direccion en la E2Prom - el EEProm Start, if FAlarmaDeSensorSE no guarda valor*/
      NULL,
      AlarmasHmi_getHDesc  
			};
			
/*Set*/
void * Box_TAlarmaDeSensor1(void * prop,uchar tecla){
  if(tecla=='r'){
    if(_Getter_getVal(prop)==RET)
      return &CBox_RET;
    else
      return &CBox_AdaptSalida;  
  }
  return NULL;
}

const struct BlockConstBoxCondicional CBox_TAlarmaDeSensor1=	{
  			  &BoxCondicional,
  			  &ParTAlar,										
          Box_TAlarmaDeSensor1
};

const struct BlockConstBoxPropBase CBox_AdaptSalida=	{
  			  &BoxPropBase,
  			  &ParAdaptSalida										
};

const struct ConstructorPropWInc*const Props_RET[]=	{
  			  &ParRetLow,										
  			  &ParRetHi,
  			  NULL
};

const struct  BlockCnstrBoxLin CBox_RET={
  				&BoxLineal,
  			  &Props_RET,
  			  NULL
};

