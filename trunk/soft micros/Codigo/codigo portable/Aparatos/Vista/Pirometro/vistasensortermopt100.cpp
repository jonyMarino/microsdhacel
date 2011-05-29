/*  MODULE: SnsHmi.c (Sensores Human Machine interface)*/


#include "BoxLineal.hpp"
#include "BoxSaltoCondicional.hpp"
#include "Sensores.h"
#include "SensorTermoPT100.hpp"
#include "propiedadesSensorTermoPT.hpp"

#include "vistasensortermopt100.hpp"

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
