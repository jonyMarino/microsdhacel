#ifndef _SD_HARDWARE_HPP
#define _SD_HARDWARE_HPP

#include "SPI.hpp"

extern SPI spi; 
//Archivo temporal para mantener compatibilidad de codigo

/* HIL */
#define ReadSPIByte     spi.receiveByte
#define WriteSPIByte    spi.sendByte
#define HighSpeedSPI    spi.highRate
#define SPI_SS          spi.setSlaveSelect

/* SD card Inserted detection Pin */
#define SD_PRESENT      PORTB_BIT3


#endif