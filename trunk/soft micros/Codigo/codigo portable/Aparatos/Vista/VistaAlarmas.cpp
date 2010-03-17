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
#include "VistaSetContrasenia.hpp"
#include "VistaControl.hpp"

#pragma MESSAGE DISABLE C1825          /* Disable warning C5703 "Parameter is not referenced" */

#define ADAPTAR_FUNCION_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return ((AlarmaControl&)((CoordinadorLazosAlCntrRet*)conf)->getAlarmaControl()).METODO(); \
  }
  
#define ADAPTAR_FUNCION_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    ((AlarmaControl&)((CoordinadorLazosAlCntrRet*)conf)->getAlarmaControl()).METODO(valor); \
  }   


#define ADAPTAR_FUNCION_RET_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return ((Retransmision&)((CoordinadorLazosAlCntrRet*)conf)->getRetransmision()).METODO(); \
  }
  
#define ADAPTAR_FUNCION_RET_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    ((Retransmision&)((CoordinadorLazosAlCntrRet*)conf)->getRetransmision()).METODO(valor); \
  }   

  
#define ADAPTAR_FUNCION_LAZO_ALARMAS_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return ((CoordinadorLazosAlCntrRet*)conf)->METODO(); \
  }
  
#define ADAPTAR_FUNCION_LAZO_ALARMAS_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    ((CoordinadorLazosAlCntrRet*)conf)->METODO(valor); \
  }         
 

#define ADAPTAR_FUNCION_ADAP_SAL_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return (*(AdaptadorSalida*)&(*(LazoControl*)&(((CoordinadorLazosAlCntrRet*)conf)->getAlarmaControl())).getAdaptadorSalida()).METODO(); \
  }
  
#define ADAPTAR_FUNCION_ADAP_SAL_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    (*(AdaptadorSalida*)&(*(LazoControl*)&(((CoordinadorLazosAlCntrRet*)conf)->getAlarmaControl())).getAdaptadorSalida()).METODO(valor); \
  }   
  

#define ADAPTAR_FUNCION_VAL_CONTROL_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return (*(ValorControl*)&(*(LazoControl*)&(((CoordinadorLazosAlCntrRet*)conf)->getAlarmaControl())).getValorControl()).METODO(); \
  }
  
#define ADAPTAR_FUNCION_VAL_CONTROL_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    (*(ValorControl*)&(*(LazoControl*)&(((CoordinadorLazosAlCntrRet*)conf)->getAlarmaControl())).getValorControl()).METODO(valor); \
  }           
  


uchar getDecimalesAlarma(void*alarma){           
  Sensor * s= &(*(ValorControl*)&(*(LazoControl*)&(((CoordinadorLazosAlCntrRet*)alarma)->getAlarmaControl())).getValorControl()).getSensor();
  return s->getDecimales();
}

/*****************************/
/********PROPIEDADES**********/
/*****************************/
  
  
  //A
  const char * const modosAlarma[5]={
      "ErEt",
      "drEt",
      "dbLK",
      "d",
      "E"											
  };


  const char * ms_getText_a(byte modo){
    return modosAlarma[modo];
  }   

 
  ADAPTAR_FUNCION_GET(getAdaptadorSalidaAlam,getAdaptadorSalidaAlarm)
  ADAPTAR_FUNCION_SET(setAdaptadorSalidaAlam,setAdaptadorSalidaAlarm)

  const struct ConstructorPropiedadTextual cPropiedadModoAlarma={
    &propiedadTextualFactory,getAdaptadorSalidaAlam,"A",setAdaptadorSalidaAlam,ms_getText_a,5
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
  
  //Funcion de alarma
  const char * const funcAlarma[2]={
      "ALm",
      "rEt",											
  };


  const char * ms_getText_f(byte modo){
    return funcAlarma[modo];
  }   

   
  ADAPTAR_FUNCION_LAZO_ALARMAS_GET(getLazo,getLazo)
  ADAPTAR_FUNCION_LAZO_ALARMAS_SET(setLazo,setLazo)

  const struct ConstructorPropiedadTextual cPropiedadTipoLazo={
    &propiedadTextualFactory,getLazo,"FA",setLazo,ms_getText_f,2
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
uchar nextSetPropA (void * obj){
  
  if(((CoordinadorLazosAlCntrRet*)obj)->getLazo() != RETRANSMISION)
    return 0;  // posicion de cPropiedadGetPotencia en el la tabla propsPot
  else
    return 3;  
}
 


const struct ConstructorPropGetterVisual*const propsConfiguracion[]=	{
			  (const struct ConstructorPropGetterVisual*)&cPropiedadModoAlarma,
  			(const struct ConstructorPropGetterVisual*)&cPropiedadTipoCtrlAlarma,
			  NULL,
			  NULL
};

const struct ConstructorBoxLinealCondicional cBoxesAlarma={
        &boxLinealCondicionalFactory,						       
  		  propsConfiguracion,
  		  NULL,						 //Proximo box	
        nextSetPropA
};


const struct ConstructorPropGetterVisual *const propRet[]=	{
  			  NULL,
  			  NULL,
  			  NULL,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadRetLimInf,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadRetLimSup,
  			  NULL
};

const struct ConstructorBoxLinealCondicional cBoxesRetransmision={
        &boxLinealCondicionalFactory,						       
  		  propRet,
  		  NULL,						 //Proximo box
  		  nextSetPropA	
};


const struct ConstructorPropGetterVisual *const propHis[]=	{
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadHistAlarma,
  			  NULL,
  			  NULL,
  			  NULL,
};
const struct ConstructorBoxLinealCondicional cBoxesHistAlarma={
      &boxLinealCondicionalFactory,						       
  		  propHis,
  		  NULL,						 //Proximo box
  		  nextSetPropA	
}; 
  
const struct ConstructorBoxPropiedad cBoxesTipoSalAlarma={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadTipoSalida
};


const struct ConstructorPropGetterVisual *const propSp[]=	{
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadSetPointAlarma,
  			  NULL,
  			  NULL,
  			  NULL
};
  
const struct ConstructorBoxLinealCondicional cBoxesSetPointAlarma={
      &boxLinealCondicionalFactory,						       
  		  propSp,
  		  NULL,						 //Proximo box
  		  nextSetPropA
};