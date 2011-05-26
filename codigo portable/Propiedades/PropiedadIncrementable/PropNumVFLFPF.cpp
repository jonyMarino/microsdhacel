#include "PropNumVFLFPF.hpp"
//#include "PE/include/PE_Types.h"

const struct PropNumVFLFPFFactory propNumVFLFPFFactory;

PropNumVFLFPF::PropNumVFLFPF(void*obj,const struct ArgumentosPropNumVFLFPF* args,uchar numObjeto):PropNumVFLF(obj,(const struct ArgumentosPropNumVFLF*)args,numObjeto){}


uchar PropNumVFLFPF::getCantidadDecimales(){
  struct ArgumentosPropNumVFLFPF* arg= (struct ArgumentosPropNumVFLFPF*)getArgumentos();
  return arg->decimales;
}

PropiedadGetterVF& PropNumVFLFPFFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetterVF* args,uchar numObjeto)const{
  return *new PropNumVFLFPF(obj,(const struct ArgumentosPropNumVFLFPF*)args,numObjeto);
} 
