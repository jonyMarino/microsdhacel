#include "FstBoxPointer.hpp"

/*
** =====================================================================
**    Method      :  FBP_getNextBox 
**    Description :  Obtiene el Box inicial del fst box pointer
** =====================================================================
*/
Box *FstBoxPointer::getNextBox()const{
  return constructor->getBox(objeto,numObjeto);  
}
