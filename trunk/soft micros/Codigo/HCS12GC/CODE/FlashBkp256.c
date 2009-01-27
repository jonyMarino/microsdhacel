#include "FlashBkp256.h"
#include "PromBkpProtected.h"
#include "stddef.h"
#include "IFsh10.h"

byte FlashBkp256_setWord(void*,word*,word);
word FlashBkp256_getWord(void*,word*);

bool FlashBkp256_getIndexArray(void * _self,word);
void FlashBkp256_setIndexArray(void * _self,word);
void FlashBkp256_clearIndexArray(void * _self);  
  
const struct FlashBkpClass FlashBkp256={
  &Class,
  "",
  &Object,
  sizeof(struct FlashBkp256),
  NULL,
  NULL,
  NULL, // differ
  NULL, // puto
  FlashBkp_getWord,
  FlashBkp_setWord,
  FlashBkp_getWord,
  FlashBkp_setWord,
  NULL,
  NULL,
  FlashBkp_borrarProm,
  FlashBkp_grabarProm,
  FlashBkp256_getIndexArray,
  FlashBkp256_setIndexArray,
  FlashBkp256_clearIndexArray 
};

#define indiceFlash  ((word*)((byte*)FlashBkp_getDireccionBkp(self)+PAGE_SIZE/2))


bool FlashBkp256_getIndexArray(void * _self,word index){
  struct FlashBkp256 * self = _self; 
  
  return (indiceFlash[index])?1:0;
}

void FlashBkp256_setIndexArray(void * _self,word index){
  struct FlashBkp256 * self = _self; 
  WriteWord(&indiceFlash[index],0);	
}

void FlashBkp256_clearIndexArray(void * _self){
  struct FlashBkp256 * self = _self; 
}

#warning agregar:
/*
void FlashBkp256_setWord(void * _self,word address){
  struct FlashBkp256 * self = _self; 
  assert(address<PAGE_SIZE/2);
  if(address>PAGE_SIZE/2)
    return; //cambiear : error	
  return super_setWord(_self,address);
}

word FlashBkp256_getWord(void * _self,word * address){
  struct FlashBkp256 * self = _self; 
  assert(address<PAGE_SIZE/2);
  if(address>PAGE_SIZE/2)
    return; //cambiear : error	
  return super_getWord(_self,address);

}
*/
