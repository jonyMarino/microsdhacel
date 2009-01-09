#ifndef _LIST_H
#define _LIST_H

#include "Collection.h"

struct ListClass{
  struct CollectionClass super;
  struct Object * (*get)(void *_self,uint index);          
};

extern const void * const List;

struct Object * get(void *_self,uint index); 
  
#endif 