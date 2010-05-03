#ifndef _FST_BOX_POINTER_HPP
#define _FST_BOX_POINTER_HPP

#include <stdtypes.h>
#include "Box.hpp"

#define SD100

#ifdef SD100

struct FstBoxPointer{	
  const struct ConstructorBox * constructor;
  void* objeto;
  uchar numObjeto;
  Box& getNextBox()const;
};

#else

struct FstBoxPointer{	
  FstBoxPointer(const struct ConstructorBox * ctr,void* obj,uchar numObj);
  Box& getNextBox()const;
  
  private:
    const struct ConstructorBox * constructor;
    void* objeto;
    uchar numObjeto;
   
};

#endif

#endif