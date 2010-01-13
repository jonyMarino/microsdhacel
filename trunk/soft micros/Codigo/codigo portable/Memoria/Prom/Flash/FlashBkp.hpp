#ifndef _FLASH_BKP_HPP
#define _FLASH_BKP_HPP

#include "PromBkp.hpp"
#include "FshTypeSizes.h"

class FlashBkp:public PromBkp{
  public:
    FlashBkp(void * direccionBkp);
    byte setByte(word*,fbyte);
    fbyte getByte(word*);
    byte setWord(word*,word);
    word getWord(word*);
    void *grabarProm();  
    byte borrarProm(void*direccion);
  protected:
    virtual bool getIndexArray(word);
    virtual void setIndexArray(word);
    virtual void clearIndexArray();
    const void * getDireccionBkp(); 
  private:
    const void * direccionBkp;
    bool escrituraHabilitada;
    void * paginaAGrabar;		//actual pagina a grabar
    bool isParaGrabar(word dir);
    void backupSector();
};



#endif