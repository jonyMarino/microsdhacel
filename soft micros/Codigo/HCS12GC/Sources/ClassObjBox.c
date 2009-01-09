/*MODULE: ClassObjBox.c*/
#include <stdarg.h>
#include "ClassObjBox.h"
#include "Math.h"
#include "str_lib.h"

#include "display.h"
#include "Cpu.h"

const struct BoxClass ObjBox;

/*
** ===================================================================
**     Method      :  ObjBox_Constructor 
**     Description :  Constructor del Box para Objetos
** ===================================================================
*/
void ObjBox_Constructor(void * _self,uchar NumObj){
  struct ObjBox * _box= _self;
  
  _box->NumObj=NumObj;   
}


/*
** ===================================================================
**     Method      :  ObjBox_PrintDescription 
**     Description :  Imprime la descripción pasada del Box con su número
**                    de objeto.
** ===================================================================
*/
void ObjBox_PrintDescription(void * _self,const char * str,uchar num_display){
  struct ObjBox * _box= _self;  
  char * str_to_print;
  uchar i;
  uchar decimales= (uchar)get_Decimales(num_display);    
  
  //Veo que cantidad de caracteres tiene el string
  for(i=0;str[i]!='\0';i++);
  Cpu_DisableInt(); 
  str_to_print=malloc(i+decimales+1); 
  Cpu_EnableInt(); 
  for(i=0;str[i]!='\0';i++)
    str_to_print[i]=str[i];    
  
  if(_box->NumObj)			// si el numero de objeto no es 0, lo agrego
    IntToStr(_box->NumObj,&str_to_print[i],decimales);
  else
    str_to_print[i]='\0';
  
  PasarASCII(str_to_print,num_display);
  
  free(str_to_print);
}

