/*  MODULE: BoxPrincipal.c*/

#include <stddef.h>
#include "Grabacion.h"
#include "display.h"
#include "BoxPrincipal.h"
#include "PromBkp.h"
#include "Mydefines.h"
#include "Configuracion.h"


#pragma DATA_SEG BoxPrincipal_DATA                                            
#pragma CODE_SEG BoxPrincipal_CODE                     
#pragma CONST_SEG DEFAULT       /* Constant section for this module */


#define PRI_PAR_SECONDS  5  //El parametro se muestra 5 segundos luego de 'u' o 'd'

#ifndef TIME_BETWEEN_PARS
  #define TIME_BETWEEN_PARS 2000
#endif  

void BoxPri_DefConstructor(void * self, va_list * args);
BOX_State BoxPri_ProcKey(void*,uchar);
void BoxPri_Destructor(void* self);

const struct BoxClass BoxPri={
  BOXCLASS_INITIALIZATION(BoxClass,
                          BoxPri,
                          Object,
                          BoxPri_DefConstructor,
                          BoxPri_Destructor,
                          NULL,
                          NULL,
                          NULL,
                          BoxPri_ProcKey,
                          NULL) 
};


void BoxPri_ActDpySup(struct BoxPri * self);
/*
** ===================================================================
**     Method      :  BoxPri_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxPri_Constructor(void* self,
                        void * sensor,
                        void *_msj)
{
  struct BoxPri * _box= (struct BoxPri *)self;
  
  _box->snsr1= sensor;
  _box->msjs=_msj;
  _box->msj_index=0;
  
  PromBkp_habilitar(pFlash);
  
  _GetterPrint(sensor,_DPY_SUP);
  
  PasarASCII("tEMP",_DPY_INF);
  
  newAlloced(&_box->timerPri,&Timer,(ulong)TIME_BETWEEN_PARS);

}

/*
** ===================================================================
**     Method      :  BoxPri_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void BoxPri_DefConstructor(void * self, va_list * args){
  struct BlockConstBoxPri * block= va_arg(*args,struct BlockConstBoxPri *); 
  BoxPri_Constructor(self,block->snsr1,block->msjs);    
}
			 
/*
** ===================================================================
**     Method      :  BoxPri_ProcKey 
**     Description :  Procesa la tecla ingresada
** ===================================================================
*/
BOX_State BoxPri_ProcKey(void*self ,uchar tecla){
  struct BoxPri * _box= (struct BoxPri *)self;
  void * sensor= _box->snsr1;
  
  if(Timer_isfinish(&_box->timerPri)){
      if(_box->msjs){     
        char * msj=MessageOut_getMessage(_box->msjs,_box->msj_index);
        if( msj ){
          ++_box->msj_index; 
          PasarASCII(msj,_DPY_INF);
        }else{
          if(_box->msj_index==0)		 //no hay mensajes?
            PasarASCII("tEMP",_DPY_INF);
          else
            _box->msj_index=0;
        }
      }
      _GetterPrint(sensor,_DPY_SUP);
  		Timer_Restart(&_box->timerPri);
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
void BoxPri_Destructor(void* self){
  struct BoxPri * _box= (struct BoxPri *)self;
  
    PromBkp_deshabilitar(pFlash);
  deleteAlloced(&_box->timerPri); 
}
 
/*
** ===================================================================
**     BOX PRINCIPAL 1 CONTROL
** ===================================================================
*/ 
void BoxPri1c_DefConstructor(void * _self, va_list * args);
BOX_State BoxPri1c_ProcKey(void*self ,uchar tecla);
void BoxPri1c_Refresh(void* _self);
void BoxPri1c_Destructor(void* self);

const struct BoxClass BoxPri1c={
    BOXCLASS_INITIALIZATION(BoxClass,
                          BoxPri1c,
                          BoxPri,
                          BoxPri1c_DefConstructor,
                          BoxPri1c_Destructor,
                          NULL,
                          NULL,
                          BoxPri1c_Refresh,
                          BoxPri1c_ProcKey,
                          NULL)
};

/*struct GetterVisual*/void * Pri_getter=NULL;
bool Pri_is_prop;

/*
** ===================================================================
**     Method      :  BoxPri1c_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxPri1c_Constructor(void* _self,
                        void * sensor,
                        void *_msj)
{
  struct BoxPri1c * _box=(struct BoxPri1c *)_self;
  
  BoxPri_Constructor(_self,sensor,_msj);
  
  if(Pri_is_prop)
    PropWInc_Refresh(Pri_getter);
  
  if(Pri_getter)
    _GetterPrint(Pri_getter,_DPY_INF);
 
  newAlloced(&_box->timerProp,&Timer,(ulong)1000);
  
  _box->par_seconds=0;
      
}
/*
** ===================================================================
**     Method      :  BoxPri1c_DefConstructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxPri1c_DefConstructor(void * _self, va_list * args){
  struct BlockConstBoxPri * block= va_arg(*args,struct BlockConstBoxPri *);
  BoxPri1c_Constructor(_self,block->snsr1,block->msjs);    
}

/*
** ===================================================================
**     Method      :  BoxPri_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
void  BoxPri1c_Destructor(void* self){
  struct BoxPri1c * _box= (struct BoxPri1c *)self;
  BoxPri_Destructor(self);
  deleteAlloced(&_box->timerProp);  
}


/*
** ===================================================================
**     Method      :  BoxPri1c_ProcKey 
**     Description :  Procesa la tecla ingresada
** ===================================================================
*/
BOX_State BoxPri1c_ProcKey(void*self ,uchar tecla){
  struct BoxPri1c * _box= (struct BoxPri1c *)self;
  struct BoxPri* _box_b=  (struct BoxPri*)self;
  void * sensor= ((struct BoxPri*)_box)->snsr1;
  void * msjs = ((struct BoxPri*)_box)->msjs;
  uint msj_index = ((struct BoxPri*)_box)->msj_index; 
  
  if( Timer_isfinish( &_box_b->timerPri ) ){
      char * msj=NULL; 

      if( _box->par_seconds==0){        
        msj=MessageOut_getMessage(msjs,msj_index);
      }else
        _box->par_seconds--;
      
      if( msj ){
        ++_box_b->msj_index; 
        PasarASCII(msj,_DPY_INF);
      }else{
          if(Pri_getter)        
               _GetterPrint(Pri_getter,_DPY_INF);
          ((struct BoxPri*)_box)->msj_index=0;
      }
      _GetterPrint(sensor,_DPY_SUP);
  		Timer_Restart( &_box_b->timerPri );
  } 
  
  if(_box->propCambio && Timer_isfinish(&_box->timerProp)){
          _box->propCambio=FALSE;
          PropWInc_Save(Pri_getter);
  }
  
  if(Pri_getter && Pri_is_prop && _box_b->msj_index==0 )	 //no hay mensaje que mostrar
  {
    
      if(tecla == 'd' || tecla == 'u'){
        _box->par_seconds=PRI_PAR_SECONDS; //seguir mostrando el parametro  
        if(tecla == 'd') 
          vPropWInc_Dec(Pri_getter);
        else  
          vPropWInc_Inc(Pri_getter);
        _box->propCambio=TRUE;
        Timer_Restart(&_box->timerProp);
        //PromBkp_demorarGrabado(pFlash,1000);
        _GetterPrint(Pri_getter,_DPY_INF);
        
        return STAY_BOX;
      }
  }
  
  if(PromBkp_grabacionOBorradoEnEspera(pFlash) )    
      return STAY_BOX;

  if(tecla=='r' || tecla=='f'){
    if(_box->propCambio){
        _box->propCambio=FALSE;
        PropWInc_Save(Pri_getter); 
        return STAY_BOX; 
    }
    return EXIT_BOX;
  }
  
  
  return STAY_BOX;
}

/*
** ===================================================================
**     Method      :  BoxPri1c_Refresh
**     Description :  Actualiza el Box
** ===================================================================
*/
void BoxPri1c_Refresh(void* _self){
  struct BoxPri1c * _box=(struct BoxPri1c *)_self;
  
  if(Pri_getter){
    if(Pri_is_prop)
      PropWInc_Refresh(Pri_getter);
    _GetterPrint(Pri_getter,_DPY_INF);
  }
}

/*
** ===================================================================
**     Method      :  BoxPri1c_ShowGetter 
**     Type        :  Static
**     Description :  Muestra el getter al display inferior
** ===================================================================
*/
void BoxPri1c_ShowGetter(void * _getter,
                         void * Obj){
                         
  if(Pri_getter){
    _delete(Pri_getter);
  }
  
  Pri_getter= pGetter_Constructor(_getter,Obj);
  Pri_is_prop=FALSE;

}

/*
** ===================================================================
**     Method      :  BoxPri1c_ShowProp 
**     Type        :  Static
**     Description :  Muestr la propiedad al display inferior
** ===================================================================
*/
void BoxPri1c_ShowProp( const void * _prop,
                        void * Obj){
                         
  if(Pri_getter){
    _delete(Pri_getter);
  }
  
  Pri_getter= pProp_Constructor(_prop,Obj);
  Pri_is_prop=TRUE;

}

