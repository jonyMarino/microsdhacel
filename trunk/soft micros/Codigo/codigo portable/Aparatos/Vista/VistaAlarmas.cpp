#include "propiedadesAlarma.hpp"
#include "BoxLineal.hpp"
#include "BoxSaltoCondicional.hpp"
#include "BoxPropiedadEntradaCondicional.hpp"
#include "BoxLinealCondicional.hpp"
#include "VistaAlarmas.hpp"
#include "CoordinadorLazosAlCntrRet.hpp"


  
  
 /***********************/
 /****** BOXES  *********/

bool getCondicionEntradaAl (void* alarma){
  if(((CoordinadorLazosAlCntrRet*)alarma)->getLazo() != RETRANSMISION)
    return TRUE;
  else
    return FALSE;  
}

bool getCondicionEntradaAlret (void* alarma){
  if(((CoordinadorLazosAlCntrRet*)alarma)->getLazo() == RETRANSMISION)
    return TRUE;
  else
    return FALSE;  
}

const struct ConstructorBoxPropiedadEntradaCondicional cBoxesAlarma ={
   &boxPropiedadEntradaCondicionalFactory,
   (const struct ConstructorPropGetterVisual*)&cPropiedadModoAlarma,
   getCondicionEntradaAl
};

const struct ConstructorBoxPropiedadEntradaCondicional cBoxesAlarmaCtrl ={
   &boxPropiedadEntradaCondicionalFactory,
   (const struct ConstructorPropGetterVisual*)&cPropiedadTipoCtrlAlarma,
   getCondicionEntradaAl
}; 


/*const struct ConstructorPropGetterVisual*const propsConfiguracion[]=	{
			  (const struct ConstructorPropGetterVisual*)&cPropiedadModoAlarma,
  			(const struct ConstructorPropGetterVisual*)&cPropiedadTipoCtrlAlarma,
			  NULL
			  
};

const struct ConstructorBoxLineal cBoxesAlarma={
        &boxLinealFactory,						       
  		  propsConfiguracion,
  		  NULL,						 //Proximo box	
};
  */

const struct ConstructorBoxPropiedadEntradaCondicional cBoxesRetLimInf ={
   &boxPropiedadEntradaCondicionalFactory,
   (const struct ConstructorPropGetterVisual*)&cPropiedadRetLimInf,
   getCondicionEntradaAlret
}; 

const struct ConstructorBoxPropiedadEntradaCondicional cBoxesRetLimSup ={
   &boxPropiedadEntradaCondicionalFactory,
   (const struct ConstructorPropGetterVisual*)&cPropiedadRetLimSup,
   getCondicionEntradaAlret
}; 

/*const struct ConstructorPropGetterVisual*const propsRet[]=	{
			  (const struct ConstructorPropGetterVisual*)&cPropiedadRetLimInf,
			  (const struct ConstructorPropGetterVisual*)&cPropiedadRetLimSup,
			  
};
const struct ConstructorBoxLineal cBoxesRetransmision={
      &boxLinealFactory,								
			propsRet,
			NULL,
			
};*/	 

const struct ConstructorBoxPropiedadEntradaCondicional cBoxesHistAlarma ={
   &boxPropiedadEntradaCondicionalFactory,
   (const struct ConstructorPropGetterVisual*)&cPropiedadHistAlarma,
   getCondicionEntradaAl
}; 

/*const struct ConstructorBoxPropiedad cBoxesHistAlarma={
       &boxPropiedadFactory,						       
  		 (const struct ConstructorPropGetterVisual*)&cPropiedadHistAlarma,
  		  
};*/ 
  
const struct ConstructorBoxPropiedad cBoxesTipoSalAlarma={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadTipoSalida
};

const struct ConstructorBoxPropiedad cBoxesTipoLazo={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadTipoLazo
};

  
const struct ConstructorBoxPropiedadEntradaCondicional cBoxesSetPointAlarma ={
   &boxPropiedadEntradaCondicionalFactory,
   (const struct ConstructorPropGetterVisual*)&cPropiedadSetPointAlarma,
   getCondicionEntradaAl
};


/*const struct ConstructorBoxPropiedad cBoxesSetPointAlarma={
        &boxPropiedadFactory,						       
  		  (const struct ConstructorPropGetterVisual*)&cPropiedadSetPointAlarma,
  		  
};
  */


