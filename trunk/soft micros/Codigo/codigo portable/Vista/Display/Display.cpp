#include <stdio.h>
#include <stdlib.h>
#include "Display.hpp"
#include "matriz.h"
#include "OOC/lang/Math.hpp"

Display::Display(byte* _puerto):puerto(_puerto),corrimiento(0),nLetras(0){}


void Display::write(const char* str){
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
   
    mensaje[nLetras]=digitoTmp;
    nLetras++;  
    str++;
  }
}

void Display::write(int i){
  char str[5];
  sprintf(str,"%*i",DIGITOS,abs(i));
  
  write(str);
  if(i<0)
    mensaje[0]|= Car_Ini[0];
}

void Display::writeAsFloat(int i,uchar decimales){
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
void Display::writeByte(unsigned char b){
	char str[2]=" ";
	str[0]=b;
	write(str);
} */

void Display::borrar(){
  nLetras = 0;  
}

void Display::apagar(){
  *puerto = 0;
}

bool Display::isScrolling(){
  return nLetras>DIGITOS;
}


void Display::resetearCorrimiento(){
  corrimiento=0;
}

void Display::incrementarCorrimiento(){
  corrimiento++;
 // if ( corrimiento==nLetras + DIGITOS )
 //   corrimiento=0;
}

void Display::imprimirDigito(byte numDigito){
  byte caracterAMostrar = (numDigito+corrimiento)%(nLetras+DIGITOS-1);
  if(caracterAMostrar<nLetras)
    *puerto = mensaje[caracterAMostrar];
  else
    *puerto = 0;
}
