#include "FstBoxPointer.hpp"

#ifndef SD100

FstBoxPointer::FstBoxPointer(const struct ConstructorBox * ctr,void* obj,uchar numObj){
  constructor=ctr;
  objeto=obj;
  numObjeto=numObj;

}

#endif

/*
** =====================================================================
**    Method      :  FBP_getNextBox 
**    Description :  Obtiene el Box inicial del fst box pointer
** =====================================================================
*/
Box& FstBoxPointer::getNextBox()const{
  return constructor->getBox(objeto,numObjeto);  
}
