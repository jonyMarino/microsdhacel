/* Module BoxPriAdquisidor.c */

#include <stdarg.h>
#include "stdtypes.h"
#include "stddef.h"
#include "BoxPrincipal_protected.h"
#include "BoxPriAdquisidor.h"
#include "display.h"
#include "TimerFlag.h"
                        
void BoxPriAdquisidor_DefConstructor(void * _self, va_list * args);
BOX_State BoxPriAdquisidor_ProcKey(void*self ,uchar tecla); 
void * BoxPriAdquisidor_Destructor(void* self);
                       
const struct BoxClass BoxPriAdquisidor={
    BOXCLASS_INITIALIZATION(BoxClass,
                          BoxPriAdquisidor,
                          BoxPri,
                          BoxPriAdquisidor_DefConstructor,
                          BoxPriAdquisidor_Destructor,
                          NULL,
                          NULL,
                          NULL,
                          BoxPriAdquisidor_ProcKey,
                          NULL)
};

static struct TimerFlag timerSensor;
/*
** ===================================================================
**     Method      :  BoxPri1c_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxPriAdquisidor_Constructor(void* _self,
                        struct SensorVisual * sensor,
                        struct MessageOut *_msj)
{
  struct BoxPriAdquisidor * _box=_self;
  char * msj;
  
  BoxPri_Constructor(_self,sensor,_msj);
  
  msj=MessageOut_getMessage((_box->base).msjs,(_box->base).msj_index);
  PasarASCII(msj,_DPY_INF);
  
  newAlloced(&timerSensor,&TimerFlag,(ulong)1000);
      
}
/*
** ===================================================================
**     Method      :  BoxPri1c_DefConstructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxPriAdquisidor_DefConstructor(void * _self, va_list * args){
  struct BlockConstBoxPri * block= va_arg(*args,void *);
  BoxPriAdquisidor_Constructor(_self,block->snsr1,block->msjs);    
}

/*
** ===================================================================
**     Method      :  BoxPri1c_DefConstructor 
**     Description :  Constructor del Box
** ===================================================================
*/
BOX_State BoxPriAdquisidor_ProcKey(void*self ,uchar tecla){
  struct BoxPriAdquisidor * _box= self;
  struct TSensorDec * sensor= (_box->base).snsr1;
  
  if(TimerFlag_getFlag(&(_box->base).timerPri)){
      if((_box->base).msjs){     
        char * msj=MessageOut_getMessage((_box->base).msjs,(_box->base).msj_index);
        if( msj ){
          PasarASCII(msj,_DPY_INF);
        }
      }
      TimerFlag_reset(&(_box->base).timerPri);
  }
  
  if(TimerFlag_getFlag(&timerSensor)){
    _GetterPrint(sensor,_DPY_SUP);  
    TimerFlag_reset(&timerSensor);
  }
  
  if(tecla=='r' || tecla=='f')
    return EXIT_BOX;
  
  return STAY_BOX;
}


/*
** ===================================================================
**     Method      :  BoxPri_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
void * BoxPriAdquisidor_Destructor(void* self){
  struct BoxPriAdquisidor * _box= self;
  deleteAlloced(&timerSensor);
  return BoxPri_Destructor(self);

}