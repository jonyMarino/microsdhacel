#include "PropGetterVisual.hpp"

PropGetterVisual::PropGetterVisual(void*obj,const struct ArgumentosPropGetterVisual* args):PropiedadGetter(obj,(const struct ArgumentosPropiedadGetter*)args){}
/*
** ===================================================================
**     Method      :  PropVisual_getDescripcion 
**     Description :  Obtiene un string con la descripción de la
**                   propiedad
** ===================================================================
*/

const char * PropGetterVisual::getDescripcion(){
  return ((const struct ArgumentosPropGetterVisual*)getArgumentos())->descripcion;  
}


void BoxPropiedad::printDescripcion(OutputStream& os){
  const char * desc = getDescripcion();
  if(numObjeto){
    char strTmp[30];
    sprintf(strTmp,"%s%d",desc,numObjeto);
    os.write(strTmp);
  } else
      os.write(desc);
}


PropiedadGetter& PropGetterVisualFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args)const{
  return *new PropGetterVisual(obj,(const struct ArgumentosPropGetterVisual*)args);
} 
