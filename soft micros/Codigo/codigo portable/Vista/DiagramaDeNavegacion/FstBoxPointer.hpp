#ifndef _FST_BOX_POINTER_HPP
#define _FST_BOX_POINTER_HPP

#include <stdtypes.h>
#include "Box.hpp"

struct FstBoxPointer{	
  struct ConstructorBox * constructor;
  void* objeto;
  uchar numObjeto;
  Box * getNextBox()const;
};


#endif