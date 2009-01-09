#include <assert.h>
#include "PlataformaEmbedded.h"
#include "ThreadAdjuntable.h"
#include "Thread.h"

void PlataformaEmbedded_ctor(void * _self,va_list * args);
void PlataformaEmbedded_mainLoop(void * _self);

const struct PlataformaEmbeddedClass PlataformaEmbedded={
  &Class,
  "",
  &Object,
  sizeof(struct PlataformaEmbedded),
  PlataformaEmbedded_ctor,
  NULL,
  Object_differ, // differ
  Object_puto, // puto
  PlataformaEmbedded_mainLoop
};
 

struct ThreadAdjuntable threads;


void PlataformaEmbedded_ctor(void * _self,va_list * args){
  newAlloced(&threads,ThreadAdjuntable);
}

void pthread_create(void * _self,void * attr,void*(*pf)(void*),void* args){
  _self = new(&Method,pf,args);
  ThreadAdjuntable_Adjuntar(&threads,_self);  
}


void PlataformaEmbedded_mainLoop(void * _self){
  MethodContainer_execute(&threads);
}


void mainLoop(void * _self){
  struct PlataformaEmbeddedClass * class = classOf(_self);
  assert(class && class->mainLoop);
  class->mainLoop(_self);  
}

void super_mainLoop(void * _class,void * _self){
  struct PlataformaEmbeddedClass * superclass= super(_class); 

	if(_self && superclass -> mainLoop)
	  superclass -> mainLoop(_self);
}