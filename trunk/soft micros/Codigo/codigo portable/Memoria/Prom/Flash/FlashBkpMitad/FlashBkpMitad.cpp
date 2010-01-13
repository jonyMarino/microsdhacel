#include <assert.h>

#include "FlashBkpMitad.hpp"
#include "IFshMem.h"
#include "stddef.h"
#include "IFsh10.h"


#define indiceFlash  ((byte*)((byte*)getDireccionBkp()+PAGE_SIZE/2))


bool FlashBkpMitad::getIndexArray(word index){ 
  return !indiceFlash[index];
}

void FlashBkpMitad::setIndexArray(word index){
  WriteWord((word*)&indiceFlash[index],0);	
}

void FlashBkpMitad::clearIndexArray(){
}


byte FlashBkpMitad::setWord(word * address,word data){
  assert( ((word)address &PAGE_SIZE) <=PAGE_SIZE/2);
  if(((word)address &PAGE_SIZE)>PAGE_SIZE/2)
    return ERR_ADDR; //cambiar : error	
  return FlashBkp::setWord(address,data);
}

word FlashBkpMitad::getWord(word * address){
  assert(((word)address &PAGE_SIZE)<=PAGE_SIZE/2);
  if(((word)address &PAGE_SIZE)>PAGE_SIZE/2)
    return ERR_ADDR; //cambiar : error	
  return FlashBkp::getWord(address);

}               
