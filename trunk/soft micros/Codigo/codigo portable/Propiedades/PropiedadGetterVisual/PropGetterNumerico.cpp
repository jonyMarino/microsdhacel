#include "PropGetterNumerico.hpp"
#include "PE/include/PE_Types.h"
#include "OOC/lang/CharPointer.hpp"

PropGetterNumerico::PropGetterNumerico(void*obj,const struct ArgumentosPropGetterNumerico* args,uchar numObjeto):PropGetterVisual(obj,(const struct ArgumentosPropGetterVisual*)args,numObjeto){}
/*
** ===================================================================
**     Method      :  PropVisual_getDescripcion 
**     Description :  Obtiene un string con la descripción de la
**                   propiedad
** ===================================================================
*/

void PropGetterNumerico::print(OutputStream&os){
  char str[7];
  byte puntoDecimal = ((struct ArgumentosPropGetterNumerico*) getArgumentos())->puntoDecimal;
  CharPointer::printFloat(str,getVal(),puntoDecimal);
  os.write(str);  
}

PropiedadGetter& PropGetterNumericoFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const{
  return *new PropGetterNumerico(obj,(const struct ArgumentosPropGetterNumerico*)args,numObjeto);
} 
