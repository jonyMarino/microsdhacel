#include <stdio.h>
#include "BoxPropiedadVF.hpp"
#include "obtenciondisplay.hpp"
#include "Propiedades/PropiedadIncrementable/PropiedadIncrementableVF.hpp"

const struct BoxPropiedadVFFactory boxPropiedadVFFactory;;
const struct BoxPropGetterVFFactory boxPropGetterVFFactory;

BoxPropiedadVF::BoxPropiedadVF():propiedad(NULL),save(FALSE){}

BoxPropiedadVF::~BoxPropiedadVF(){
  if(propiedad)
    delete propiedad;
}

void BoxPropiedadVF::setPropiedad(PropGetterVisualVF& _propiedad,bool _isIncrementable){
  const char * desc;
  if(propiedad)
    delete propiedad;
  propiedad = &_propiedad;
  propiedad->printDescripcion(getDisplay(1));
  propiedad->print(getDisplay(0));
  save=FALSE;
  isIncrementable = _isIncrementable; 
}

PropGetterVisualVF * BoxPropiedadVF::getPropiedad(){
  return propiedad;
}

void BoxPropiedadVF::refresh(){
  //PropWInc_Refresh(_box->prop_actual);  
  propiedad->print(getDisplay(0));
}

Box * BoxPropiedadVF::procesarTecla(uchar tecla,TEstadoBox& estado){
    if(!propiedad){
      estado = EXIT_BOX;  
      return NULL;
    }
      
    if (isIncrementable && ((tecla=='u') || (tecla=='d'))){ // Fue presionada una Tecla UP o Down???
			  PropiedadIncrementableVF * p = (PropiedadIncrementableVF *) propiedad;
			  if(tecla=='u')
			    p->incrementar();
			  if(tecla=='d')
			    p->decrementar();			  
			  save=TRUE;							            // Grabar parametros
			  propiedad->print(getDisplay(0));
			  propiedad->printDescripcion(getDisplay(1));
			  estado = STAY_BOX;
			  return NULL;
  } else if (tecla=='r'){
    if(save)
	    ((PropiedadIncrementableVF *) propiedad)->guardar(); 
    estado = EXIT_BOX;
    return  NULL;
   }
  
  estado = STAY_BOX;  
  return NULL;

}