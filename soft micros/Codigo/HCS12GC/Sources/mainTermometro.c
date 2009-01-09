#include "Termometro.h"
#include "FlashBkpEnFlash.h"

#pragma CONST_SEG PARAMETERS_PAGE
volatile const ConfiguracionTermometro termometro_config={
  TERMOMETRO_CONF_DEFAULT
};
#pragma CONST_SEG DEFAULT

struct Termometro termometro;
NEW_FLASH_BKP_EN_FLASH(flash,0x4200);

void main(void){
  newAllocObj(&termometro,Termometro,&termometro_config,&flash);
  
  for(;;){
    Termometro_mainLoop(&termometro);
  }
  
}