#include "PropDescripcionVariablePV.hpp"


const struct PropDescripcionVariablePVFactory propDescripcionVariablePVFactory;


PropDescripcionVariablePV::PropDescripcionVariablePV(void*obj,const struct ArgumentosPropNumDPPV* args,uchar numObjeto):
  PropNumLFPV(obj,(const struct ArgumentosPropNumLFPV*) args,numObjeto){}
  
const char * PropDescripcionVariablePV::getDescripcion(){
  return ((const struct ArgumentosPropNumDPPV *)getArgumentos())->getDescripcion(*this);
}

PropiedadGetter& PropDescripcionVariablePVFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const{
  return *new PropDescripcionVariablePV(obj,(const struct ArgumentosPropNumDPPV*)args,numObjeto);
} 