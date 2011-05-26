  #include <stdio.h>
#include "PropGetterVisualVF.hpp"


PropGetterVisualVFFactory::PropGetterVisualVFFactory(){
}

PropGetterVisualVF::PropGetterVisualVF(void*obj,const struct ArgumentosPropGetterVisualVF* args,uchar _numObjeto):PropiedadGetterVF(obj,_numObjeto,(const struct ArgumentosPropiedadGetterVF*)args),numObjeto(_numObjeto){}
/*
** ===================================================================
**     Method      :  PropVisual_getDescripcion 
**     Description :  Obtiene un string con la descripción de la
**                   propiedad
** ===================================================================
*/

const char * PropGetterVisualVF::getDescripcion(){
  return ((const struct ArgumentosPropGetterVisualVF*)getArgumentos())->descripcion;  
}

const char * PropGetterVisualVF::getUnidad(){
  return ((const struct ArgumentosPropGetterVisualVF*)getArgumentos())->unidad;
}


void PropGetterVisualVF::printDescripcion(OutputStream& os){
  const char * desc = getDescripcion();
  const char * und = getUnidad();
  if(numObjeto){
    char strTmp[30];
    sprintf(strTmp,"%s%d%s",desc,numObjeto,und);
    os.write(strTmp);
  } else
      os.write(desc);
}

PropiedadGetterVF& ConstructorPropGetterVisualVF::getPropiedad(void*obj,uchar numObj)const{
  return factory->getPropiedad(obj,(const struct ArgumentosPropiedadGetterVF*)&args,numObj);
}  


PropiedadGetterVF& PropGetterVisualVFFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetterVF* args,uchar numObjeto)const{
  return *new PropGetterVisualVF(obj,(const struct ArgumentosPropGetterVisualVF*)args,numObjeto);
} 
