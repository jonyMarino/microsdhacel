#include "ThreadAttachable.hpp"


/*
** ===================================================================
**     Method      :  AdjuntadorAHilo_adjuntar 
**     Description :  adjunta el metodo al hilo de ejecucion
** ===================================================================
*/

void ThreadAttachable::adjuntar(struct Method * method){
  if(!method)
    return; //error thow exception
  add(method);
}

void ThreadAttachable::executeThreads(){
  //executeMethods();
  typedef void*(*pf)(void*);
  LinkedListIterator it;
  
  linkedListIterator(&it);
  
  while(it.hasNext()){
    struct Method * m = (struct Method *)it.next();
    (*((pf)(m->pmethod)))(m->obj);
  }
}

ThreadAttachable::ThreadAttacher * ThreadAttachable::getAdjuntador(void){
  return new  ThreadAttacher(this);
}

/*
** ===================================================================
**     Method      :  AdjuntadorAHilo_constructor 
**     Description :  Constructor de la clase
** ===================================================================
*/
ThreadAttachable::ThreadAttacher::ThreadAttacher(ThreadAttachable * thread){  
  threadAdjuntable = thread;   
}


/*
** ===================================================================
**     Method      :  AdjuntadorAHilo_adjuntar 
**     Description :  adjunta el metodo al hilo de ejecucion
** ===================================================================
*/

void ThreadAttachable::ThreadAttacher::adjuntar(struct Method * method){
  if(!method)
    return; //error thow exception
  threadAdjuntable->add(method);
}
