/*MODULE RlxFTimer*/


#include <stdarg.h>
#include <stdlib.h>

#include "Cpu.h"
#include "stddef.h"
#include "stdtypes.h"
#include "LinkedList.h"
#include "RlxMTimer.h"

#pragma DATA_SEG RlxMTimer_DATA                                            
#pragma CODE_SEG RlxMTimer_CODE 
#pragma CONST_SEG DEFAULT

void RlxMTimer_DefConstruct(void * _self,va_list * args); 
void RlxMTimer_OnTime(struct RlxMTimer * self);
void *RlxMTimer_Destruct(void * _self);

const struct TimerClass RlxMTimer={
   TIMER_CLASS_INITIALIZATION(TimerClass,RlxMTimer,MethodTimer,RlxMTimer_DefConstruct,RlxMTimer_Destruct,NULL,NULL,RlxMTimer_OnTime)
};

static struct LinkedList list;
static struct LinkedList * _RlxMTCont=NULL;


/*
** ===================================================================
**     Method     : RlxMTimer_Construct
**    Description : Constructor del Objeto
** ===================================================================
*/
void RlxMTimer_Construct(void * _self,ulong tiempo,   void (*pf)(void*),void * Obj ){
void * p_tmp;
struct RlxMTimer * _mt=_self;  
  
  MTimer_Construct(_self,tiempo,pf,Obj);
  _mt->execute=FALSE;
  
  if(!_RlxMTCont){
    newAlloced(&list,&LinkedList);
    _RlxMTCont = &list;
  }
  LinkedList_add(_RlxMTCont,_self);
  
}

/*
** ===================================================================
**     Method     : RlxMTimer_DefConstruct
**    Description : Constructor por defecto del Objeto
** ===================================================================
*/
void RlxMTimer_DefConstruct(void * _self,va_list * args){
  RlxMTimer_Construct(_self,va_arg(*args,ulong),va_arg(*args,void*),va_arg(*args,void*));
}

/*
** ===================================================================
**     Method     : RlxMTimer_DefConstruct
**    Description : Destructor del Objeto
** ===================================================================
*/
void *RlxMTimer_Destruct(void * _self){
  LinkedList_deleteReference(_RlxMTCont,_self);
 // if(LinkedList_Vacia(_RlxMTCont))
 //   deleteAndNil(&_RlxMTCont);
  return Timer_Destruct(_self);
}

/*
** ===================================================================
**     Method      :  RlxMTimer_OnTime 
**    Description : funcion a llamar cuando se llega al tiempo
** ===================================================================
*/
void RlxMTimer_OnTime(struct RlxMTimer * self){
  self->execute=TRUE;
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
void RlxMTimer_Handler(void){
  if(_RlxMTCont){     
    uint i;
    struct LinkedListIterator it;
    LinkedList_linkedListIterator(_RlxMTCont,&it);
    
    while(LinkedListIterator_hasNext(&it)){
      struct RlxMTimer * _rmt= LinkedListIterator_next(&it); 
      if(_rmt && _rmt->execute){
        _rmt->execute=FALSE;
        (*(_rmt->_base.pf))(_rmt->_base.Obj);  
      }
       
    }
  }
}


