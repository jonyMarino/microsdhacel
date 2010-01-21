#include "PropiedadTextual.hpp"
#include "PE/include/PE_Types.h"
#include "OOC/lang/CharPointer.hpp"

const struct PropiedadTextualFactory propiedadTextualFactory;

PropiedadTextual::PropiedadTextual(void*obj,const struct ArgumentosPropiedadTextual* args):PropiedadIncrementable(obj,(const struct ArgumentosPropiedadIncrementable*)args){}


void PropiedadTextual::print(OutputStream&os){
  int valor= getVal();
  struct ArgumentosPropiedadTextual* arg= (struct ArgumentosPropiedadTextual*)getArgumentos();
  char * str= (*(arg->getTxt))((uchar)valor);
  
  os.write(str); 
}

void PropiedadTextual::incrementar(){
  int valorTmp= getVal();
  byte limSup =  ((struct ArgumentosPropiedadTextual*)getArgumentos())->maximoValorTexto -1;
  
  if(valorTmp<limSup){
    valorTmp++;
	  setValorTmp(valorTmp); 
  }
}

void PropiedadTextual::decrementar(){
  int valorTmp= getVal();
	if (valorTmp > 0){
		  valorTmp--;
		  setValorTmp(valorTmp); 
	}
	  
}

PropiedadGetter& PropiedadTextualFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args)const{
  return *new PropiedadTextual(obj,(const struct ArgumentosPropiedadTextual*)args);
} 
