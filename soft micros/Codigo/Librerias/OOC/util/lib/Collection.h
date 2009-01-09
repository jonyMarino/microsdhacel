#ifndef _COLLECTION_H
#define _COLLECTION_H

#include "Object.h"
#include "Iterator.h"

struct CollectionClass{
  struct Class super;
  bool (*add)(void * _self,void * obj);
  void (*clear)(void * _self);
  bool (*contains)(void * _self,void * obj);   
  bool (*isEmpty)(void * _self);
  struct Iterator * (*iterator)(void * _self);
  bool (*moveOut)(void * _self,void * obj); 
  uint (*size)(void * _self);       
};

extern const void * const Collection;


bool add(void * _self,void * obj);
void clear(void * _self);
bool contains(void * _self,void * obj);   
bool isEmpty(void * _self);
struct Iterator * iterator(void * _self);
bool moveOut(void * _self,void * obj); 
uint size(void * _self); 
  
#endif