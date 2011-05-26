#include <assert.h>
#include "FlashBkp.hpp"
#include "stddef.h"
#include "flash.h"


FlashBkp::FlashBkp(void * _direccionBkp):direccionBkp(_direccionBkp),escrituraHabilitada(TRUE),paginaAGrabar(NULL){
  Flash_init();
}



const void * FlashBkp::getDireccionBkp(){
  return direccionBkp;
}

/*
** ===================================================================
**    Function    :  FlashBkp_setWord 
**    Description : 
** ===================================================================
*/
byte FlashBkp::setWord(word*Address,word valor){
  word Addr = (word)Address;
  
  if (Addr & 1 || Flash_isInPage(Address,direccionBkp)){
    /* Aligned address ? */
    return ERR_NOTAVAIL;
  }
 

  if(*(word *)Addr!=valor){
    byte shift;
    
    
    if(!escrituraHabilitada)		//no esta libre para escribir?
      return ERR_NOTAVAIL;
    
    if((word)paginaAGrabar==0) 
      paginaAGrabar=(void*)(Addr & (65535 ^ (PAGE_SIZE-1)));
    else if (paginaAGrabar!=(void*)(Addr & (65535 ^ (PAGE_SIZE-1))))
      return ERR_BUSY;      /* Todavia no se grabo la página en cola*/  
  
    Flash_writeWord(&((word*)direccionBkp)[(Addr&(PAGE_SIZE-1))/2], valor);
    setIndexArray(Addr&(PAGE_SIZE-1));
    setAGrabar(TRUE);
  }
  return ERR_OK;
}

byte FlashBkp::setByte(word*address,fbyte valor){
  return setWord(address,valor);
}



/*
** ===================================================================
**    Function    :  FlashBkp_getWord 
**    Description : 
** ===================================================================
*/
word FlashBkp::getWord(word*direccion){
  word dir = (word)direccion;
  
  if(!getAGrabar() || !Flash_isInPage(direccion,paginaAGrabar) ||   !isParaGrabar(dir)) // con que el primero este para grabar alcanza
    return *direccion;
  else
    return *(word *)&((word*)direccionBkp)[(dir&(PAGE_SIZE-1))/2];
}

fbyte FlashBkp::getByte(fbyte*direccion){
  return (fbyte)getWord(direccion);
}

/*
** ===================================================================
**    Function    :  FlashBkp_grabarProm 
**    Description : 
** ===================================================================
*/
void FlashBkp::backupSector(){
  word a;  
  
  for (a=0;a<PAGE_SIZE/2;a+=2){
      if (!getIndexArray(a)){
        word * addr = &(((word*)direccionBkp)[a/2]);
        word value = *(((word*)paginaAGrabar)+a/2);
        Flash_writeWord(addr,value);
    
    }
  }
  clearIndexArray();
}
/*
** ===================================================================
**    Function    :  FlashBkp_grabarProm 
**    Description : 
** ===================================================================
*/
void *FlashBkp::grabarProm(){
  byte err;
  void * paginaTmp = (void*)paginaAGrabar;

	 if(escrituraHabilitada){ 
  	 escrituraHabilitada=FALSE;
  	 backupSector();                      /* Backup sector */
     return direccionBkp;
	 }
   //PromBkp_callPreEraseListeners(self,paginaTmp);
   err=Flash_grabarFlash(paginaTmp,(word *)direccionBkp);
    if(err)
      return NULL;                     /* Return error code if previous operation finished not correctly */
 	 paginaAGrabar=0;  	 
 	 borrarPagina(direccionBkp);
 	 return paginaTmp;  
}
/*
** ===================================================================
**    Function    :  FlashBkp_borrarProm 
**    Description : 
** ===================================================================
*/
byte FlashBkp::borrarProm(void*direccion){
  byte err=Flash_eraseSector(direccion);
  if(err)
    return err;
  if(Flash_getPage(direccion)==Flash_getPage(direccionBkp)){
    setAGrabar(FALSE);
    escrituraHabilitada=TRUE;
  }
  
  return ERR_OK;    
}
/*
** ===================================================================
**    Function    :  isParaGrabar 
**    Description : 
** ===================================================================
*/
bool FlashBkp::isParaGrabar(word dir){
    return getIndexArray(dir&(PAGE_SIZE-1));
}

