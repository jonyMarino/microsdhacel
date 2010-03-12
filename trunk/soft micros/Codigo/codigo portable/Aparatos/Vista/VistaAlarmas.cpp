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
#include "AlarmaControl.hpp"
#include "ValorControl.hpp"
#include "Retransmision.hpp"
#include "CoordinadorLazosAlCntrRet.hpp"
#include "VistaAlarmas.hpp"

#pragma MESSAGE DISABLE C1825          /* Disable warning C5703 "Parameter is not referenced" */

#define ADAPTAR_FUNCION_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return ((AlarmaControl*)conf)->METODO(); \
  }
  
#define ADAPTAR_FUNCION_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    ((AlarmaControl*)conf)->METODO(valor); \
  }   

#define ADAPTAR_FUNCION_RET_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return ((Retransmision*)conf)->METODO(); \
  }
  
#define ADAPTAR_FUNCION_RET_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    ((Retransmision*)conf)->METODO(valor); \
  }   
  
#define ADAPTAR_FUNCION_ADAP_SAL_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return ((AdaptadorSalida*)conf)->METODO(); \
  }
  
#define ADAPTAR_FUNCION_ADAP_SAL_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    ((AdaptadorSalida*)conf)->METODO(valor); \
  } 
  
#define ADAPTAR_FUNCION_VAL_CONTROL_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return ((ValorControl*)conf)->METODO(); \
  }
  
#define ADAPTAR_FUNCION_VAL_CONTROL_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    ((ValorControl*)conf)->METODO(valor); \
  }           


uchar getDecimalesAlarma(void*alarma){           
  Sensor * s= &((ValorControl*)alarma)->getSensor();
  return s->getDecimales();
}

/*****************************/
/********PROPIEDADES**********/
/*****************************/


  //A
  const char * const modosAlarma[5]={
      "rEtn",
      "drEt",
      "dbLK",
      "d",
      "e"											
  };


  const char * ms_getText_a(byte modo){
    return modosAlarma[modo];
  }   

 
  ADAPTAR_FUNCION_GET(getAdaptadorSalida,getAdaptadorSalida)
  ADAPTAR_FUNCION_SET(setAdaptadorSalida,setAdaptadorSalida)

  const struct ConstructorPropiedadTextual cPropiedadModoAlarma={
    &propiedadTextualFactory,getAdaptadorSalida,"A",setAdaptadorSalida,ms_getText_a,5
  };

  //AL
  const char * const tipoCtrlAlarma[3]={
      "AbS",
      "rEL",
      "bAn",											
  };


  const char * ms_getText_b(byte modo){
    return tipoCtrlAlarma[modo];
  }   

 
  ADAPTAR_FUNCION_GET(getTipoControl,getTipoControl)
  ADAPTAR_FUNCION_SET(setTipoControl,setTipoControl)

  const struct ConstructorPropiedadTextual cPropiedadTipoCtrlAlarma={
    &propiedadTextualFactory,getTipoControl,"AL",setTipoControl,ms_getText_b,3
  };
  
  //retransmision
 //limite inferior
  ADAPTAR_FUNCION_RET_GET(getLimiteInferior,getLimiteInferior)
  ADAPTAR_FUNCION_RET_SET(setLimiteInferior,setLimiteInferior)
  const struct ConstructorPropNumLFPF cPropiedadRetLimInf={
    &propNumLFPFFactory,getLimiteInferior,"AnL",setLimiteInferior,0,9999,0
  };
  
 //limite superior
  ADAPTAR_FUNCION_RET_GET(getLimiteSuperior,getLimiteSuperior)
  ADAPTAR_FUNCION_RET_SET(setLimiteSuperior,setLimiteSuperior)
  const struct ConstructorPropNumLFPF cPropiedadRetLimSup={
    &propNumLFPFFactory,getLimiteSuperior,"AnH",setLimiteSuperior,0,9999,0
  };
  
  //Histeresis de Alarma
  ADAPTAR_FUNCION_ADAP_SAL_GET(getHisteresisAlarma,getHisteresis)
  ADAPTAR_FUNCION_ADAP_SAL_SET(setHisteresisAlarma,setHisteresis)
  const struct ConstructorPropNumLFPF cPropiedadHistAlarma={
    &propNumLFPFFactory,getHisteresisAlarma,"HA",setHisteresisAlarma,-9999,9999,0
  };
  
  //tipo salida
  const char * const tipoSalida[2]={
      "onoff",
      "ProP",											
  };


  const char * ms_getText_c(byte modo){
    return tipoSalida[modo];
  }   

  
  ADAPTAR_FUNCION_ADAP_SAL_GET(getTipoSalida,getTipoSalida)
  ADAPTAR_FUNCION_ADAP_SAL_SET(setTipoSalida,setTipoSalida)
   const struct ConstructorPropiedadTextual cPropiedadTipoSalida={
    &propiedadTextualFactory,getTipoSalida,"AL",setTipoSalida,ms_getText_c,2
  };
  
  //SetPoint de Alarma
  ADAPTAR_FUNCION_VAL_CONTROL_GET(getValorControlador,getValorControlador)
  ADAPTAR_FUNCION_VAL_CONTROL_SET(setValorControlador,setValorControlador)
   const struct ConstructorPropNumLFPV cPropiedadSetPointAlarma={
    &propNumLFPVFactory,getValorControlador,"A",setValorControlador,-9999,9999,getDecimalesAlarma 
  };
  
  
 /***********************/
 /****** BOXES  *********/
 
  

const struct ConstructorPropGetterVisual *const propAlarma[]=	{
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadModoAlarma,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadTipoCtrlAlarma,
  			  NULL
};

const struct ConstructorBoxLineal cBoxesAlarma={
        &boxLinealFactory,						       
  		  propAlarma,
  		  NULL						 //Proximo box	
};


const struct ConstructorPropGetterVisual *const propRet[]=	{
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadRetLimInf,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadRetLimSup,
  			  NULL
};

const struct ConstructorBoxLineal cBoxesRetransmision={
        &boxLinealFactory,						       
  		  propRet,
  		  NULL						 //Proximo box	
};



const struct ConstructorBoxPropiedad cBoxesHistAlarma={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadHistAlarma
}; 
 
const struct ConstructorBoxPropiedad cBoxesTipoSalAlarma={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadTipoSalida
};

const struct ConstructorBoxPropiedad cBoxesSetPointAlarma={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadSetPointAlarma
};