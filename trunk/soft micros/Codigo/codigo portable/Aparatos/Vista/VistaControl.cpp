
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
#include "ControlPID.hpp"
#include "VistaPWM.hpp"
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

bool getCondicionEntrada (void* control){
  if(((ControlPID*)control)->getModoSalida() != ControlPID::_MAN)
    return TRUE;
  else
    return FALSE;  
}


uchar nextSetProp (void * obj){
  
  if(((ControlPID*)obj)->getModoSalida() != ControlPID::_MAN)
    return 0;  // posicion de cPropiedadGetPotencia en el la tabla propsPot
  else
    return 2;  
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
  
  //SetPoint                              
  ADAPTAR_FUNCION_GET(getConfiguracionSetPoint,getConfiguracionSetPoint)
  ADAPTAR_FUNCION_SET(setConfiguracionSetPoint,setConfiguracionSetPoint)
  //ADAPTAR_FUNCION_GET(getDecimales,getDecimales)
  
  const struct ConstructorPropNumLFPV cPropiedadSetPoint={
    &propNumLFPVFactory,getConfiguracionSetPoint,"SP",setConfiguracionSetPoint,-9999,9999,getDecimalesControl 
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

 
  ADAPTAR_FUNCION_GET(getModoSalida,getModoSalida)
  ADAPTAR_FUNCION_SET(setModoSalida,setModoSalida)

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
   const struct ConstructorPropNumLFPV cPropiedadLimInfPot={
    &propNumLFPVFactory,getLimiteInferiorPotencia,"Pi",setLimiteInferiorPotencia,-9999,9999,getDecimalesControl
  };
   
   ADAPTAR_FUNCION_GET(getLimiteSuperiorPotencia,getLimiteSuperiorPotencia)
   ADAPTAR_FUNCION_SET(setLimiteSuperiorPotencia,setLimiteSuperiorPotencia)
   const struct ConstructorPropNumLFPV cPropiedadLimSupPot={
    &propNumLFPVFactory,getLimiteSuperiorPotencia,"PS",setLimiteSuperiorPotencia,-9999,9999,getDecimalesControl
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


const struct ConstructorBoxPropiedad cBoxesSetPoint={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadSetPoint
};  

const struct ConstructorBoxPropiedad cBoxModoSalida={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadModoSalida
};


const struct ConstructorBoxPropiedadEntradaCondicional cBoxPotInst ={
   &boxPropiedadEntradaCondicionalFactory,
   (const struct ConstructorPropGetterVisual*)&cPropiedadGetPotenciaInst,
   getCondicionEntrada
};
 
 

const struct ConstructorPropGetterVisual*const propsPot[]=	{
			  (const struct ConstructorPropGetterVisual*)&cPropiedadSetPoint,
			  NULL,
			  (const struct ConstructorPropGetterVisual*)&cPropiedadPotManual,
			  NULL
};
const struct ConstructorBoxLinealCondicional cBoxPotMan={
      &boxLinealCondicionalFactory,								
			propsPot,
			NULL,
			nextSetProp
};	 
 
const struct ConstructorPropGetterVisual *const propLimites[]=	{
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadLimInfSp,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadLimSupSp,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadLimInfPot,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadLimSupPot,
  			  NULL
};

const struct ConstructorBoxLineal cBoxesLimites={
        &boxLinealFactory,						       
  		  propLimites,
  		  NULL						 //Proximo box	
}; 