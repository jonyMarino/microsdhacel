#include "PropNumLFPV.hpp"
//#include "PE/include/PE_Types.h"

const struct PropNumLFPVFactory propNumLFPVFactory;

PropNumLFPV::PropNumLFPV(void*obj,const struct ArgumentosPropNumLFPV* args,uchar numObjeto):PropNumLF(obj,(const struct ArgumentosPropNumLF*)args,numObjeto){}


uchar PropNumLFPV::getCantidadDecimales(){
  struct ArgumentosPropNumLFPV* arg= (struct ArgumentosPropNumLFPV*)getArgumentos();
  return (*arg->getCantidadDecimales)(getObjeto());
}

PropiedadGetter& PropNumLFPVFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const{
  return *new PropNumLFPV(obj,(const struct ArgumentosPropNumLFPV*)args,numObjeto);
} 
