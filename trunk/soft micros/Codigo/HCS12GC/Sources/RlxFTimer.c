/*MODULE RlxFTimer*/


#include <stdarg.h>
#include <stdlib.h>

#include "Cpu.h"
#include "stddef.h"
#include "stdtypes.h"
#include "FunctionContainer.h"
#include "RlxFTimer.h"

 
void RlxFTimer_OnTime(struct RlxFTimer * self);

const T_Timer TableRlxFTimer={
  sizeof(struct RlxFTimer),
  FTimer_DefConstruct,
  NULL,
  Timer_Destruct,
  RlxFTimer_OnTime
};

const void *const RlxFTimer=&TableRlxFTimer;

static struct FncContainer * _FnCont=NULL;
/*
** ===================================================================
**     Method      :  RlxFTimer_OnTime 
**    Description : funcion a llamar cuando se llega al tiempo
** ===================================================================
*/
void RlxFTimer_OnTime(struct RlxFTimer * self){
  if(!_FnCont)
    _FnCont=newObj(FncContainer);	 
  FncContainer_Add(_FnCont,_FTimer_getFunction(self)); 
}

/*
** ===================================================================
**    Event       :  RlxFTimer_Handler 
**    Type        :  Static
**    Description :  Manejador a llamar para ejecutar las funciones
** ===================================================================
*/
void RlxFTimer_Handler(void){
  if(_FnCont){
      FncContainer_Execute(_FnCont);
      Cpu_DisableInt();
      if(FncContainer_isEmpty(_FnCont))
        deleteObj(&_FnCont);
      Cpu_EnableInt();      
  }
    
}


