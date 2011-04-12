#include <stddef.h>
#include "NodoICModBus.hpp"
#include "PropiedadIncrementable.hpp"
#include "PE_Error.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////USAR COMO EN LOS BOXES CREANDO EL GETTER/PROPIEDAD////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int NodoICModBus::getDato(void * dir) {
                      
  if(!contieneDireccion(dir))  
    return 0; //cambiar: error     
      
  ConstructorPropGetterVisual * constGetter= (ConstructorPropGetterVisual *)Array_get( getsProps.arrayConstructores , ((size_t)dir - (size_t)dirIni) /2);
  return ((struct ArgumentosPropiedadGetter*)&constGetter->args)->get(obj);    
}

bool NodoICModBus::contieneDireccion(void * dir) {
  if(dirIni<=dir && getDirFin()>=dir)
    return TRUE;
  return FALSE;
}

bool NodoICModBus::setDato(void * dir,int dato) {  
  if(!contieneDireccion(dir))  
    return 1; //cambiar: error
  if(!getsProps.isPropiedad)
    return ERR_VALUE;  
  ConstructorPropGetterVisual * constGetter= (ConstructorPropGetterVisual *)Array_get( getsProps.arrayConstructores , ((size_t)dir - (size_t)dirIni) /2);
  PropiedadGetter*p = &constGetter->getPropiedad(obj,0);  
  ((PropiedadIncrementable*)p)->setValorTmp(dato);
  ((PropiedadIncrementable*)p)->guardar();
  delete p;
  return ERR_OK;
}

const void * NodoICModBus::getDirFin() {
  return (const void *)((size_t)dirIni + (size_t) Array_count(getsProps.arrayConstructores) * 2) ;
}

const void * NodoICModBus::getDirIni() {
  return dirIni;
}

const struct Array/*<Getter>*/ * NodoICModBus::getGetter() {
  return getsProps.arrayConstructores;
}

bool NodoICModBus::isEscribible(){
  return getsProps.isPropiedad;
}

void * NodoICModBus::getObj() {
  return obj;
}

