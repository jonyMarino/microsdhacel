#include "RamSimulaFlash.h"
#include "PromBkpProtected.h"
#include "stddef.h"
#include "IFsh10.h"

byte RamSimulaFlash_setWord(void*,word*,word);
word RamSimulaFlash_getWord(void*,word*);
void *RamSimulaFlash_grabarProm(void*);  
byte RamSimulaFlash_borrarProm(void*self,void*direccion);
  
const struct PromBkpClass RamSimulaFlash={
  PROM_BKP_CLASS_INITIALIZATION(PromBkpClass,
                                RamSimulaFlash,
                                PromBkp,
                                NULL,
                                NULL,
                                NULL,
                                NULL,
                                RamSimulaFlash_getWord,
                                RamSimulaFlash_setWord,
                                RamSimulaFlash_getWord,
                                RamSimulaFlash_setWord,
                                NULL,
                                NULL,
                                RamSimulaFlash_grabarProm,
                                RamSimulaFlash_borrarProm)
};


/*
** ===================================================================
**    Function    :  FlashBkpEnFlash_setWord 
**    Description : 
** ===================================================================
*/
byte RamSimulaFlash_setWord(void* self,word*Address,word valor){
  struct RamSimulaFlash * _f=self;
  
  *Address = valor;
  
  return ERR_OK;
}
/*
** ===================================================================
**    Function    :  FlashBkpEnFlash_getWord 
**    Description : 
** ===================================================================
*/
word RamSimulaFlash_getWord(void*self,word*direccion){
  struct RamSimulaFlash * _f=self;

  return *direccion;

}


/*
** ===================================================================
**    Function    :  FlashBkpEnFlash_grabarProm 
**    Description : 
** ===================================================================
*/
void *RamSimulaFlash_grabarProm(void*self){
  struct RamSimulaFlash * _f=self;
}
/*
** ===================================================================
**    Function    :  FlashBkpEnFlash_borrarProm 
**    Description : 
** ===================================================================
*/
byte RamSimulaFlash_borrarProm(void*self,void*direccion){
  struct RamSimulaFlash * _f=self;
  
  return ERR_OK;    
}

