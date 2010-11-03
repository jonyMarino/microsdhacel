#ifndef _SPI_HPP
#define _SPI_HPP

#include "FslTypes.h"

class ISPI{
  public:
    ISPI();
    virtual void sendByte(UINT8 u8Data)=0;
    virtual UINT8 receiveByte(void)=0;
    virtual void highRate(void)=0; //pone el SPI en 375KHz
    virtual void setSlaveSelect(byte)=0; //selecciona el esclavo con el cual se comunica
};

#endif