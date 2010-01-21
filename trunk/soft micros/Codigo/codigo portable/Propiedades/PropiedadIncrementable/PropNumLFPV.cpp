#include "PropNumLFPV.hpp"
//#include "PE/include/PE_Types.h"

const struct PropNumLFPVFactory propNumLFPVFactory;

PropNumLFPV::PropNumLFPV(void*obj,const struct ArgumentosPropNumLFPV* args):PropNumLF(obj,(const struct ArgumentosPropNumLF*)args){}


uchar PropNumLFPV::getCantidadDecimales(){
  struct ArgumentosPropNumLFPV* arg= (struct ArgumentosPropNumLFPV*)getArgumentos();
  return (*arg->getCantidadDecimales)(getObjeto());
}

PropiedadGetter& PropNumLFPVFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args)const{
  return *new PropNumLFPV(obj,(const struct ArgumentosPropNumLFPV*)args);
} 
