#include <stdio.h>
#include <stdlib.h>
#include "CharPointer.hpp"
#include "Math.hpp"


void CharPointer::printFloat(char * str,int integer,byte decimalPosition){
   if(decimalPosition){
    int a;
    a=sprintf(str,"%d.",integer/ Math::pow10(decimalPosition));
    str+=a;
    sprintf(str,"%0*d",decimalPosition,abs(integer)% Math::pow10(decimalPosition));
   }else
    sprintf(str,"%d",integer); 
}

void CharPointer::printFloatLeft(char * str,int size,int integer,byte decimalPosition){
   if(decimalPosition){
    int a;
    a=sprintf(str,"%i.",integer/ Math::pow10(decimalPosition));
    str+=a;
    sprintf(str,"%0*i",decimalPosition,abs(integer)% Math::pow10(decimalPosition));
   }else
    sprintf(str,"%4i",integer); 
}
