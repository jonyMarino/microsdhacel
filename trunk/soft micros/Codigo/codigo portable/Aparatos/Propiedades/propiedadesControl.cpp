#include "comunicacionControl.hpp"
#include "ControlPID.hpp"
#include "SensorTermoPT100.hpp"
#include "CoordinadorControladorSintonizador.hpp"
#include "AutoSintonia.hpp"

#pragma MESSAGE DISABLE C1825          /* Disable warning C5703 "Parameter is not referenced" */


#define ADAPTAR_FUNCION_GET(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return ((ControlPID*)conf)->METODO(); \
  }
  
#define ADAPTAR_FUNCION_SET(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    ((ControlPID*)conf)->METODO(valor); \
  }   

#define ADAPTAR_FUNCION_GET_CONTROL(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return ((ControlPID*)(((CoordinadorControladorSintonizador*)conf)->getControl()))->METODO(); \
  }
  
#define ADAPTAR_FUNCION_SET_CONTROL(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    ((ControlPID*)(((CoordinadorControladorSintonizador*)conf)->getControl()))->METODO(valor); \
  }   

#define ADAPTAR_FUNCION_GET_AUTOSINTONIA(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return ((AutoSintonia*)(((CoordinadorControladorSintonizador*)conf)->getAutoSintonia()))->METODO(); \
  }
  
#define ADAPTAR_FUNCION_SET_AUTOSINTONIA(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    ((AutoSintonia*)(((CoordinadorControladorSintonizador*)conf)->getAutoSintonia()))->METODO(valor); \
  }   


#define ADAPTAR_FUNCION_GET_AUTS(NOMBRE,METODO)\
    int NOMBRE(void*conf){           \
    return ((CoordinadorControladorSintonizador*)conf)->METODO(); \
  }
  
#define ADAPTAR_FUNCION_SET_AUTS(NOMBRE,METODO)      \
  void NOMBRE(void*conf,int valor){           \
    ((CoordinadorControladorSintonizador*)conf)->METODO(valor); \
  }   
  
uchar getDecimalesAutoSintonia(void*control){           
  return (uchar)(((AutoSintonia*)(((CoordinadorControladorSintonizador*)control)->getAutoSintonia()))->getDecimales());
} 

uchar getDecimalesControl(void*control){           
  return ((ControlPID*)control)->getDecimales();
}

int getLimiteInfPotManual(void*control){           
  return ((ControlPID*)control)->getLimiteInferiorPotenciaManual();
}

int getLimiteSupPotManual(void*control){           
  return ((ControlPID*)control)->getLimiteSuperiorPotenciaManual();
}

 int getPotencia (void * control){
   return ((ControlPID*)control)->getSalida().getPotencia();
}



uchar nextLimProp (void * obj){
  if(((CoordinadorControladorSintonizador*)obj)->getModo() == AUTOSINTONIA)
    return 0;
  else
    return 5;
}

/*uchar nextSetProp (void * obj){
  if(((CoordinadorControladorSintonizador*)obj)->getModo() == AUTOSINTONIA)
    return 4;
  else if(((ControlPID*)obj)->getModoSalida() != ControlPID::_MAN)
    return 0;  // posicion de cPropiedadGetPotencia en el la tabla propsPot
  else
    return 2;  
}*/

int getVal_ (void * control){
  
  return(((ControlPID*)control)->getSensor()).getVal();
}


/*****************************/
/********PROPIEDADES**********/
/*****************************/

  //Modos
  const char * const Modos[2]={
      "oFF ",	//controlPID								
			"on  ", //AutoSintonia
			
  };



  const char * Modos_getText(byte Modo){
    return Modos[Modo];
  }   

 
  ADAPTAR_FUNCION_GET_AUTS(getModo,getModo)
  ADAPTAR_FUNCION_SET_AUTS(setModo,setModo)

  const struct ConstructorPropiedadTextual cPropiedadModos={
    &propiedadTextualFactory,getModo,"St",setModo,Modos_getText,2
  };
  
  
  
  //Reset
  ADAPTAR_FUNCION_GET_CONTROL(getReset,getReset)
  ADAPTAR_FUNCION_SET(setReset,setReset)
  const struct ConstructorPropNumLFPV cPropiedadReset={
    &propNumLFPVFactory,getReset,"rES",setReset,-9999,9999,getDecimalesControl
  };

  //Histeresis
  ADAPTAR_FUNCION_GET_CONTROL(getHisteresis,getHisteresis)
  ADAPTAR_FUNCION_SET_CONTROL(setHisteresis,setHisteresis)
  
  const char * histeresisVista(PropGetterVisual * prop){    
    int valObj=prop->getVal();
    
    if(valObj<0)
      return "H  ";
    return "Ab ";    
}
  
  const struct ConstructorPropDescripcionVariablePV cPropiedadHisteresis={
    &propDescripcionVariablePVFactory,getHisteresis,"H  ",setHisteresis,-9999,9999,getDecimalesControl,histeresisVista
  };
    
  
  //Integral
  ADAPTAR_FUNCION_GET_CONTROL(getIntegral,getIntegral)
  ADAPTAR_FUNCION_SET_CONTROL(setIntegral,setIntegral)
  const struct ConstructorPropNumLFPF cPropiedadIntegral={
    &propNumLFPFFactory,getIntegral,"in ",setIntegral,-9999,9999,1
  };

  //Derivada
  ADAPTAR_FUNCION_GET_CONTROL(getDerivada,getDerivada)
  ADAPTAR_FUNCION_SET_CONTROL(setDerivada,setDerivada)
  const struct ConstructorPropNumLFPF cPropiedadDerivada={
    &propNumLFPFFactory,getDerivada,"dr",setDerivada,0,9999,1
  };
  
  //SetPoint
 /* #ifdef VF
  ADAPTAR_FUNCION_GET_CONTROL(getConfiguracionSetPoint,getSetPointEnRam)
  ADAPTAR_FUNCION_SET(setConfiguracionSetPoint,setSetPointEnRam)  
  #else  */                             
  ADAPTAR_FUNCION_GET_CONTROL(getConfiguracionSetPoint,getConfiguracionSetPoint)
  ADAPTAR_FUNCION_SET(setConfiguracionSetPoint,setConfiguracionSetPoint)
  //ADAPTAR_FUNCION_GET(getDecimales,getDecimales)
  //#endif
  
  const struct ConstructorPropNumLFPV cPropiedadSetPoint={
    &propNumLFPVFactory,getConfiguracionSetPoint,"SP",setConfiguracionSetPoint,-9999,9999,getDecimalesControl 
  };
  
  //SetPoint autoSintonia                              
  ADAPTAR_FUNCION_GET_AUTOSINTONIA(getConfiguracionSetPointAs,getConfiguracionSetPoint)
  //ADAPTAR_FUNCION_SET_AUTOSINTONIA(setConfiguracionSetPointAs,setConfiguracionSetPoint)
  //ADAPTAR_FUNCION_GET(getDecimales,getDecimales)
 
 // const struct ConstructorPropNumLFPV cPropiedadSetPointAutoSintonia={
  //  &propNumLFPVFactory,getConfiguracionSetPointAs,"SP",setConfiguracionSetPointAs,-9999,9999,getDecimalesAutoSintonia 
 // };
  
  const struct ConstructorPropGetterNumericoPV cPropiedadSetPointAutoSintonia={
    &propGetterNumericoPVFactory,getConfiguracionSetPointAs,"SP",getDecimalesAutoSintonia
  }; 
  
  
  //ModoSalida
  
  const char * const modos[3]={
      "cAL",
      "rEF",
      "mAn",											
  };


  const char * ms_getText(byte modo){
    return modos[modo];
  }   

 
  ADAPTAR_FUNCION_GET_CONTROL(getModoSalida,getModoSalida)
  ADAPTAR_FUNCION_SET_CONTROL(setModoSalida,setModoSalida)

  const struct ConstructorPropiedadTextual cPropiedadModoSalida={
    &propiedadTextualFactory,getModoSalida,"C",setModoSalida,ms_getText,3
  };
    
  //PotenciaManual
  ADAPTAR_FUNCION_GET(getPotenciaManual,getPotenciaManual)
  ADAPTAR_FUNCION_SET(setPotenciaManual,setPotenciaManual)
  const struct ConstructorPropNumLVPF cPropiedadPotManual={
    &propNumLVPFFactory,getPotenciaManual,"Pot",setPotenciaManual,getLimiteInfPotManual,getLimiteSupPotManual,1
  };
  
  //Potencia
    const struct ConstructorPropGetterNumerico cPropiedadGetPotenciaInst={
    &propGetterNumericoFactory,getPotencia,"Pot",1
  };

   //Limites
   ADAPTAR_FUNCION_GET(getLimiteInferiorPotencia,getLimiteInferiorPotencia)
   ADAPTAR_FUNCION_SET(setLimiteInferiorPotencia,setLimiteInferiorPotencia)
   const struct ConstructorPropNumLFPF cPropiedadLimInfPot={
    &propNumLFPFFactory,getLimiteInferiorPotencia,"Pi",setLimiteInferiorPotencia,-9999,9999,1
  };
   
   ADAPTAR_FUNCION_GET(getLimiteSuperiorPotencia,getLimiteSuperiorPotencia)
   ADAPTAR_FUNCION_SET(setLimiteSuperiorPotencia,setLimiteSuperiorPotencia)
   const struct ConstructorPropNumLFPF cPropiedadLimSupPot={
    &propNumLFPFFactory,getLimiteSuperiorPotencia,"PS",setLimiteSuperiorPotencia,-9999,9999,1
  };
  
   ADAPTAR_FUNCION_GET(getLimiteInferiorSetPoint,getLimiteInferiorSetPoint)
   ADAPTAR_FUNCION_SET(setLimiteInferiorSetPoint,setLimiteInferiorSetPoint)
   const struct ConstructorPropNumLFPV cPropiedadLimInfSp={
    &propNumLFPVFactory,getLimiteInferiorSetPoint,"Li",setLimiteInferiorSetPoint,-9999,9999,getDecimalesControl
  };
  
   ADAPTAR_FUNCION_GET(getLimiteSuperiorSetPoint,getLimiteSuperiorSetPoint)
   ADAPTAR_FUNCION_SET(setLimiteSuperiorSetPoint,setLimiteSuperiorSetPoint)
   const struct ConstructorPropNumLFPV cPropiedadLimSupSp={
    &propNumLFPVFactory,getLimiteSuperiorSetPoint,"LS",setLimiteSuperiorSetPoint,-9999,9999,getDecimalesControl
  };
  
  ADAPTAR_FUNCION_GET_AUTOSINTONIA(getLimiteInferiorPotenciaAs,getLimiteInferiorPotencia)
   ADAPTAR_FUNCION_SET_AUTOSINTONIA(setLimiteInferiorPotenciaAs,setLimiteInferiorPotencia)
   const struct ConstructorPropNumLFPF cPropiedadLimInfPotAs={
    &propNumLFPFFactory,getLimiteInferiorPotenciaAs,"Pi",setLimiteInferiorPotenciaAs,-9999,9999,1
  };
   
   ADAPTAR_FUNCION_GET_AUTOSINTONIA(getLimiteSuperiorPotenciaAs,getLimiteSuperiorPotencia)
   ADAPTAR_FUNCION_SET_AUTOSINTONIA(setLimiteSuperiorPotenciaAs,setLimiteSuperiorPotencia)
   const struct ConstructorPropNumLFPF cPropiedadLimSupPotAs={
    &propNumLFPFFactory,getLimiteSuperiorPotenciaAs,"PS",setLimiteSuperiorPotenciaAs,-9999,9999,1
  };
  
   ADAPTAR_FUNCION_GET_AUTOSINTONIA(getLimiteInferiorSetPointAs,getLimiteInferiorSetPoint)
   ADAPTAR_FUNCION_SET_AUTOSINTONIA(setLimiteInferiorSetPointAs,setLimiteInferiorSetPoint)
   const struct ConstructorPropNumLFPV cPropiedadLimInfSpAs={
    &propNumLFPVFactory,getLimiteInferiorSetPointAs,"Li",setLimiteInferiorSetPointAs,-9999,9999,getDecimalesControl
  };
  
   ADAPTAR_FUNCION_GET_AUTOSINTONIA(getLimiteSuperiorSetPointAs,getLimiteSuperiorSetPoint)
   ADAPTAR_FUNCION_SET_AUTOSINTONIA(setLimiteSuperiorSetPointAs,setLimiteSuperiorSetPoint)
   const struct ConstructorPropNumLFPV cPropiedadLimSupSpAs={
    &propNumLFPVFactory,getLimiteSuperiorSetPointAs,"LS",setLimiteSuperiorSetPointAs,-9999,9999,getDecimalesControl
  };
  
  //valor del sensor2
 const struct ConstructorPropGetterNumericoPV cPropiedadGetSensor1={
    &propGetterNumericoPVFactory,getVal_,"S2",getDecimalesControl
  };
