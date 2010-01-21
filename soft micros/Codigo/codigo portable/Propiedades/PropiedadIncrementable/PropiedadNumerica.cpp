#include "PropiedadNumerica.hpp"
#include "PE/include/PE_Types.h"

PropiedadNumerica::PropiedadNumerica(void*obj,const struct ArgumentosPropiedadIncrementable* args):PropiedadIncrementable(obj,args){}


void PropiedadNumerica::print(OutputStream&os){
  os.writeAsFloat(getVal(),getCantidadDecimales()); 
}

void PropiedadNumerica::incrementar(){
  int valorTmp= getVal();
  int limSup =  getLimiteSuperior();
  
  if(valorTmp<limSup){
    valorTmp++;
	  setValorTmp(valorTmp); 
  }
}

void PropiedadNumerica::decrementar(){
  int valorTmp= getVal();
  int limInf =  getLimiteInferior();
  
	if (valorTmp > limInf){
		  valorTmp--;
		  setValorTmp(valorTmp); 
	}
	  
}

