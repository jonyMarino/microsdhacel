#include <assert.h>
#include "PlataformaEmbedded.hpp"
#include "Thread.h"
#include "Method.hpp"
#include "WDog1.h"


ThreadAttachable PlataformaEmbedded::threads;

void pthread_create(void * _self,void * attr,void*(*pf)(void*),void* args){
  struct Method * m = new Method();
  m->pmethod=(Method::pMethod)pf;
  m->obj=args;
  _self = (void*)m;
  PlataformaEmbedded::threads.adjuntar(m);  
}


void PlataformaEmbedded::mainLoop(void){
  WDog1_Clear();
  threads.executeThreads();
}

