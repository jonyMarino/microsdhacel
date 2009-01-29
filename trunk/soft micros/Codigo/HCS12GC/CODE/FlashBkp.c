#include <assert.h>
#include "FlashBkp.h"
#include "PromBkpProtected.h"
#include "stddef.h"
#include "IFsh10.h"



bool getIndexArray(void * _self,word address){
  struct FlashBkpClass * class = classOf(_self);
  assert(class && class->getIndexArray );
  return class->getIndexArray( _self , address ); 
}

void setIndexArray(void * _self,word address){
  struct FlashBkpClass * class = classOf(_self);
  assert(class && class->setIndexArray );
  class->setIndexArray( _self , address ); 
}

void clearIndexArray(void * _self){
  struct FlashBkpClass * class = classOf(_self);
  assert(class && class->clearIndexArray );
  class->clearIndexArray( _self ); 
}

word * FlashBkp_getDireccionBkp(void* _self){
  struct FlashBkp * self= _self;
  return self->direccionBkp;
}

/*
** ===================================================================
**    Function    :  FlashBkp_setWord 
**    Description : 
** ===================================================================
*/
byte FlashBkp_setWord(void* self,word*Address,word valor){
  struct FlashBkp * _f=self;
  
  word Addr = (word)Address;
  
  if (Addr & 1 || IFsh10_isInPage(Address,_f->direccionBkp)){
    /* Aligned address ? */
    return ERR_NOTAVAIL;
  }
 

  if(*(word *)Addr!=valor){
    byte shift;
    
    
    if(!_f->escrituraHabilitada)		//no esta libre para escribir?
      return ERR_NOTAVAIL;
    
    if((word)_f->paginaAGrabar==0) 
      _f->paginaAGrabar=(void*)(Addr&65024);
    else if (_f->paginaAGrabar!=(void*)(Addr&65024))
      return ERR_BUSY;      /* Todavia no se grabo la página en cola*/  
  
    WriteWord(&((word*)_f->direccionBkp)[(Addr&(PAGE_SIZE-1))/2], valor);
    setIndexArray(self,Addr&(PAGE_SIZE-1));
    PromBkp_setAGrabar(self,TRUE);
  }
  return ERR_OK;
}
/*
** ===================================================================
**    Function    :  FlashBkp_getWord 
**    Description : 
** ===================================================================
*/
word FlashBkp_getWord(void*self,word*direccion){
  struct FlashBkp * _f=self;
  word dir = (word)direccion;
  
  if(!PromBkp_getAGrabar(self) || !IFsh10_isInPage(direccion,_f->paginaAGrabar) ||   !getIndexArray(self,dir)/*PromBkp_isEnIndex(self,direccion) */) // con que el primero este para grabar alcanza
    return *direccion;
  else
    return *(word *)&((word*)_f->direccionBkp)[(dir&(PAGE_SIZE-1))/2];

}

/*
** ===================================================================
**    Function    :  FlashBkp_grabarProm 
**    Description : 
** ===================================================================
*/
void FlashBkp_backupSector(void * self){
  struct FlashBkp * _f=self;
  word a;  
  
  for (a=0;a<PAGE_SIZE/2;a++){
      if (getIndexArray(self,a)){
        word * addr = &(((word*)_f->direccionBkp)[a]);
        word value = *(((word*)_f->paginaAGrabar)+a);
        WriteWord(addr,value);
    
    }
  }
  clearIndexArray(self);
}
/*
** ===================================================================
**    Function    :  FlashBkp_grabarProm 
**    Description : 
** ===================================================================
*/
void *FlashBkp_grabarProm(void*self){
  struct FlashBkp * _f=self;
  byte err;
  void * paginaTmp = _f->paginaAGrabar;

	 if(_f->escrituraHabilitada){ 
  	 _f->escrituraHabilitada=FALSE;
  	 FlashBkp_backupSector(self);                      /* Backup sector */
     return _f->direccionBkp;
	 }
   //PromBkp_callPreEraseListeners(self,paginaTmp);
   err=IFsh10_GrabarFlash(paginaTmp,_f->direccionBkp);
    if(err)
      return NULL;                     /* Return error code if previous operation finished not correctly */
 	 _f->paginaAGrabar=0;  	 
 	 PromBkp_borrarPagina(self,_f->direccionBkp);
 	 return paginaTmp;  
}
/*
** ===================================================================
**    Function    :  FlashBkp_borrarProm 
**    Description : 
** ===================================================================
*/
byte FlashBkp_borrarProm(void*self,void*direccion){
  struct FlashBkp * _f=self;
  
  byte err=EraseSectorInternal(direccion);
  if(err)
    return err;
  if(IFsh10_getPage(direccion)==IFsh10_getPage(_f->direccionBkp)){
    PromBkp_setAGrabar(self,FALSE);
    _f->escrituraHabilitada=TRUE;
  }
  
  return ERR_OK;    
}

