#ifndef _FLASH_BKP_EN_FLASH_H
#define _FLASH_BKP_EN_FLASH_H

#include "PromBkp.h"
#include "IFshMem.h"
#include "FshTypeSizes.h"

struct FlashBkpEnFlash{
  struct PromBkp super;
  const void * direccionBkp;
  word indiceFlash[PAGE_SIZE/32];
  bool escrituraHabilitada;
  void * paginaAGrabar;		//actual pagina a grabar
};

extern const void * const FlashBkpEnFlash;
//usado internamente, no referenciar!!!
extern const struct TPromBkp flashBkpEnFlashTable; 
///////////////////////////////////////

#define INITIALIZATION_FLASH_BKP_EN_FLASH(class,bkpAddr)       \
    INITIALIZATION_PROM_BKP(class),              							\
    (const void*)bkpAddr,														\
    0,0,0,0,0,0,0,0,  							                \
    0,0,0,0,0,0,0,0,  						                	\
    TRUE,																						\
    NULL

#define NEW_FLASH_BKP_EN_FLASH(name,bkpAddr) \
  struct FlashBkpEnFlash name={																				\
    INITIALIZATION_FLASH_BKP_EN_FLASH(&flashBkpEnFlashTable,bkpAddr)  \
  }
#endif