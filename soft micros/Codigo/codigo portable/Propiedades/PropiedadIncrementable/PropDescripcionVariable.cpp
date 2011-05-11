#include "PropDescripcionVariable.hpp"


const struct PropDescripcionVariableFactory propDescripcionVariableFactory;


PropDescripcionVariable::PropDescripcionVariable(void*obj,const struct ArgumentosPropNumDP* args,uchar numObjeto):
  PropNumLFPF(obj,(const struct ArgumentosPropNumLFPF*) args,numObjeto){}
  
const char * PropDescripcionVariable::getDescripcion(){
  return ((const struct ArgumentosPropNumDP *)getArgumentos())->getDescripcion(*this);
}

PropiedadGetter& PropDescripcionVariableFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const{
  return *new PropDescripcionVariable(obj,(const struct ArgumentosPropNumDP*)args,numObjeto);
} 