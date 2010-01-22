#ifndef _FLASH_BKP_HPP
#define _FLASH_BKP_HPP

#include "Memoria/Prom/PromBkp.hpp"
#include "Memoria/FshTypeSizes.h"

class FlashBkp:public PromBkp{
  public:
    FlashBkp(void * direccionBkp);
    byte setByte(word*,fbyte);
    fbyte getByte(fbyte*);
    byte setWord(word*,word);
    word getWord(word*);
    void *grabarProm();  
    byte borrarProm(void*direccion);
  protected:
    virtual bool getIndexArray(word)=0;
    virtual void setIndexArray(word)=0;
    virtual void clearIndexArray()=0;
    const void * getDireccionBkp(); 
  private:
    const void * direccionBkp;
    bool escrituraHabilitada;
    void * paginaAGrabar;		//actual pagina a grabar
    bool isParaGrabar(word dir);
    void backupSector();
};



#endif