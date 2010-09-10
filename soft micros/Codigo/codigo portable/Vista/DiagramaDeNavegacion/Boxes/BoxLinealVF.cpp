#include <stddef.h>
#include "PE/include/PE_Types.h"
#include "BoxLinealVF.hpp"

const struct BoxLinealVFFactory boxLinealVFFactory;

void BoxLinealVF::initBoxLineal (struct ConstructorBoxLinealVF * _constructor){
   constructor =  _constructor;
   numProp=0;
}

BoxLinealVF::BoxLinealVF(struct ConstructorBoxLinealVF * _constructor) {
   initBoxLineal(_constructor); 
}


/*
** ===================================================================
**     Method      :  BoxLineal_Constructor 
**     Description :  Constructor del Box Lineal
** ===================================================================
*/
BoxLinealVF::BoxLinealVF(struct ConstructorBoxLinealVF * _constructor,void*obj,uchar numObjeto){
  initBoxLineal(_constructor);
  mostrarPropiedad(obj,numObjeto);
}

/*
** ===================================================================
**     Method      :  BoxLineal_Destructor 
**     Description :  Destructor del Box Lineal
** ===================================================================
*/
BoxLinealVF::~BoxLinealVF(){
}

/*
** ===================================================================
**     Method      :  BoxLineal_setBox 
**     Description :  Setea los valores de la Propiedad correspondiente
** ===================================================================
*/

void BoxLinealVF::mostrarPropiedad(void * obj,int numObjeto){

  PropiedadIncrementableVF* propiedadActual = (PropiedadIncrementableVF*)&((constructor->propiedades[numProp])->getPropiedad(obj,numObjeto)); 
  
   setPropiedad(*propiedadActual,TRUE);
}

/*
** ===================================================================
**     Method      :  BoxLineal_Refresh 
**     Description :  Procesa la tecla
** ===================================================================
*/
Box * BoxLinealVF::procesarTecla(uchar tecla,TEstadoBox& estado){

  BoxPropiedadVF::procesarTecla(tecla,estado);
  if (tecla=='r'){
    void * obj = getPropiedad()->getObjeto();
    int numObj = getPropiedad()->getNumObjeto();
    numProp++;
    if(constructor->propiedades[numProp]==NULL){    
      estado = EXIT_BOX;
      if(!constructor->proximoBox)
        return NULL;
      return &constructor->proximoBox->getBox(obj,numObj);
    }
    estado=STAY_BOX;  
    mostrarPropiedad(obj,numObj);
  }
  return NULL;
}


struct ConstructorBoxLinealVF * BoxLinealVF::getConstructor (){
  return constructor;
}


uchar BoxLinealVF::getNumProp () {
  return numProp;
}


void BoxLinealVF::setNumProp (uchar n){
   numProp = n;
}
