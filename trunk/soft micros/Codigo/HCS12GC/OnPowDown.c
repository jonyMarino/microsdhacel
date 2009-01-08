/*MODULE: OnPowDown (on power down and rise)

  Este objeto, actua ante una caida de alimentacion detectada 
mediante un modulo de menor nivel, y actua ante la subida de alimentacion.
*/

#include "Cpu.h"
#include "OnPowDown.h"
#include "FTimer.h"
#include "OnPowDownProtected.h"
#include "timer_interrupt.h"
#include "PWSN.h"

#define PWSN_TICKS  30  /*periodos en llamar a PWSN_Handler para que 
                        se active el evento*/  

static bool EnPwsn=FALSE;

void OnPowDown_DefConstructor(void * _self,va_list * args);
void * OnPowDown_Destructor(void * _self);

const struct Class OnPowDown={
  CLASS_INITIALIZATION(Class,
                        OnPowDown,
                        Object,
                        OnPowDown_DefConstructor,
                        OnPowDown_Destructor,
                        Object_differ,
                        Object_puto)
};

static struct OnPowDown * _onpow=NULL;

void OnPowDown_onPowDown(void * _self);
/*
** ===================================================================
**     Method      :  OnPowDown_Constructor 
**     Description :  Constructor del objeto
** ===================================================================
*/
void OnPowDown_Constructor(void * _self){
  struct OnPowDown * _opd=_self;
  newAlloced(&_opd->listeners,&MethodContainer);
  add1msListener(OnPowDown_handler,_self);   
}
															
/*
** ===================================================================
**     Method      :  OnPowDown_DefConstructor 
**     Description :  Constructor por defecto del objeto
** ===================================================================
*/
void OnPowDown_DefConstructor(void * _self,va_list * args){
  OnPowDown_Constructor(_self);    
}

void* OnPowDown_getInstance(void){
  if(!_onpow)
    _onpow = new(&OnPowDown);
  return _onpow;
}

/*
** ===================================================================
**     Method      :  OnPowDown_Destructor
**     Description :  Destructor  del objeto
** ===================================================================
*/
void * OnPowDown_Destructor(void * _self){
  struct OnPowDown * _opd=_self;
  deleteAlloced(&_opd->listeners);
  return _self; 
}

/*
** ===================================================================
**     Event      :  PWSN_Handler 
**
**     Description :
**         Este evento se llama cada periodo para controlar si 
**     hubo una caida de energia.
** ===================================================================
*/

void OnPowDown_handler(void * _self){
    static byte pwsn;
    if (PWSN_GetVal() && EnPwsn)		    //Pwsn is high??
    {		 
      pwsn++;									// inc counter
      if (pwsn== PWSN_TICKS){  			
			  OnPowDown_onPowDown(_self);
			  EnPwsn = FALSE;
      }
    }else pwsn=0;							 // put counter=0
    #ifdef DEBUG 
    {     
      extern byte powdown;
      if(powdown){
			  OnPowDown_onPowDown(_self);        
      }
    }
    #endif
}

/*
** ===================================================================
**     Method      :  PWSN_Able 
**
**     Description :  Habilita el senseo de la caida de energia
**
** ===================================================================
*/
void OnPowDown_enable(void * _self){
  EnPwsn=TRUE;  
}

/*
** ===================================================================
**     Event       :  OnPowDown_handler 
**     Description :
**         Funcion a llamar ante caida de energia
** ===================================================================
*/
void OnPowDown_onPowDown(void * _self){
  uint i;
  Cpu_DisableInt();
      /*  
  			#ifdef _PROGRAMADOR
        GuardarPrograma();
        #endif					 */
        
  if(_onpow){
    MethodContainer_execute(&_onpow->listeners);
  }
  Cpu_EnableInt();

}

/*
** ===================================================================
**     Event       :  OnPowDown_addMethod 
**     Description :
**         Agrega un metodo a llamar ante caida de energia
** ===================================================================
*/
void OnPowDown_addPowDownListener(void * _self,struct Method *metodo){
  struct OnPowDown * self=_self;
  MethodContainer_add(& self->listeners,metodo);
}


