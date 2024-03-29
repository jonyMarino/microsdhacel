#include "PropNumLFPF.hpp"
//#include "PE/include/PE_Types.h"

const struct PropNumLFPFFactory propNumLFPFFactory;

PropNumLFPF::PropNumLFPF(void*obj,const struct ArgumentosPropNumLFPF* args,uchar numObjeto):PropNumLF(obj,(const struct ArgumentosPropNumLF*)args,numObjeto){}


uchar PropNumLFPF::getCantidadDecimales(){
  struct ArgumentosPropNumLFPF* arg= (struct ArgumentosPropNumLFPF*)getArgumentos();
  return arg->decimales;
}

PropiedadGetter& PropNumLFPFFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const{
  return *new PropNumLFPF(obj,(const struct ArgumentosPropNumLFPF*)args,numObjeto);
} 
