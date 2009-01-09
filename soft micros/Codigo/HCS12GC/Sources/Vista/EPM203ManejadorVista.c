/* MODULE: dateTimeVista.c*/
#include "PropWithInc.h"
#include "PropTextual.h"
#include "BoxPropBase.h"

#include "DiagramaNavegacion.h"
#include "ClassBoxLineal.h"

#include "com_events.h"

#include "EPM203Manejador.h"

#include "EPM203ManejadorVista.h"


#define ADAPTAR_BYTE_A_INT_GET(f) \
  int f##Vista(void * obj){       \
    return f(obj);                \
  }

#define ADAPTAR_BYTE_A_INT_SET(f) \
  byte f##Vista(void * obj,int val){       \
    return f(obj,val);                \
  }  
/*****************************/
/********PROPIEDADES**********/
/*****************************/

  /*Fuente*/
  
  ADAPTAR_BYTE_A_INT_GET(EPM203Manejador_getFuente)
  ADAPTAR_BYTE_A_INT_SET(EPM203Manejador_setFuenteAndConfig)
  int get_2(void * a){
    return 2;
  }
  static char * getFuenteTxt(int val){
    static const char * str[3]={
      "8.16",
      "12.20",
      "7.16"
    };
    return str[val];
  }
  static const struct ConstPropTxt parFuente={
    &PropiedadGenerica,EPM203Manejador_getFuenteVista, EPM203Manejador_setFuenteAndConfigVista, get_0, get_2,&PropTxt,"FuEntE",getFuenteTxt
  };
  /*Direccion*/
  ADAPTAR_BYTE_A_INT_GET(EPM203Manejador_getDireccion)
  ADAPTAR_BYTE_A_INT_SET(EPM203Manejador_setDireccionAndConfig)
    
  int getLimSupDireccion(void * _self){
    return 1;
  }
    static char * getDireccionTxt(int val){
    static const char * str[]={
      "dir",
      "inv"
    };
    return str[val];
  }
  static const struct ConstPropTxt parDireccion={
    &PropiedadGenerica,EPM203Manejador_getDireccionVista,EPM203Manejador_setDireccionAndConfigVista,get_0,getLimSupDireccion,&PropTxt,"dirEccion",getDireccionTxt
  };
  
  
  const struct GetterGenerico *const manejadorEPM203VistaProps[]={
    &parFuente,
    &parDireccion 
  };
/*
** ===================================================================
**     Function      :  DateTimeVista_comuAdd 
**     Description :  Agrega la variable tipo DateTime a la comunicacion
** ===================================================================
*/

word manejadorEPM203Vista_comuAdd(const struct TmDt1 * adq,word dir_ini){
  word cant = sizeof(manejadorEPM203VistaProps)/sizeof(struct GetterGenerico *)-1;

  com_Add(manejadorEPM203VistaProps,adq,dir_ini,dir_ini+cant);

  return cant;
}

/*Boxes*/

const struct ConstructorPropWInc*const propsManejadorEPM203[]=	{
  			  &parFuente,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
  			  &parDireccion,
  			  NULL
};

const struct BlockCnstrBoxLin  cBoxesManejadorEPM203={
      &BoxLineal,
      &propsManejadorEPM203,
      NULL
			};

