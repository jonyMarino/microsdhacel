#ifndef _SD_FAT_HPP
#define _SD_FAT_HPP

//clase interina, la idea es que pueda tener varias instancias
#include "./SD/Fat/Fat.h"

class SDFat{
  public:
    SDFat(ISPI& spi,BitIn& sdPresent);
    VUINT8 fileOpen(const VUINT8*,VUINT8);
    void fileWrite(const VUINT8*,VUINT32);
    VUINT16 fileRead(VUINT8*);
    void fileClose();
};

#endif
