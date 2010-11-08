#ifndef _ISPI_HPP
#define _ISPI_HPP

#include "PE/include/PE_Types.h"

class ISPI{
  public:
    //ISPI();
    virtual void sendByte(VUINT8 u8Data)=0;
    virtual VUINT8 receiveByte(void)=0;
    virtual void highRate(void)=0; //pone el SPI en 375KHz
    virtual void setSlaveSelect(byte)=0; //selecciona el esclavo con el cual se comunica
};

#endif