 /*  MODULE: BoxPrincipalNC.c*/

#include <stddef.h>
#include "Grabacion.h"
#include "display.h"
#include "BoxPrincipalNC.h"
#include "PromBkp.h"

#pragma DATA_SEG BoxPrincipalNC_DATA                                            
#pragma CODE_SEG BoxPrincipalNC_CODE                     
#pragma CONST_SEG DEFAULT       /* Constant section for this module */

void BoxPriNC_DefConstructor(void * self, va_list * args);
BOX_State BoxPriNC_ProcKey(void*,uchar);
void * BoxPriNC_Destructor(void* self);

const struct BoxClass BoxPriNC={
               BOXCLASS_INITIALIZATION(BoxClass,
                          BoxPriNC,
                          Box,
                          BoxPriNC_DefConstructor,
                          BoxPriNC_Destructor,
                          NULL,
                          NULL,
                          NULL,
                          BoxPriNC_ProcKey,
                          NULL)
};

extern struct FlashBkpEnFlash flash;
static struct PromBkp *const pFlash=&flash;


void BoxPriNC_ActDpySup(struct BoxPriNC * self);
/*
** ===================================================================
**     Method      :  BoxPriNC_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxPriNC_Constructor(void* self,
                        struct ArrayList * getters,
                        struct MessageOut *_msj)
{
  struct BoxPriNC * _box= self;
  byte i;
  byte tamanio = size(getters);
  
  _box->getters= getters;
  _box->msjs=_msj;

     
  for(i=0;i<tamanio;i++){   
    _box->msj_index[i]=0;  
    _GetterPrint(get(getters,i) ,i);
  }
  PromBkp_habilitar(pFlash);
  
  //_GetterPrint(sensor,_DPY_SUP);
  
  newAlloced(&_box->timerPri,&Timer,(ulong)1000);

}

/*
** ===================================================================
**     Method      :  BoxPriNC_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void BoxPriNC_DefConstructor(void * self, va_list * args){
  struct BlockConstBoxPriNC * block= va_arg(*args,void *); 
  BoxPriNC_Constructor(self,block->getters,block->msjs);    
}
			 
/*
** ===================================================================
**     Method      :  BoxPriNC_ProcKey 
**     Description :  Procesa la tecla ingresada
** ===================================================================
*/
BOX_State BoxPriNC_ProcKey(void*self ,uchar tecla){
  struct BoxPriNC * _box= self;
  byte i,tamanio = sizeOf(_box->getters);
  char * msj;
  
  if(Timer_isfinish(&_box->timerPri)){
      for(i=0;i<CANTIDAD_DISPLAYS;i++){        
        if(_box->msjs && (msj=MessageOut_getMessage(&_box->msjs[i],_box->msj_index[i])) ){
            PasarASCII(msj,i);
            ++_box->msj_index[i]; 
        }else if(i<tamanio){            
            _GetterPrint(get(_box->getters,i),i);
            _box->msj_index[i]=0;
        }
      }
  		Timer_Restart(&_box->timerPri);
  }
  if(tecla=='r' || tecla=='f'){
    if(!PromBkp_grabacionOBorradoEnEspera(pFlash))
      return EXIT_BOX;
  }
  return STAY_BOX;
}

/*
** ===================================================================
**     Method      :  BoxPriNC_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
void * BoxPriNC_Destructor(void* self){
  struct BoxPriNC * _box= self;
  
  PromBkp_deshabilitar(pFlash);
  deleteAlloced(&_box->timerPri);
  return self;  
}
 