#include "Display.hpp"
#include "matriz.h"


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

void Display::write(unsigned char b){
	char str[2]=" ";
	str[0]=b;
	write(str);	
}

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
  if ( corrimiento==nLetras + DIGITOS )
    corrimiento=0;
}

void Display::imprimirDigito(byte numDigito){
  byte caracterAMostrar = numDigito+corrimiento;
  if(caracterAMostrar<nLetras)
    *puerto = mensaje[numDigito+corrimiento];
  else
    *puerto = 0;
}
