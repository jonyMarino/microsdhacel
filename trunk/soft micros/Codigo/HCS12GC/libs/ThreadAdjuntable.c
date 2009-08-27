#include "ThreadAdjuntable.h"

void MethodContainer_Defconstructor(void * _self,va_list * args);
void *MethodContainer_Destructor(void* _self);

const struct Class TableThreadAdjuntable={
  &Class,
  "",
  &Object,
  sizeof(struct ThreadAdjuntable),
  MethodContainer_Defconstructor,
  MethodContainer_Destructor,
    NULL, // differ
  NULL, // puto
};


const void * const ThreadAdjuntable= &TableThreadAdjuntable;


struct AdjuntadorAHilo * ThreadAdjuntable_getAdjuntador(void * _self){
  struct ThreadAdjuntable * _t = _self;
  
  return _new(&AdjuntadorAHilo,_t);
}
