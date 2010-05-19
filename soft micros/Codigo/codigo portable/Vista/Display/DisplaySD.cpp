#include <stdio.h>
#include <stdlib.h>
#include "DisplaySD.hpp"
#include "matriz.h"
#include "OOC/lang/Math.hpp"

DisplaySD::DisplaySD(byte* _puerto,char _nroDys):puerto(_puerto),corrimiento(0),nLetras(0),nroDys(_nroDys){}


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

   //Transformacion para el SD		( el puerto A tiene los segmentos cambiados respecto del B)
     if(nroDys==1 || nroDys==2){
      
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
     }
   
    mensaje[nLetras]=digitoTmp;
    nLetras++;  
    str++;
  }
}

void DisplaySD::write(int i){
  char str[5];
  sprintf(str,"%*i",DIGITOS,abs(i));
  
  write(str);
  if(i<0)
    mensaje[0]|= Car_Ini[0];
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
    mensaje[0]|= Car_Ini[0];

  
}
    
/*
void DisplaySD::writeByte(unsigned char b){
	char str[2]=" ";
	str[0]=b;
	write(str);
} */

void DisplaySD::borrar(){
  nLetras = 0;  
}

void DisplaySD::apagar(){
  *puerto = 0;
}

bool DisplaySD::isScrolling(){
  return nLetras>DIGITOS;
}


void DisplaySD::resetearCorrimiento(){
  corrimiento=0;
}

void DisplaySD::incrementarCorrimiento(){
  corrimiento++;
 // if ( corrimiento==nLetras + DIGITOS )
 //   corrimiento=0;
}

void DisplaySD::imprimirDigito(byte numDigito){
  byte caracterAMostrar = (numDigito+corrimiento)%(nLetras+DIGITOS-1);
  if(caracterAMostrar<nLetras)
    *puerto = mensaje[caracterAMostrar];
  else
    *puerto = 0;
}
