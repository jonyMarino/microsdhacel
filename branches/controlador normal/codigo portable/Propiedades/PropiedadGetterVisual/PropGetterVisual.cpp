#include <stdio.h>
#include "PropGetterVisual.hpp"


PropGetterVisualFactory::PropGetterVisualFactory(){
}

PropGetterVisual::PropGetterVisual(void*obj,const struct ArgumentosPropGetterVisual* args,uchar _numObjeto):PropiedadGetter(obj,(const struct ArgumentosPropiedadGetter*)args),numObjeto(_numObjeto){}
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


void PropGetterVisual::printDescripcion(OutputStream& os){
  const char * desc = getDescripcion();
  if(numObjeto){
    char strTmp[30];
    sprintf(strTmp,"%s%d",desc,numObjeto);
    os.write(strTmp);
  } else
      os.write(desc);
}

PropiedadGetter& ConstructorPropGetterVisual::getPropiedad(void*obj,uchar numObj)const{
  return factory->getPropiedad(obj,(const struct ArgumentosPropiedadGetter*)&args,numObj);
}  


PropiedadGetter& PropGetterVisualFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const{
  return *new PropGetterVisual(obj,(const struct ArgumentosPropGetterVisual*)args,numObjeto);
} 
