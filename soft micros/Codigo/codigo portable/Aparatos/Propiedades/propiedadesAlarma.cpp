#include "propiedadesAlarma.hpp"
#include "AlarmaControl.hpp"
#include "ValorControl.hpp"
#include "Retransmision.hpp"
#include "CoordinadorLazosAlCntrRet.hpp"
#include "configuracionValorControl.hpp"
#include "configuracionAlarmas.hpp"
#include "ConfiguracionAdapSalida.hpp"

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
  
#define ADAPTAR_FUNCION_VAL_CONTROL_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return (*(ValorControl*)&(*(LazoControl*)&(((CoordinadorLazosAlCntrRet*)conf)->getAlarmaControl())).getValorControl()).METODO(); \
  }
  
#define ADAPTAR_FUNCION_VAL_CONTROL_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
   (*(ConfiguracionValorControlado*)&((*(ValorControl*)&(*(LazoControl*)&(((CoordinadorLazosAlCntrRet*)conf)->getAlarmaControl()))).getConfiguracion())).METODO(valor); \
  }           
  
void setValorControladorAl(void * alarma,int valor){
  
  ValorControl * v= &(*(ValorControl*)&(*(LazoControl*)&(((CoordinadorLazosAlCntrRet*)alarma)->getAlarmaControl())).getValorControl());    
  (*(ConfiguracionValorControlado*)&(v->getConfiguracion())).setValorControlador(valor);
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
    &propiedadTextualFactory,getLazo,"LA",setLazo,ms_getText_f,2
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
  
 void setHisteresisAlarma(void*conf,int valor){           
    const AdaptadorSalidaConfiguracion& config = (*(AdaptadorSalida*)&(*(LazoControl*)&(((CoordinadorLazosAlCntrRet*)conf)->getAlarmaControl())).getAdaptadorSalida()).getConfiguracion();
    ((ConfiguracionAdapSalida*)&config)->setHisteresis(valor);
 }
  
  const char * histeresisAlarmaVista(PropGetterVisual * prop){    
    int valObj=prop->getVal();
    
    if(valObj<0)
      return "HA ";
    return "AbA";    
}
  
  const struct ConstructorPropDescripcionVariablePV cPropiedadHistAlarma={
    &propDescripcionVariablePVFactory,getHisteresisAlarma,"HA",setHisteresisAlarma,-9999,9999,getDecimalesAlarma,histeresisAlarmaVista
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
  
   void setTipoSalida(void*conf,int valor){           
      const AdaptadorSalidaConfiguracion& config = (*(AdaptadorSalida*)&(*(LazoControl*)&(((CoordinadorLazosAlCntrRet*)conf)->getAlarmaControl())).getAdaptadorSalida()).getConfiguracion();
      ((ConfiguracionAdapSalida*)&config)->setTipoSalida(valor);
   }
   
   const struct ConstructorPropiedadTextual cPropiedadTipoSalida={
    &propiedadTextualFactory,getTipoSalida,"AL",setTipoSalida,ms_getText_c,2
  };
   
  //SetPoint de Alarma
  ADAPTAR_FUNCION_VAL_CONTROL_GET(getValorControlador,getValorControlador)
  //ADAPTAR_FUNCION_VAL_CONTROL_SET(setValorControlador,setValorControlador)
   const struct ConstructorPropNumLFPV cPropiedadSetPointAlarma={
    &propNumLFPVFactory,getValorControlador,"A",setValorControladorAl,-9999,9999,getDecimalesAlarma 
  };
