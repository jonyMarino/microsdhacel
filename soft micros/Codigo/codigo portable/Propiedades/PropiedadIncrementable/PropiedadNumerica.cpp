#include "PropiedadNumerica.hpp"
#include "PE/include/PE_Types.h"

PropiedadNumerica::PropiedadNumerica(void*obj,const struct ArgumentosPropiedadIncrementable* args,uchar numObjeto):PropiedadIncrementable(obj,args,numObjeto){}


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


void PropiedadNumerica::setValor(int valor){
  int limInf =  getLimiteInferior();  
  int limSup =  getLimiteSuperior();
  
  if (valor > limInf && valor<limSup)
    setValorTmp(valor);
}

