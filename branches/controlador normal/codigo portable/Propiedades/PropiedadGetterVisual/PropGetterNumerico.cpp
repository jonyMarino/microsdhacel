#include "PropGetterNumerico.hpp"
#include "PE/include/PE_Types.h"

const struct PropGetterNumericoFactory propGetterNumericoFactory;

PropGetterNumericoFactory::PropGetterNumericoFactory(){
}

PropGetterNumerico::PropGetterNumerico(void*obj,const struct ArgumentosPropGetterNumerico* args,uchar numObjeto):PropGetterVisual(obj,(const struct ArgumentosPropGetterVisual*)args,numObjeto){}
/*
** ===================================================================
**     Method      :  PropVisual_getDescripcion 
**     Description :  Obtiene un string con la descripción de la
**                   propiedad
** ===================================================================
*/

void PropGetterNumerico::print(OutputStream&os){
  byte puntoDecimal = ((struct ArgumentosPropGetterNumerico*) getArgumentos())->puntoDecimal;
  os.writeAsFloat(getVal(),puntoDecimal);  
}

PropiedadGetter& PropGetterNumericoFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const{
  return *new PropGetterNumerico(obj,(const struct ArgumentosPropGetterNumerico*)args,numObjeto);
} 
