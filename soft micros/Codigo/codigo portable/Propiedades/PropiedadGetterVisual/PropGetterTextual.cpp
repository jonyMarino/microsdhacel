#include "PropGetterTextual.hpp"

PropGetterTextual::PropGetterTextual(void*obj,const struct ArgumentosPropGetterTextual* args):PropGetterVisual(obj,(const struct ArgumentosPropGetterVisual*)args){}
/*
** ===================================================================
**     Method      :  PropVisual_getDescripcion 
**     Description :  Obtiene un string con la descripción de la
**                   propiedad
** ===================================================================
*/

void PropGetterTextual::print(OutputStream&os){   
  int valor= getVal();
  struct ArgumentosPropGetterTextual* arg= (struct ArgumentosPropGetterTextual*)getArgumentos();
  char * str= (*(arg->getTxt))((uchar)valor);
  
  os.write(str);   
}

PropiedadGetter& PropGetterTextualFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args)const{
  return *new PropGetterTextual(obj,(const struct ArgumentosPropGetterTextual*)args);
} 
