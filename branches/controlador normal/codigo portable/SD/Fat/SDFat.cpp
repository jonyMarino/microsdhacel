#include "SDFat.hpp"

SDFat::SDFat(ISPI& spi,BitIn& sdPresent){
  byte errr= SD_Init(spi,sdPresent);
  FAT_Read_Master_Block();
}

VUINT8 SDFat::fileOpen(const VUINT8 *pu8FileName,VUINT8 u8Function){
  return FAT_FileOpen(pu8FileName,u8Function);
}

void SDFat::fileWrite(const VUINT8 *pu8DataPointer,VUINT32 u32Size){
  FAT_FileWrite(pu8DataPointer,u32Size);
}

VUINT16 SDFat::fileRead(VUINT8 *pu8UserBuffer){
  return FAT_FileRead(pu8UserBuffer);
}


void SDFat::fileClose(){
  FAT_FileClose();  
}


