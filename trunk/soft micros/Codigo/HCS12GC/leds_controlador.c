#include "leds.h"

 
 byte salidaLedNum(byte numSalida){
  static const byte led[]={			 //leds de alarma en orden
      5,
      2,
      6,
      4,      
      3,
      0,
      1,
      7 
  };
  if(numSalida<8)
    return  led[numSalida];
  return 2; //led de control
}
