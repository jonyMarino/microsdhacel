#include "FstBoxPointer.hpp"


FstBoxPointer::FstBoxPointer(const struct ConstructorBox * ctr,void* obj,uchar numObj){
  constructor=ctr;
  objeto=obj;
  numObjeto=numObj;

}





/*
** =====================================================================
**    Method      :  FBP_getNextBox 
**    Description :  Obtiene el Box inicial del fst box pointer
** =====================================================================
*/
Box& FstBoxPointer::getNextBox()const{
  return constructor->getBox(objeto,numObjeto);  
}
