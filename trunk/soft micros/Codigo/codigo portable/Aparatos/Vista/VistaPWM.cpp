#include "BoxLineal.hpp"
#include "BoxSaltoCondicional.hpp"
#include "PropDescripcionVariable.hpp"
#include "BoxLinealCondicional.hpp"


#include "VistaPWM.hpp"


  
 /***********************/
 /****** BOXES  *********/
 
const struct ConstructorBoxPropiedad cBoxPeriodo={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadPeriodo
}; 

const struct ConstructorBoxPropiedad cBoxPeriodoAlarma={
      &boxPropiedadFactory,	
      (const struct ConstructorPropGetterVisual*)&cPropiedadPeriodoAlarma
};
 
  
