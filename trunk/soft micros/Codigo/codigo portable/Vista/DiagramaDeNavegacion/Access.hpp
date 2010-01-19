#ifndef _ACCESS_HPP
#define _ACCESS_HPP

#include "OOC/util/lib_cpp/Array.h"
#include "BoxList.hpp"

struct Access{											 // sabe get_new_box
  struct Array/*<BoxList>*/ super;				 
  const int * codigo;
  const char * name;
  Box *getNextBox(uchar list_count,uchar box_count)const;
};


#define NEW_ACCESS(name,arrayBoxList,strName,pCodigo)  \
  struct Access name={                                  \
    INITIALIZATION_ARRAY(Access,arrayBoxList),  \
    pCodigo,																							\
    strName  																							\
}

#endif