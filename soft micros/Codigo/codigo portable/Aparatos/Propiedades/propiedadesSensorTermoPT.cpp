#include "propiedadesSensorTermoPT.hpp"
#include "Sensores.h"
#include "SensorTermoPT100.hpp"



#pragma MESSAGE DISABLE C1825          /* Disable warning C5703 "Parameter is not referenced" */

#define ADAPTAR_FUNCION_GET(NOMBRE,METODO)\
    int NOMBRE(void*sensor){           \
    return ((SensorTermoPT100*)sensor)->METODO(); \
  }
  
#define ADAPTAR_FUNCION_SET(NOMBRE,METODO)      \
  void NOMBRE(void*sensor,int valor){           \
    ((SensorTermoPT100*)sensor)->METODO(valor); \
  }   

int getValor(void*sensor){           
  return ((SensorTermoPT100*)sensor)->getVal();
}

uchar getDecimalesMostrados(void*sensor){           
  return ((SensorTermoPT100*)sensor)->getDecimales();
}

int getEstado(void*sensor){           
  return ((SensorTermoPT100*)sensor)->getEstado();
}


/*****************************/
/********PROPIEDADES**********/
/*****************************/

  //Valor del Sensor
  const struct ConstructorPropGetterVisual cGetterValSen={
    &propGetterVisualFactory,getValor,"VAL"
  };
  
  //Valor del Sensor
  const struct ConstructorPropGetterVisual cGetterEstado={
    &propGetterVisualFactory,getEstado,"EStAdo"
  };
  
  //Decimales
  /*const struct ConstructorPropGetterVisual GetterDecimales={
    (const struct Class * const)&GetterGenerico,getDecimalesMostrados
  };*/ 
  
  
  //Sensor
  int  getTipoSensor(void*sensor){
    return ((SensorTermoPT100*)sensor)->getSensor();
  }
  void setTipoSensor(void*sensor,int valor){
    ((SensorTermoPT100*)sensor)->setSensor(valor);  
  }
  const struct ConstructorPropiedadTextual cPropiedadTipoSensor={
    &propiedadTextualFactory,getTipoSensor,"SEn",setTipoSensor,SENSOR_getText,NUM_SENSORES
  };

/*  
  //Decimales Mostrados
  int SenTPT_getDecimales(const struct TSensor_TermoPT * self);
  typedef int (*ipfvp)(void*);
  const struct ConstructorPropWInc ParDecimales= {
    (const struct Class * const)&PropiedadGenerica,(ipfvp)SenTPT_getDecimalesMostrados,SenTPT_setDecimales,get_0,get_LimSup_Decimales,&PropWInc,"dec "
  };
*/
  //Filtro
  ADAPTAR_FUNCION_GET(getFiltro,getFiltro)
  ADAPTAR_FUNCION_SET(setFiltro,setFiltro)
  const struct ConstructorPropNumLFPF cPropiedadFiltro={
    &propNumLFPFFactory,getFiltro,"FiL",setFiltro,0,9999,1
  };

  //Offset
  ADAPTAR_FUNCION_GET(getOffset,getOffset)
  ADAPTAR_FUNCION_SET(setOffset,setOffset)
  const struct ConstructorPropNumLFPV cPropiedadOffset={
    &propNumLFPVFactory,getOffset,"oFS",setOffset,-1999,9999,getDecimalesMostrados
  };

  //Gan1
  ADAPTAR_FUNCION_GET(getGanancia,getGanancia)
  ADAPTAR_FUNCION_SET(setGanancia,setGanancia) 
  const struct ConstructorPropNumLFPF cPropiedadGanancia={
    &propNumLFPFFactory,getGanancia,"gAn",setGanancia,-1999,9999,3
  };

  //Ajuste Cero Termopar 
  ADAPTAR_FUNCION_GET(getCeroTermopar,getCeroTermopar)
  ADAPTAR_FUNCION_SET(setCeroTermopar,setCeroTermopar) 
  const struct ConstructorPropNumLFPV cPropiedadAjCeroT={
    &propNumLFPVFactory,getCeroTermopar,"AC ",setCeroTermopar,-1999,9999,getDecimalesMostrados
  };

  //Ajuste Gan Termopar
  ADAPTAR_FUNCION_GET(getGananciaTermopar,getGananciaTermopar)
  ADAPTAR_FUNCION_SET(setGananciaTermopar,setGananciaTermopar) 
  const struct ConstructorPropNumLFPF cPropiedadAjGanT={
    &propNumLFPFFactory,getGananciaTermopar,"Ag ",setGananciaTermopar,-1999,9999,1
  };

  //Ajuste Cero PT100
  ADAPTAR_FUNCION_GET(getCeroPT100,getCeroPT100)
  ADAPTAR_FUNCION_SET(setCeroPT100,setCeroPT100) 
  const struct ConstructorPropNumLFPV cPropiedadAjCeroPT={
    &propNumLFPVFactory,getCeroPT100,"ACP",setCeroPT100,-1999,9999,getDecimalesMostrados
  };

  //Ajuste Gan PT100
  ADAPTAR_FUNCION_GET(getGananciaPT100,getGananciaPT100)
  ADAPTAR_FUNCION_SET(setGananciaPT100,setGananciaPT100)
  const struct ConstructorPropNumLFPF cPropiedadAjGanPT={
    &propNumLFPFFactory,getGananciaPT100,"AGP",setGananciaPT100,-1999,9999,3
  };

  //Ajuste Temperatura Ambiente
  ADAPTAR_FUNCION_GET(getAjusteTemperaturaAmbiente,getAjusteTemperaturaAmbiente)
  ADAPTAR_FUNCION_SET(setAjusteTemperaturaAmbiente,setAjusteTemperaturaAmbiente)
  const struct ConstructorPropNumLFPF cPropiedadAjTempAmb={
    &propNumLFPFFactory,getAjusteTemperaturaAmbiente,"AtA",setAjusteTemperaturaAmbiente,-1999,9999,1
  };
