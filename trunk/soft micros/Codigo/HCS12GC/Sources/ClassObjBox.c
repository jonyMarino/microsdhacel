/*MODULE: ClassObjBox.c*/
#include <stdarg.h>
#include "ClassObjBox.h"
#include "Math.h"
#include "str_lib.h"

#include "display.h"
#include "Cpu.h"

const struct BoxClass ObjBox={
  CLASS_INITIALIZATION(Class,ObjBox,Object,Object_ctor,Object_dtor,Object_differ,Object_puto)  
};

/*
** ===================================================================
**     Method      :  ObjBox_Constructor 
**     Description :  Constructor del Box para Objetos
** ===================================================================
*/
void ObjBox_Constructor(void * _self,uchar NumObj){
  struct ObjBox * _box= (struct ObjBox *)_self;
  
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
  struct ObjBox * _box= (struct ObjBox *)_self;  
  char * str_to_print;
  uchar i;
  uchar decimales= (uchar)get_Decimales(num_display);    
  
  //Veo que cantidad de caracteres tiene el string
  for(i=0;str[i]!='\0';i++);
  #ifndef DEBUG
  Cpu_DisableInt(); 
  #endif
  str_to_print=(char *)malloc(i+decimales+1); 
  #ifndef DEBUG
  Cpu_EnableInt();
  #endif 
  for(i=0;str[i]!='\0';i++)
    str_to_print[i]=str[i];    
  
  if(_box->NumObj)			// si el numero de objeto no es 0, lo agrego
    IntToStr(_box->NumObj,&str_to_print[i],decimales);
  else
    str_to_print[i]='\0';
  
  PasarASCII(str_to_print,num_display);
  

  free(str_to_print);

}

