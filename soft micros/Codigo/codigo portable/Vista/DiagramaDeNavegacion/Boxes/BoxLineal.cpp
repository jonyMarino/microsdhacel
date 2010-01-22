//#include <typeinfo>
#include <stddef.h>
#include "PE/include/PE_Types.h"
#include "BoxLineal.hpp"

const struct BoxLinealFactory boxLinealFactory;
/*
** ===================================================================
**     Method      :  BoxLineal_Constructor 
**     Description :  Constructor del Box Lineal
** ===================================================================
*/
BoxLineal::BoxLineal(struct ConstructorBoxLineal * _constructor,void*obj,uchar numObjeto):BoxPropiedad(){
  constructor =  _constructor;
  numProp=0;
  mostrarPropiedad(obj,numObjeto); 
  
}

/*
** ===================================================================
**     Method      :  BoxLineal_Destructor 
**     Description :  Destructor del Box Lineal
** ===================================================================
*/
BoxLineal::~BoxLineal(){
}

/*
** ===================================================================
**     Method      :  BoxLineal_setBox 
**     Description :  Setea los valores de la Propiedad correspondiente
** ===================================================================
*/

void BoxLineal::mostrarPropiedad(void * obj,int numObjeto){

  PropiedadIncrementable* propiedadActual = (PropiedadIncrementable*)&((constructor->propiedades[numProp])->getPropiedad(obj,numObjeto)); 
  setPropiedad(*propiedadActual,TRUE);
}

/*
** ===================================================================
**     Method      :  BoxLineal_Refresh 
**     Description :  Procesa la tecla
** ===================================================================
*/
Box * BoxLineal::procesarTecla(uchar tecla,TEstadoBox& estado){

  BoxPropiedad::procesarTecla(tecla,estado);
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

