/*  MODULE: SnsHmi.c (Sensores Human Machine interface)*/
#include "PropGetterVisual.hpp"
#include "PropiedadNumerica.hpp"
#include "PropNumLFPV.hpp"
#include "PropNumLFPF.hpp"
#include "PropiedadTextual.hpp"

#include "BoxLineal.hpp"
#include "BoxSaltoCondicional.hpp"
#include "PropDescripcionVariable.hpp"
//#include "BoxProp.h"
//#include "DataBox.h"

//#include "com_events.h"

//#include "Sensores.h"
#include "ControlPID.hpp"

#include "VistaControl.hpp"

#pragma MESSAGE DISABLE C1825          /* Disable warning C5703 "Parameter is not referenced" */

#define ADAPTAR_FUNCION_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return ((ControlPID*)conf)->METODO(); \
  }
  
#define ADAPTAR_FUNCION_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    ((ControlPID*)conf)->METODO(valor); \
  }   


/*****************************/
/********PROPIEDADES**********/
/*****************************/


  //Reset
  ADAPTAR_FUNCION_GET(getReset,getReset)
  ADAPTAR_FUNCION_SET(setReset,setReset)
  const struct ConstructorPropNumLFPF cPropiedadReset={
    &propNumLFPFFactory,getReset,"rES",setReset,-9999,9999,1
  };

  //Histeresis
  ADAPTAR_FUNCION_GET(getHisteresis,getHisteresis)
  ADAPTAR_FUNCION_SET(setHisteresis,setHisteresis)
  
  const char * histeresisVista(PropGetterVisual * prop){    
    int valObj=prop->getVal();
    
    if(valObj<0)
      return "H  ";
    return "Ab ";    
}
  
  const struct ConstructorPropDescripcionVariable cPropiedadHisteresis={
    &propDescripcionVariableFactory,getHisteresis,"H  ",setHisteresis,-9999,9999,1,histeresisVista
  };
    
  
  //Integral
  ADAPTAR_FUNCION_GET(getIntegral,getIntegral)
  ADAPTAR_FUNCION_SET(setIntegral,setIntegral)
  const struct ConstructorPropNumLFPF cPropiedadIntegral={
    &propNumLFPFFactory,getIntegral,"in ",setIntegral,-9999,9999,1
  };

  //Derivada
  ADAPTAR_FUNCION_GET(getDerivada,getDerivada)
  ADAPTAR_FUNCION_SET(setDerivada,setDerivada)
  const struct ConstructorPropNumLFPF cPropiedadDerivada={
    &propNumLFPFFactory,getDerivada,"dr",setDerivada,0,9999,1
  };

 /***********************/
 /****** BOXES  *********/
 
  

const struct ConstructorPropGetterVisual *const propSintonia[]=	{
  			  //(const struct ConstructorPropGetterVisual*)&cPropiedadReset,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadHisteresis,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadIntegral,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadDerivada,
  			  NULL
};

const struct ConstructorBoxLineal cBoxesSintonia={
        &boxLinealFactory,						       
  		  propSintonia,
  		  NULL						 //Proximo box	
};


const struct ConstructorBoxPropiedad cBoxesReset={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadReset
}; 
