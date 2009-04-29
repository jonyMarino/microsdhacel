#include "valvulaProporcionalHMI.h"
#include "ValvulaProporcional.h"
#include "PropWithInc.h"
#include "ClassBoxLineal.h" 
 
 /* Propiedades*/
 
  const struct ConstructorPropWInc PropTiempoApertura={
    &PropiedadGenerica,get_tiempoAbierto,set_tiempoAbierto,get_0,get_LimSup_tiempoAbierto,&PropWInc,"TA "
  };
  
  const struct ConstructorPropWInc PropBandaMuerta={
    &PropiedadGenerica,get_bandaMuerta,set_bandaMuerta,get_0,get_LimSup_bandaMuerta,&PropWInc,"BM "
  }; 

//Boxes:
  const struct ConstructorPropWInc*const Props_PID_Lim[]=	{
  			  &PropTiempoApertura,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
  			  &PropBandaMuerta,
   			  NULL
};

const struct BlockCnstrBoxLin CBox_PID_Lim={
      &BoxLineal,
      Props_PID_Lim,
			NULL
			};
			
			
			


