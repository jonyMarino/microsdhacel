#include "valvulaProporcionalHMI.h"
#include "ValvulaProporcional.h"
#include "PropWithInc.h"
#include "ClassBoxLineal.h" 
 
 /* Propiedades*/
 
  const struct ConstructorPropWInc PropTiempoApertura={
    (const struct Class * const)&PropiedadGenerica,get_tiempoAbierto,set_tiempoAbierto,get_0,NULL,&PropWInc,"tA "
  };
  
  const struct ConstructorPropWInc PropBandaMuerta={
    (const struct Class * const)&PropiedadGenerica,get_bandaMuerta,set_bandaMuerta,get_0,NULL,&PropWInc,"bM "
  }; 

//Boxes:
  const struct ConstructorPropWInc*const Props_ValvulaProporcional[]=	{
  			  &PropTiempoApertura,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
  			  &PropBandaMuerta,
   			  NULL
};

const struct BlockCnstrBoxLin CBox_ValvulaProporcional={
      &BoxLineal,
      Props_ValvulaProporcional,
			NULL
			};
			
			
			


