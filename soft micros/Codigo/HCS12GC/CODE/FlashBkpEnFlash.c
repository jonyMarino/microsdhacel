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

bool FlashBkpEnFlash_getIndexArray(void * _self,word);
void FlashBkpEnFlash_setIndexArray(void * _self,word);
void FlashBkpEnFlash_clearIndexArray(void * _self);  
  
const struct FlashBkpClass FlashBkpEnFlash={
  &Class,
  "",
  &Object,
  sizeof(struct FlashBkpEnFlash),
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
  FlashBkpEnFlash_getIndexArray,
  FlashBkpEnFlash_setIndexArray,
  FlashBkpEnFlash_clearIndexArray 
};

const word mask[]={
  1<<0,
  1<<1,
  1<<2,
  1<<3,
  1<<4,
  1<<5,
  1<<6,
  1<<7,
  1<<8,
  1<<9,
  1<<10,
  1<<11,
  1<<12,
  1<<13,
  1<<14,
  1<<15,  
};


bool FlashBkpEnFlash_getIndexArray(void * _self,word index){
  struct FlashBkpEnFlash * self = _self; 
  byte shift=(index/2)% ( sizeof(word)*8 );
  return self->indiceFlash[index/INDICE_SIZE]&= mask[shift];
}

void FlashBkpEnFlash_setIndexArray(void * _self,word index){
  struct FlashBkpEnFlash * self = _self; 
  byte shift=(index/2)% ( sizeof(word)*8 );
  self->indiceFlash[index/INDICE_SIZE]|= mask[shift];	

}

void FlashBkpEnFlash_clearIndexArray(void * _self){
  struct FlashBkpEnFlash * self = _self; 
  int i;
  for(i=0; i < INDICE_SIZE ; i++){
    self->indiceFlash[i]=0;
  }
}
