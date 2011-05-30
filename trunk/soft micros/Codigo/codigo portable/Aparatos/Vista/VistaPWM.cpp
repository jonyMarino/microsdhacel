#include "VistaPWM.hpp"
#include "propiedadesPWM.hpp"
#include "BoxLineal.hpp"
#include "BoxSaltoCondicional.hpp"
#include "BoxLinealCondicional.hpp"





  
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
 
  
