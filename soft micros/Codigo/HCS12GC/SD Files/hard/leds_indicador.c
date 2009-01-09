 #include "leds.h"

 
 byte salidaLedNum(byte numSalida){
  static const byte led[]={			 //leds de alarma en orden
      3,
      0,
      1,
      7 
  };
  if(numSalida<4)
    return  led[numSalida];
  return 2; //led de control
}
