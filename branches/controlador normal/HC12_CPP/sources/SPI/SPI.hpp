#ifndef _SPI_HPP
#define _SPI_HPP

#include "Hardware/SPI/ISPI.hpp"

class SPI: public ISPI{
  public:
    SPI(){}
    virtual void sendByte(VUINT8 u8Data){
    }
    virtual VUINT8 receiveByte(void){
      return 0;
    }
    virtual void highRate(void){
    }//pone el SPI en 375KHz
    virtual void setSlaveSelect(byte a){
    }//selecciona el esclavo con el cual se comunica
};

#endif
