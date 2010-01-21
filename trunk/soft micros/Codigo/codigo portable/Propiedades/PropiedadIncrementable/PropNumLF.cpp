#include "PropNumLF.hpp"
//#include "PE/include/PE_Types.h"

const struct PropNumLFFactory propNumLFFactory;

PropNumLF::PropNumLF(void*obj,const struct ArgumentosPropNumLF* args):PropiedadNumerica(obj,(const struct ArgumentosPropiedadIncrementable*)args){}

int PropNumLF::getLimiteInferior(){
  struct ArgumentosPropNumLF* arg= (struct ArgumentosPropNumLF*)getArgumentos();
  return arg->limiteInferior;
}

int PropNumLF::getLimiteSuperior(){
  struct ArgumentosPropNumLF* arg= (struct ArgumentosPropNumLF*)getArgumentos();
  return arg->limiteSuperior;
}

uchar PropNumLF::getCantidadDecimales(){
  return 0;
}

PropiedadGetter& PropNumLFFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args)const{
  return *new PropNumLF(obj,(const struct ArgumentosPropNumLF*)args);
} 
