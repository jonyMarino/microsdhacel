/*MODULE RlxMTimer*/


#include <stdlib.h>


#include "stddef.h"
#include "stdtypes.h"
#include "RlxMTimer.hpp"
#include "Thread/Thread.h"

#pragma DATA_SEG RlxMTimer_DATA                                            
#pragma CODE_SEG RlxMTimer_CODE 
#pragma CONST_SEG DEFAULT




/*
** ===================================================================
**     Method     : RlxMTimer_Construct
**    Description : Constructor del Objeto
** ===================================================================
*/
RlxMTimer::RlxMTimer(ulong tiempo,struct Method& metodo ):MethodTimer(tiempo,metodo){
  void *thread;  

  execute=FALSE;
  
  if(!rlxMTCont){    
    rlxMTCont=new LinkedList();
    pthread_create(&thread,NULL,RlxMTimer::handler,NULL);
  }
  
  rlxMTCont->add(this);

}

/*
** ===================================================================
**     Method     : RlxMTimer_DefConstruct
**    Description : Destructor del Objeto
** ===================================================================
*/
RlxMTimer::~RlxMTimer(){
  rlxMTCont->moveOut(this);
 // if(rlxMTCont->isEmpty())
 //   delete(rlxMTCont);
}

/*
** ===================================================================
**     Method      :  RlxMTimer_OnTime 
**    Description : funcion a llamar cuando se llega al tiempo
** ===================================================================
*/
void RlxMTimer::onTime(){ 
  execute=TRUE;
}

/*
** ===================================================================
**    Event       :  RlxMTimer_Handler 
**    Type        :  Static
**    Description :  Manejador a llamar para ejecutar las funciones
** en caso de que se borre algun timer al llamar a su funcion pf,
** el siguiente timer no se ejecutara hasta la siguiente llamada al Handler  
** ===================================================================
*/
void * RlxMTimer::handler(void * a){
  if(rlxMTCont){     
    uint i;
    LinkedList::LinkedListIterator it;
    rlxMTCont->linkedListIterator(&it);
    
    while(it.hasNext()){
      struct RlxMTimer * _rmt= (struct RlxMTimer *)it.next(); 
      if(_rmt && _rmt->execute){
        _rmt->execute=FALSE;
        _rmt->getMetodo().execute();  
      }       
    }
  }
  return NULL;
}


