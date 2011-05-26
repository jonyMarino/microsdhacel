/*  MODULE: SnsHmi.c (Sensores Human Machine interface)*/
#include "PropGetterVisual.hpp"
#include "PropiedadNumerica.hpp"
#include "PropNumLFPV.hpp"
#include "PropNumLFPF.hpp"
#include "PropiedadTextual.hpp"

#include "BoxLineal.hpp"
#include "BoxSaltoCondicional.hpp"
#include "Sensores.h"
#include "SensorTermoPT100.hpp"

#include "vistasensortermopt100.hpp"

#pragma MESSAGE DISABLE C1825          /* Disable warning C5703 "Parameter is not referenced" */

#define ADAPTAR_FUNCION_GET(NOMBRE,METODO)\
    int NOMBRE(void*sensor){           \
    return ((SensorTermoPT100*)sensor)->METODO(); \
  }
  
#define ADAPTAR_FUNCION_SET(NOMBRE,METODO)      \
  void NOMBRE(void*sensor,int valor){           \
    ((SensorTermoPT100*)sensor)->METODO(valor); \
  }   

uchar getDecimalesMostrados(void*sensor){           
  return ((SensorTermoPT100*)sensor)->getDecimales();
}

  
/*****************************/
/********PROPIEDADES**********/
/*****************************/

  //Valor del Sensor
/*  const struct GetterGenerico GetterValSen={
    (const struct Class * const)&GetterGenerico,SenTPT_getValue
  };
  
  //Decimales
  extern int SenTPT_getDecimales(const struct TSensor_TermoPT * self);
  const struct GetterGenerico GetterDecimales={
    (const struct Class * const)&GetterGenerico,SenTPT_getDecimales
  }; 
  
  */
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
/*  //Estado del Sensor
  int getEstadoSensorVista(void *sensor){
    return SenTPT_getState(sensor);
  }
  const struct GetterGenerico GetterEstadoSen={
    (const struct Class * const)&GetterGenerico,getEstadoSensorVista
  };
  
  const void *const SensProps[]={
    &ParSensor,
    &ParDecimales,
    &ParFiltro,
    &ParOffset,
    &ParGanancia,
    &ParAjCeroT,
    &ParAjGanT,
    &ParAjCeroPT,
    &ParAjGanPT,
    &ParAjTempAmb,
    &GetterValSen,
    &GetterDecimales,
    &GetterEstadoSen
  };
  
  const NEW_ARRAY(arraySenGetters,SensProps);
  

*/  

 /***********************/
 /****** BOXES  *********/
 /***********************/
extern const struct ConstructorBoxSaltoCondicional cBoxGanancia; 
extern const struct ConstructorBoxPropiedad cBoxFiltro;
extern const struct ConstructorBoxLineal cBoxAjustes;            
/*
** ===================================================================
**     Function      :  SnsHmi_Add 
**     Description :  Agrega a los boxes el sensor
** ===================================================================
*/


 
//  Sensor y Offset

const struct ConstructorPropGetterVisual *const propsSen1[]=	{
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadTipoSensor,								
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadOffset,
  			  NULL
};
const struct ConstructorBoxLineal cBoxesSensor={
        &boxLinealFactory,						       
  		  propsSen1,
  			(const struct ConstructorBox*)&cBoxGanancia,						 //Proximo box	
};

			
//ganancia
Box * gananciaNext(PropGetterVisual * prop,uchar tecla){
  if(tecla == 'r' || tecla == 'f'){
    void * obj = prop->getObjeto();
    uchar numObj = prop->getNumObjeto();   
    if(tecla=='r')
      return  &((struct ConstructorBox*)&cBoxFiltro)->getBox(obj,numObj);
    else if(tecla=='f')
      return  &((struct ConstructorBox*)&cBoxAjustes)->getBox(obj,numObj);
  }
  return NULL;
}
const struct ConstructorBoxSaltoCondicional cBoxGanancia={
      &boxSaltoCondicionalFactory,						 
			(const struct ConstructorPropGetterVisual*)&cPropiedadGanancia,
			gananciaNext
};
		

//ajuste cero canal 1
const struct ConstructorPropGetterVisual*const propsAjustes[]=	{
			  (const struct ConstructorPropGetterVisual*)&cPropiedadAjCeroT,							
			  (const struct ConstructorPropGetterVisual*)&cPropiedadAjGanT,
			  (const struct ConstructorPropGetterVisual*)&cPropiedadAjCeroPT,
			  (const struct ConstructorPropGetterVisual*)&cPropiedadAjGanPT,
			  (const struct ConstructorPropGetterVisual*)&cPropiedadAjTempAmb,	
			  NULL
};
const struct ConstructorBoxLineal cBoxAjustes={
      &boxLinealFactory,								
			propsAjustes,
			(const struct ConstructorBox*)&cBoxGanancia
};			


const struct ConstructorBoxPropiedad cBoxFiltro={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadFiltro
}; 
