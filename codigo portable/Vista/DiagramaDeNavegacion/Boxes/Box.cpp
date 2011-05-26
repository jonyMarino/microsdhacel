#include <stdio.h>
#include "Box.hpp"

Box& ConstructorBox::getBox(void*obj,uchar numObjeto)const{
  return factory->getBox(this,obj,numObjeto);  
}
