/*  MODULE str_lib.c  */
/*  Implementacion de funciones para strings no contenidas en stdlib.h*/

#include <stdlib.h>
#include <stdio.h>
#include "Math.hpp"
#include "stddef.h"
#include "str_lib.h"


char * IntToStr(int integer, char * str, int max_size){
   int i;
   int tmp_integer=integer;
   char * ret;
   
   for(i=0;i<max_size;i++){
    tmp_integer/=10;
    if(!tmp_integer)
      break;  
   }
   
   if(i>=max_size)
    return NULL;
   
   ret=str+i+1;
   *ret = '\0';
   
   for(;i>=0;i--){
    *(str+i)=integer%10+'0';
    integer/=10;
   }
   
   return ret;
}

void FloatToStr(int integer, char * str, int max_size,int decimales){
   int i;
   int tmp_integer=integer;
   char * ret=str;
   
   if(decimales){
    int a;
    #warning intentar sacar este if
    if(integer<0){
      *str='-';
      integer = -integer;
      ++str;
    }
    a=sprintf(str,"%d.",integer/ Math::pow10(decimales));
    str+=a;
    sprintf(str,"%0*d",decimales,integer% Math::pow10(decimales));
   }else
    sprintf(str,"%d",integer); 
}