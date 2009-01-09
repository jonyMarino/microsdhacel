/*  MODULE: SnsHmi.c (Sensores Human Machine interface)*/
#include "PropVisual.h"
#include "PropNumerica.h"
#include "PropNumPV.h"
#include "PropTextual.h"

#include "DiagramaNavegacion.h"
#include "ClassBoxLineal.h"
#include "BoxProp.h"
#include "BoxCondicional.h"
#include "DataBox.h"

#include "com_events.h"

#include "Sensores.h"
#include "SensorTPT_Class.h"

#include "SnsHmi.h"

#pragma MESSAGE DISABLE C1825          /* Disable warning C5703 "Parameter is not referenced" */



/*****************************/
/********PROPIEDADES**********/
/*****************************/

  /*Valor del Sensor*/
  const struct GetterGenerico GetterValSen={
    &GetterGenerico,SenTPT_getValue
  };
  
  /*Decimales*/
  extern int SenTPT_getDecimales(const struct TSensor_TermoPT * self);
  const struct GetterGenerico GetterDecimales={
    &GetterGenerico,SenTPT_getDecimales
  }; 
  
  
  /*Sensor*/ 

  const struct ConstPropTxt ParSensor={
    &PropiedadGenerica,get_Sensor,set_Sensor,get_LimInf_Sensores,get_LimSup_Sensores,&PropTxt,"SEn",SENSOR_getText
  };

  
  /*Decimales Mostrados*/
  extern int SenTPT_getDecimales(const struct TSensor_TermoPT * self);
  const struct ConstructorPropWInc ParDecimales= {
    &PropiedadGenerica,SenTPT_getDecimalesMostrados,SenTPT_setDecimales,get_0,get_LimSup_Decimales,&PropWInc,"dec "
  };

  /*Filtro*/
  const struct ConstPropNum ParFiltro={
    &PropiedadGenerica,get_filtro,set_filtro,get_LimInf_filtro,get_LimSup_filtro,&PropNum,"FiL",1
  };

  /*Offset*/
  const struct ConstPropNumPV ParOffset={
    &PropiedadGenerica,get_offset,set_offset,NULL,NULL,&PropNumPV,"oFS",SenTPT_getDecimalesMostrados
  };

  /*Gan1*/
  const struct ConstPropNum ParGanancia={
    &PropiedadGenerica,get_ganancia,set_ganancia,NULL,NULL,&PropNum,"gAn",3
  };

  /*Ajuste Cero Termopar */
  const struct ConstPropNumPV ParAjCeroT={
    &PropiedadGenerica,get_CeroTermopar,set_CeroTermopar,NULL,NULL,&PropNumPV,"AC ",SenTPT_getDecimalesMostrados
  };

  /*Ajuste Gan Termopar */
  const struct ConstPropNum ParAjGanT={
    &PropiedadGenerica,get_GananciaTermopar,set_GananciaTermopar,NULL,NULL,&PropNum,"Ag",1
  };

  /*Ajuste Cero PT100 */
  const struct ConstPropNumPV ParAjCeroPT={
    &PropiedadGenerica,get_CeroPT100,set_CeroPT100,NULL,NULL,&PropNumPV,"ACP",SenTPT_getDecimalesMostrados
  };

  /*Ajuste Gan PT100*/
  const struct ConstPropNum ParAjGanPT={
    &PropiedadGenerica,get_GananciaPT100,set_GananciaPT100,NULL,NULL,&PropNum,"AGP",3
  };

  /*Ajuste Temperatura Ambiente*/
  const struct ConstPropNum ParAjTempAmb={
    &PropiedadGenerica,get_AjTempAmb,set_AjTempAmb,NULL,NULL,&PropNum,"AtA ",1
  };
  
  const struct GetterGenerico *const SensProps[]={
    &ParSensor,
    &ParDecimales,
    &ParFiltro,
    &ParOffset,
    &ParGanancia,
    &ParAjCeroT,
    &ParAjGanT,
    &ParAjCeroPT,
    &ParAjGanPT,
    &ParAjTempAmb,
    &GetterValSen,
    &GetterDecimales
  };
  
  const NEW_ARRAY(arraySenGetters,SensProps);
  

  

/*
** ===================================================================
**     Function      :  SnsHmi_ComuAdd 
**     Description :  Agrega el sensor a la comunicacion
** ===================================================================
*/

word SnsHmi_ComuAdd(const struct TSensor_TermoPT * sensor,word dir_ini){
  word cant = sizeof(SensProps)/sizeof(struct ClassPropiedad *)-1;

  com_Add(SensProps,sensor,dir_ini,dir_ini+cant);
  return cant;
}
 /***********************/
 /****** BOXES  *********/
 /***********************/
const struct BlockCnstrBoxLin CBox_Sen1;
const struct BlockConstBoxCondicional CBox_Ganancia; 
const struct BlockCnstrBoxLin CBox_Sen2;
const struct BlockConstDataBox CBox_ATA;
const struct BlockConstBoxProp CBox_Filtro;
 
            
/*
** ===================================================================
**     Function      :  SnsHmi_Add 
**     Description :  Agrega a los boxes el sensor
** ===================================================================
*/

 void SnsHmi_Add(const struct TSensor_TermoPT * sensor,uchar num_obj){
  DN_AddBox(0,"CAL ",&CBox_Sen1,sensor,num_obj);
 }
 
 /*Test*/
 
 
/*  Sensor y Offset*/

const struct ConstructorPropWInc*const Props_Sen1[]=	{
  			  &ParSensor,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
  			  &ParOffset,
  			  NULL
};
const struct BlockCnstrBoxLin CBox_Sen1={
        &BoxLineal,						        /* funcion que procesa al box*/
  		  Props_Sen1,
  			(struct BlockBoxConstruct*)&CBox_Ganancia,						 //Proximos estados	
};
			
/* ganancia*/
void * Box_GananciaNext(void * prop,uchar tecla){
  if(tecla=='r')
    return &CBox_Filtro;
  else if(tecla=='f')
    return &CBox_Sen2;
  return NULL;
}
const struct BlockConstBoxCondicional CBox_Ganancia={
      &BoxCondicional,						 /* funcion que procesa al box*/      
			&ParGanancia,										 /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			Box_GananciaNext
};
		

/*ajuste cero canal 1*/
const struct ConstructorPropWInc*const Props_Sen2[]=	{
			  &ParAjCeroT,													/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			  &ParAjGanT,
			  &ParAjCeroPT,
			  &ParAjGanPT,
			  NULL
};
const struct BlockCnstrBoxLin CBox_Sen2={
      &BoxLineal,									/* funcion que procesa al box*/     
			Props_Sen2,
			&CBox_ATA
};			

		
/*ajuste temp ambiente*/		
const struct BlockConstDataBox CBox_ATA={
      &DataBox,									/* funcion que procesa al box*/
      &ParAjTempAmb,						/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			&CBox_Ganancia			//Proximos estados
};

const struct BlockConstBoxProp CBox_Filtro={
      &BoxProp,									/* funcion que procesa al box*/
      &ParFiltro,												
			NULL						//Proximos estados
}; 