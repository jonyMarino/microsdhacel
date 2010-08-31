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
#include "ControlPID.hpp"
#include "VistaPWM.hpp"
#include "VistaControl.hpp"
#include "SensorTermoPT100.hpp"
#include "PropGetterNumericoPV.hpp"
#include "ControlVF.hpp"
#include "VistaControlVF.hpp"


#pragma MESSAGE DISABLE C1825          /* Disable warning C5703 "Parameter is not referenced" */


#define ADAPTAR_FUNCION_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return ((ControlVF*)conf)->METODO(); \
  }
  
#define ADAPTAR_FUNCION_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    ((ControlVF*)conf)->METODO(valor); \
  }   


/*****************************/
/********PROPIEDADES**********/
/*****************************/

  // Etapas
  ADAPTAR_FUNCION_GET(getCantidadDeEtapas,getCantidadDeEtapas)
  ADAPTAR_FUNCION_SET(setCantidadDeEtapas,setCantidadDeEtapas)
  const struct ConstructorPropNumLFPF cPropiedadEtapas={
    &propNumLFPFFactory,getCantidadDeEtapas,"EtAPAS",setCantidadDeEtapas,1,10,0
  };

 
 /***********************/
 /****** BOXES  *********/
 


const struct ConstructorBoxPropiedad cBoxesEtapas={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadEtapas
};  

