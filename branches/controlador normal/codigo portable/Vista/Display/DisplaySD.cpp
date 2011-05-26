#include <stdio.h>
#include <stdlib.h>
#include "DisplaySD.hpp"
#include "matriz.h"
#include "OOC/lang/Math.hpp"

DisplaySD::DisplaySD(byte* _puerto):Display(_puerto){
 
}


void DisplaySD::write(const char* str){
  byte temp, digitoTmp;
  
	if(nLetras>4)		 // En el anterior hubo scrolling?
    resetearCorrimiento();
	nLetras=0;
	
  while(*str!='\0')
  {
    temp=*str;
    temp-='-';
    
    if(*str=='.' && nLetras){			 // Agrego el punto en el digito anterior 	
      str++;
      mensaje[nLetras-1]|=0x80;
      continue;
    }

    if((*str)!=' ')
      digitoTmp=(byte)Car_Ini[temp];
    else
      digitoTmp=0x00;
    
    uchar c=digitoTmp;
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
    digitoTmp=c;
    
    
    mensaje[nLetras]=digitoTmp;
    nLetras++;  
    str++;
  }
} 
/*
  
  static char i=0;
  char* msj=NULL; 
 
  Display::write(str);
  msj = Display::getMensaje();
  
  //Transformacion para el SD		( el puerto A tiene los segmentos cambiados respecto del B)
   while((*(str+i))!='\0'){
    
      uchar c=(*(msj+i));
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
      (*(msj+i))=c;
      
      i++;
   }
  i=0;
  Display::setMensaje(msj);
   
}   */   

void DisplaySD::write(int i){
  char str[5];
  sprintf(str,"%*i",DIGITOS,abs(i));
  write(str);
  if(i<0){
    (*mensaje)|= 1; //valor para poner el signo "-" en display sd
  }
}

void DisplaySD::writeAsFloat(int i,uchar decimales){
  if(!decimales){ 
    write(i);
    return;
  }
  char str[6];
  int a;
  a=sprintf(str,"%*i.",DIGITOS-decimales,abs(i)/ Math::pow10(decimales));
  //str+=a;
  sprintf(str+a,"%0*i",decimales,abs(i)% Math::pow10(decimales));

  write(str);
  if(i<0)
    {
    (*mensaje)|= 1; //valor para poner el signo "-" en display sd
  }

  
}

