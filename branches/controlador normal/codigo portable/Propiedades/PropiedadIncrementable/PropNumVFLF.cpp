#include "PropNumVFLF.hpp"
//#include "PE/include/PE_Types.h"

const struct PropNumVFLFFactory propNumVFLFFactory;

PropNumVFLF::PropNumVFLF(void*obj,const struct ArgumentosPropNumVFLF* args,uchar numObjeto):PropiedadNumericaVF(obj,(const struct ArgumentosPropiedadIncrementableVF*)args,numObjeto){}

int PropNumVFLF::getLimiteInferior(){
  struct ArgumentosPropNumVFLF* arg= (struct ArgumentosPropNumVFLF*)getArgumentos();
  return arg->limiteInferior;
}

int PropNumVFLF::getLimiteSuperior(){
  struct ArgumentosPropNumVFLF* arg= (struct ArgumentosPropNumVFLF*)getArgumentos();
  return arg->limiteSuperior;
}

uchar PropNumVFLF::getCantidadDecimales(){
  return 0;
}

PropiedadGetterVF& PropNumVFLFFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetterVF* args,uchar numObjeto)const{
  return *new PropNumVFLF(obj,(const struct ArgumentosPropNumVFLF*)args,numObjeto);
} 
