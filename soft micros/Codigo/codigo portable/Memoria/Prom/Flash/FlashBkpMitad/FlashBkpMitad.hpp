#ifndef _FLASH_BKP_MITAD_HPP
#define _FLASH_BKP_MITAD_HPP

#include "Memoria/Prom/Flash/FlashBkp.hpp"


class FlashBkpMitad:public FlashBkp{
  public:
    FlashBkpMitad(void * direccionBkp);
    byte setWord(word * address,word data);

    word getWord(word * address);
  
  protected:
    bool getIndexArray(word index);

    void setIndexArray(word index);

    void clearIndexArray();
};
  
  
#endif