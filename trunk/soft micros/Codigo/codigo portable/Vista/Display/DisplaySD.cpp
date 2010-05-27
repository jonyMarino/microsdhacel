#include <stdio.h>
#include <stdlib.h>
#include "DisplaySD.hpp"
#include "matriz.h"
#include "OOC/lang/Math.hpp"

DisplaySD::DisplaySD(byte* _puerto):Display(_puerto){
 
}


void DisplaySD::write(const char* str){
  static byte i=0;
  
  Display::write(str);
  //Transformacion para el SD		( el puerto A tiene los segmentos cambiados respecto del B)
   while((Display::mensaje[i])!='\0'){
    
      uchar c=Display::mensaje[i];
      uchar bit1=(c&2)>>1;
      uchar bit2=(c&1)<<1;
      uchar bit3=(c&8)>>1;
      uchar bit4=(c&4)<<1;
      c&=0xfe;
      c|=bit1;
      c&=0xfd;
      c|=bit2;
      c&=0xfb;
      c|=bit3;
      c&=0xf7;
      c|=bit4;
      Display::mensaje[i]=c;
      
      i++;
   }
   i=0;
}

void DisplaySD::write(int i){
  char str[5];
  sprintf(str,"%*i",DIGITOS,abs(i));
  write(str);
  if(i<0)
    mensaje[0]|= Car_Ini[0];
}

