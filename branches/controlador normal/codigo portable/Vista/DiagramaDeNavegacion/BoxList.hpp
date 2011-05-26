#ifndef _BOX_LIST_HPP
#define _BOX_LIST_HPP

#include "OOC/util/lib_cpp/Array.h"
#include "Box.hpp"

struct BoxList{										 
  struct Array/*<FstBoxPointer>*/ super;
  const char * nombre; 
  Box *getNextBox(uchar box_count)const;
};

#define NEW_BOX_LIST(NAME,arrayFstBoxes,STR_NAME)  \
  struct BoxList NAME ={									\
    INITIALIZATION_ARRAY(arrayFstBoxes),  \
    STR_NAME															\
  }
#endif