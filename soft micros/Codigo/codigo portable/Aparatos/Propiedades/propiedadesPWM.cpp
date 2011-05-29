#include "propiedadesPWM.hpp"
#include "IPWM.hpp"
#include "stddef.h"

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
 const struct ConstructorPropiedadTextual cPropiedadPeriodoAlarma={
    &propiedadTextualFactory,getPeriodo,"PrA",setPeriodo,Periodos_getText,10
  };   
  
  //potencia
   /*
  ADAPTAR_FUNCION_GET(getPotenciaPWM,getPotencia)
  
  const struct ConstructorPropGetterNumerico cPropiedadGetPotencia={
    &propGetterNumericoFactory,getPotenciaPWM,"Pot",1
  };

  
  ADAPTAR_FUNCION_SET(setPotenciaPWM,setPotencia)
  
  const struct ConstructorPropNumLFPF cPropiedadPotencia={
    &propNumLFPFFactory,getPotenciaPWM,"Pot",setPotenciaPWM,0,1000,1
  };*/
