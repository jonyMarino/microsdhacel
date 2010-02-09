#include <stdio.h>
#include "BoxPropiedad.hpp"
#include "obtenciondisplay.hpp"
#include "PropiedadIncrementable.hpp"

const struct BoxPropiedadFactory boxPropiedadFactory;;
const struct BoxPropGetterFactory boxPropGetterFactory;

BoxPropiedad::BoxPropiedad():propiedad(NULL),save(FALSE){}

BoxPropiedad::~BoxPropiedad(){
  if(propiedad)
    delete propiedad;
}

void BoxPropiedad::setPropiedad(PropGetterVisual& _propiedad,bool _isIncrementable){
  const char * desc;
  if(propiedad)
    delete propiedad;
  propiedad = &_propiedad;
  propiedad->printDescripcion(getDisplay(1));
  propiedad->print(getDisplay(0));
  save=FALSE;
  isIncrementable = _isIncrementable; 
}

PropGetterVisual * BoxPropiedad::getPropiedad(){
  return propiedad;
}

void BoxPropiedad::refresh(){
  //PropWInc_Refresh(_box->prop_actual);  
  propiedad->print(getDisplay(0));
}

Box * BoxPropiedad::procesarTecla(uchar tecla,TEstadoBox& estado){
    if(!propiedad){
      estado = EXIT_BOX;  
      return NULL;
    }
      
    if (isIncrementable && ((tecla=='u') || (tecla=='d'))){ // Fue presionada una Tecla UP o Down???
			  PropiedadIncrementable * p = (PropiedadIncrementable *) propiedad;
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
	    ((PropiedadIncrementable *) propiedad)->guardar(); 
    estado = EXIT_BOX;
    return  NULL;
   }
  
  estado = STAY_BOX;  
  return NULL;

}