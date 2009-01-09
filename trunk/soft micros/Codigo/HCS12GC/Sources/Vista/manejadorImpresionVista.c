/* MODULE: dateTimeVista.c*/
#include "PropWithInc.h"
#include "PropTextual.h"
#include "BoxPropBase.h"

#include "DiagramaNavegacion.h"
#include "ClassBoxLineal.h"

#include "com_events.h"

#include "ManejadorImpresion.h"

#include "manejadorImpresionVista.h"



/*****************************/
/********PROPIEDADES**********/
/*****************************/

  /*Intervalo*/
  static int get_5(void * a){
    return 5;
  }
  static const struct ConstructorPropWInc parIntervalo={
    &PropiedadGenerica,getIntervaloMI, setIntervaloMI, get_5, NULL,&PropWInc,"interVALo"
  };
  /*Habilitado*/
  int ManejadorImpresionVista_getHabilitado(void * _self){
    return getHabilitadoMI(_self);
  }
  byte ManejadorImpresionVista_setHabilitado(void * _self,int habilitar){
    setHabilitadoMI(_self,habilitar);
    return ERR_OK;
  }  
  int getLimSupHabilitado(void * _self){
    return 1;
  }
  char * getHabilitadoTxt(int val){
    static const char * str[2]={
      "no",
      "Si"
    };
    return str[val];
  }
  static const struct ConstPropTxt parHabilitado={
    &PropiedadGenerica,ManejadorImpresionVista_getHabilitado,ManejadorImpresionVista_setHabilitado,get_0,getLimSupHabilitado,&PropTxt,"ImPriMir",getHabilitadoTxt
  };
  
  
  const struct GetterGenerico *const manejadorImpresionVistaProps[]={
    &parIntervalo,
    &parHabilitado 
  };
/*
** ===================================================================
**     Function      :  DateTimeVista_comuAdd 
**     Description :  Agrega la variable tipo DateTime a la comunicacion
** ===================================================================
*/

word manejadorImpresionVista_comuAdd(const struct TmDt1 * adq,word dir_ini){
  word cant = sizeof(manejadorImpresionVistaProps)/sizeof(struct GetterGenerico *)-1;

  com_Add(manejadorImpresionVistaProps,adq,dir_ini,dir_ini+cant);

  return cant;
}

/*Boxes*/

const struct BlockConstBoxPropBase cBoxManejadorImpresionIntervalo={
      &BoxPropBase,
      &parIntervalo
			};

const struct BlockConstBoxPropBase cBoxManejadorImpresionHabilitado={
      &BoxPropBase,
      &parHabilitado
			};

