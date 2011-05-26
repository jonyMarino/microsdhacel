//#include <typeinfo>
#include <stddef.h>
#include "PE/include/PE_Types.h"
#include "BoxSaltoCondicional.hpp"
#include "obtenciondisplay.hpp"

const struct BoxSaltoCondicionalFactory boxSaltoCondicionalFactory;
/*
** ===================================================================
**     Method      :  BoxSaltoCondicional_Constructor 
**     Description :  Constructor del Box Lineal
** ===================================================================
*/
BoxSaltoCondicional::BoxSaltoCondicional(struct ConstructorBoxSaltoCondicional * _constructor,void*obj,uchar numObjeto):BoxPropiedad(){
  constructor =  _constructor;

  propiedad = (PropiedadIncrementable*)&((constructor->propiedad)->getPropiedad(obj,numObjeto));
  setPropiedad(*propiedad,TRUE);
}

/*
** ===================================================================
**     Method      :  BoxSaltoCondicional_Destructor 
**     Description :  Destructor del Box Lineal
** ===================================================================
*/
BoxSaltoCondicional::~BoxSaltoCondicional(){
}

/*
** ===================================================================
**     Method      :  BoxSaltoCondicional_Refresh 
**     Description :  Procesa la tecla
** ===================================================================
*/
Box * BoxSaltoCondicional::procesarTecla(uchar tecla,TEstadoBox& estado){

  BoxPropiedad::procesarTecla(tecla,estado);
  if (tecla=='r' || tecla=='f'){
    estado = EXIT_BOX;
    return  (*(constructor->getNextBox))(propiedad,tecla);
  }
  return NULL;

}

