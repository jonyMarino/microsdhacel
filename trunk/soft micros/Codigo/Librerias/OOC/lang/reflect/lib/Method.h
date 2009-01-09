#ifndef _METHOD_H
#define _METHOD_H

#include "Object.h"

#pragma DATA_SEG METHOD_DATA                                            
#pragma CODE_SEG METHOD_CODE 
#pragma CONST_SEG DEFAULT

typedef void (*pMethod)(void*);

struct Method{
  void * Class;
  pMethod pmethod;
  void* Obj;
};


extern const struct Class Method;

void Method_execute(void * self);

pMethod Method_getMethod(void * self);

void Method_setMethod(void * self,pMethod method);

void * Method_getObj(void * self); 


#define NEW_METHOD(name,method,obj)  \
  struct Method name={               \
    &Method,                         \
    method,                          \
    obj                              \
  }

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 

#endif