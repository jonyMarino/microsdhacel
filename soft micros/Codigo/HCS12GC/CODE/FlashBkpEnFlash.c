#include "FlashBkpEnFlash.h"
#include "PromBkpProtected.h"
#include "stddef.h"
#include "IFsh10.h"

byte FlashBkpEnFlash_setWord(void*,word*,word);
word FlashBkpEnFlash_getWord(void*,word*);
//byte FlashBkpEnFlash_setDWord(void*,dword*,dword);
//dword FlashBkpEnFlash_getDWord(void*,dword*);
void *FlashBkpEnFlash_grabarProm(void*);  
byte FlashBkpEnFlash_borrarProm(void*self,void*direccion);
  
const struct PromBkpClass flashBkpEnFlashTable={
  &Class,
  "",
  &Object,
  sizeof(struct FlashBkpEnFlash),
  NULL,
  NULL,
  NULL, // differ
  NULL, // puto
  FlashBkpEnFlash_getWord,
  FlashBkpEnFlash_setWord,
  FlashBkpEnFlash_getWord,
  FlashBkpEnFlash_setWord,
  NULL,
  NULL,
  FlashBkpEnFlash_borrarProm,
  FlashBkpEnFlash_grabarProm 
};


const void * const FlashBkpEnFlash=&flashBkpEnFlashTable;

/*
** ===================================================================
**    Function    :  FlashBkpEnFlash_setWord 
**    Description : 
** ===================================================================
*/
bool PromBkp_isEnIndex(void * self,void * direccion){
  struct FlashBkpEnFlash * _f=self;
  word dir = (word)direccion;
  word mask= 1<<(((dir&(PAGE_SIZE-1))/2)%16);
  word index=(dir&(PAGE_SIZE-1))/32;
  return (_f->indiceFlash[index]&mask)?TRUE:FALSE ;    
}
/*
** ===================================================================
**    Function    :  FlashBkpEnFlash_setWord 
**    Description : 
** ===================================================================
*/
byte FlashBkpEnFlash_setWord(void* self,word*Address,word valor){
  struct FlashBkpEnFlash * _f=self;
  
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
    shift=((Addr&(PAGE_SIZE-1))/2)%16;
    _f->indiceFlash[(Addr&(PAGE_SIZE-1))/32]|= 1<<shift;	 //MSB
    PromBkp_setAGrabar(self,TRUE);
  }
  return ERR_OK;
}
/*
** ===================================================================
**    Function    :  FlashBkpEnFlash_getWord 
**    Description : 
** ===================================================================
*/
word FlashBkpEnFlash_getWord(void*self,word*direccion){
  struct FlashBkpEnFlash * _f=self;
  word dir = (word)direccion;
  
  if(!PromBkp_getAGrabar(self) || !IFsh10_isInPage(direccion,_f->paginaAGrabar) ||   !PromBkp_isEnIndex(self,direccion) ) // con que el primero este para grabar alcanza
    return *direccion;
  else
    return *(word *)&((word*)_f->direccionBkp)[(dir&(PAGE_SIZE-1))/2];

}

/*
** ===================================================================
**    Function    :  FlashBkpEnFlash_grabarProm 
**    Description : 
** ===================================================================
*/
void FlashBkpEnFlash_backupSector(void * self){
  struct FlashBkpEnFlash * _f=self;
  word a;
  byte i;  
  
  for (a=0;a<(PAGE_SIZE/32);a++){
    for (i=0;i<16;i++){
      if (!(_f->indiceFlash[a]&1)){
        word * addr = &(((word*)_f->direccionBkp)[a*16+i]);
        word value = *(((word*)_f->paginaAGrabar)+a*16+i);
        WriteWord(addr,value);
      }
    _f->indiceFlash[a]>>=1;
    }
  }
}
/*
** ===================================================================
**    Function    :  FlashBkpEnFlash_grabarProm 
**    Description : 
** ===================================================================
*/
void *FlashBkpEnFlash_grabarProm(void*self){
  struct FlashBkpEnFlash * _f=self;
  byte err;
  void * paginaTmp = _f->paginaAGrabar;

	 if(_f->escrituraHabilitada){ 
  	 _f->escrituraHabilitada=FALSE;
  	 FlashBkpEnFlash_backupSector(self);                      /* Backup sector */
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
**    Function    :  FlashBkpEnFlash_borrarProm 
**    Description : 
** ===================================================================
*/
byte FlashBkpEnFlash_borrarProm(void*self,void*direccion){
  struct FlashBkpEnFlash * _f=self;
  
  byte err=EraseSectorInternal(direccion);
  if(err)
    return err;
  if(IFsh10_getPage(direccion)==IFsh10_getPage(_f->direccionBkp)){
    PromBkp_setAGrabar(self,FALSE);
    _f->escrituraHabilitada=TRUE;
  }
  
  return ERR_OK;    
}

