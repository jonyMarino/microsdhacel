#include <assert.h>
#include "PlataformaEmbedded.hpp"
#include "Thread.h"
#include "OOC/lang/reflect/lib_cpp/Method.hpp"
#include "WDog1.h"


ThreadAttachable* PlataformaEmbedded::threads;


PlataformaEmbedded::PlataformaEmbedded(){threads=&thread;}


void pthread_create(void ** _self,void * attr,void*(*pf)(void*),void* args){
  struct Method * m = new Method();
  m->pmethod=(Method::pMethod)pf;
  m->obj=args;
  *_self = (void*)m;
  PlataformaEmbedded::threads->adjuntar(m);  
}


void PlataformaEmbedded::mainLoop(void){
  WDog1_Clear();
  threads->executeThreads();
}


