#include "PropGetterVisual.hpp"
#include "PropiedadNumerica.hpp"
#include "PropNumLFPV.hpp"
#include "PropNumLFPF.hpp"
#include "PropNumLVPF.hpp"
#include "PropiedadTextual.hpp"
#include "PropGetterNumerico.hpp"
#include "BoxLineal.hpp"
#include "BoxSaltoCondicional.hpp"
#include "BoxPropiedadEntradaCondicional.hpp"
#include "BoxLinealCondicional.hpp"
#include "PropDescripcionVariable.hpp"
#include "PropDescripcionVariablePV.hpp"
#include "CoordinadorControladorSintonizador.hpp"


#define ADAPTAR_FUNCION_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return ((CoordinadorControladorSintonizador*)conf)->METODO(); \
  }
  
#define ADAPTAR_FUNCION_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    ((CoordinadorControladorSintonizador*)conf)->METODO(valor); \
  }   
  
  
 /*****************************/
/********PROPIEDADES**********/
/*****************************/
 //Modos
  const char * const Modos[2]={
      "off ",	//controlPID								
			"on  ", //AutoSintonia
			
  };



  const char * Modos_getText(byte Modo){
    return Modos[Modo];
  }   

 
  ADAPTAR_FUNCION_GET(getModo,getModo)
  ADAPTAR_FUNCION_SET(setModo,setModo)

  const struct ConstructorPropiedadTextual cPropiedadModos={
    &propiedadTextualFactory,getModo,"St",setModo,Modos_getText,2
  };
  
  /***********************/
 /****** BOXES  *********/
 
const struct ConstructorBoxPropiedad cBoxModos={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadModos
}; 
