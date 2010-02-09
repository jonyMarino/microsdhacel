#include "PropGetterVisual.hpp"
#include "PropiedadNumerica.hpp"
#include "PropNumLFPV.hpp"
#include "PropNumLFPF.hpp"
#include "PropiedadTextual.hpp"
#include "PropGetterNumerico.hpp"
#include "BoxLineal.hpp"
#include "BoxSaltoCondicional.hpp"
#include "PropDescripcionVariable.hpp"
#include "BoxLinealCondicional.hpp"
#include "stddef.h"
#include "ControlPID.hpp"
#include "IPWM.hpp"
#include "VistaPWM.hpp"

#pragma MESSAGE DISABLE C1825          /* Disable warning C5703 "Parameter is not referenced" */

#define ADAPTAR_FUNCION_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return ((IPWM*)conf)->METODO(); \
  }
  
#define ADAPTAR_FUNCION_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    ((IPWM*)conf)->METODO(valor); \
  }   


/*****************************/
/********PROPIEDADES**********/
/*****************************/

  //Periodo
  const char * const Periodos[10]={
      ".1  ",									
			".2  ",
			".5  ",
			"1   ",
			"2   ",
			"5   ",
			"10  ",
			"20  ",
			"50  ",
			"AnL ",
  };



  const char * Periodos_getText(byte periodo){
    return Periodos[periodo];
  }   

 
  ADAPTAR_FUNCION_GET(getPeriodo,getPeriodo)
  ADAPTAR_FUNCION_SET(setPeriodo,setPeriodo)

  const struct ConstructorPropiedadTextual cPropiedadPeriodo={
    &propiedadTextualFactory,getPeriodo,"Pr",setPeriodo,Periodos_getText,10
  };
    
  
  //potencia
   
  ADAPTAR_FUNCION_GET(getPotenciaPWM,getPotencia)
  
  const struct ConstructorPropGetterNumerico cPropiedadGetPotencia={
    &propGetterNumericoFactory,getPotenciaPWM,"Pot",1
  };

  
  ADAPTAR_FUNCION_SET(setPotenciaPWM,setPotencia)
  
  const struct ConstructorPropNumLFPF cPropiedadPotencia={
    &propNumLFPFFactory,getPotenciaPWM,"Pot",setPotenciaPWM,0,1000,1
  };
  
 /***********************/
 /****** BOXES  *********/
 
const struct ConstructorBoxPropiedad cBoxPeriodo={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadPeriodo
}; 
 
/*
uchar nextSetProp (void * obj){
  
  if(((ControlPID*)obj)->getModoSalida() != ControlPID::_MAN)
    return 0;  // posicion de cPropiedadGetPotencia en el la tabla propsPot
  else
    return 2;  
}

const struct ConstructorPropGetterVisual*const propsPot[]=	{
			  (const struct ConstructorPropGetterVisual*)&cPropiedadGetPotencia,
			  NULL
};
const struct ConstructorBoxLinealCondicional cBoxPot={
      &boxLinealCondicionalFactory,								
			propsPot,
			NULL,
			nextSetProp
};	

 */
 const struct ConstructorBoxPropiedad cBoxGetPotencia={
      &boxPropGetterFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadGetPotencia
}; 
 
 
const struct ConstructorBoxPropiedad cBoxPotencia={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadPotencia
};
 
  
