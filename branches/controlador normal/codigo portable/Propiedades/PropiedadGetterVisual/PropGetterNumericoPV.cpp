#include "PropGetterNumericoPV.hpp"
#include "PE/include/PE_Types.h"

const struct PropGetterNumericoPVFactory propGetterNumericoPVFactory;

PropGetterNumericoPVFactory::PropGetterNumericoPVFactory(){
}

PropiedadGetter& PropGetterNumericoPVFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const{
  return *new PropGetterNumericoPV(obj,(const struct ArgumentosPropGetterNumericoPV*)args,numObjeto);
} 

PropGetterNumericoPV::PropGetterNumericoPV(void*obj,const struct ArgumentosPropGetterNumericoPV* args,uchar numObjeto):PropGetterVisual(obj,(const struct ArgumentosPropGetterVisual*)args,numObjeto){}
/*
** ===================================================================
**     Method      :  PropVisual_getDescripcion 
**     Description :  Obtiene un string con la descripción de la
**                   propiedad
** ===================================================================
*/

void PropGetterNumericoPV::print(OutputStream&os){
  
  byte puntoDecimal = ((struct ArgumentosPropGetterNumericoPV*) getArgumentos())->getCantidadDecimales(getObjeto());
  os.writeAsFloat(getVal(),puntoDecimal);  
}


