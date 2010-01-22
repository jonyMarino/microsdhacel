#ifndef _RAM_SIMULA_FLASH_H
#define _RAM_SIMULA_FLASH_H

#include "PromBkp.h"
#include "IFshMem.h"
#include "FshTypeSizes.h"

struct RamSimulaFlash{
  struct PromBkp super;
};

extern const struct PromBkpClass RamSimulaFlash;
///////////////////////////////////////

#define INITIALIZATION_RAM_SIMULA_FLASH(class)       \
    INITIALIZATION_PROM_BKP(class)              							\

/*
#define NEW_RAM_SIMULA_FLASH(name) \
  struct RamSimulaFlash name={														\
    INITIALIZATION_RAM_SIMULA_FLASH(&RamSimulaFlash) \
  }
  */
#endif