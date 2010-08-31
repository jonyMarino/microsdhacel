#include "PropGetterVisual.hpp"
#include "PropiedadNumerica.hpp"
#include "PropGetterVisualVF.hpp"
#include "PropiedadNumericaVF.hpp"
#include "PropNumLFPV.hpp"
#include "PropNumLFPF.hpp"
#include "PropNumLVPF.hpp"
#include "PropNumVFLFPF.hpp"
#include "PropiedadTextual.hpp"
#include "PropGetterNumerico.hpp"
#include "BoxPropiedadVF.hpp"
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

#define ADAPTAR_FUNCION_VF_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf,int nro){           \
    return ((ControlVF*)conf)->METODO(nro); \
  }
  
#define ADAPTAR_FUNCION_VF_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int nro,int valor){           \
    ((ControlVF*)conf)->METODO(nro,valor); \
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

  // Vel
  ADAPTAR_FUNCION_VF_GET(getVelDeEtapa,getVelDeEtapa)
  ADAPTAR_FUNCION_VF_SET(setVelDeEtapa,setVelDeEtapa)
  const struct ConstructorPropNumVFLFPF cPropiedadVel1={
    &propNumVFLFPFFactory,getVelDeEtapa,"VEL"," <C/HorA",setVelDeEtapa,0,9999,1
  };
 /***********************/
 /****** BOXES  *********/
 


const struct ConstructorBoxPropiedad cBoxesEtapas={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadEtapas
};  

 const struct ConstructorBoxPropiedadVF cBoxesVel1={
      &boxPropiedadVFFactory,	
			(const struct ConstructorPropGetterVisualVF*)&cPropiedadVel1
};  
