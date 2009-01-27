#ifndef _FLASH_BKP_EN_FLASH_H
#define _FLASH_BKP_EN_FLASH_H

#include "FlashBkp.h"
#include "IFshMem.h"
#include "FshTypeSizes.h"

#define INDICE_SIZE (PAGE_SIZE/ ( sizeof(word)*8 ) )

struct FlashBkpEnFlash{
  struct FlashBkp super;
  word indiceFlash[INDICE_SIZE];
};

extern const struct FlashBkpClass FlashBkpEnFlash; 
///////////////////////////////////////

#define INITIALIZATION_FLASH_BKP_EN_FLASH(class,bkpAddr)       \
    INITIALIZATION_FLASH_BKP(class),              							\
    0,0,0,0,0,0,0,0,  							                \
    0,0,0,0,0,0,0,0,  						                	\
    0,0,0,0,0,0,0,0,  							                \
    0,0,0,0,0,0,0,0,  						                	

#define NEW_FLASH_BKP_EN_FLASH(name,bkpAddr) \
  struct FlashBkpEnFlash name={																				\
    INITIALIZATION_FLASH_BKP_EN_FLASH(&FlashBkpEnFlash,bkpAddr)  \
  }
  
  
#endif