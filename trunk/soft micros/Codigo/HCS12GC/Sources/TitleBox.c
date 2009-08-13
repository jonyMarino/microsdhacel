/*  MODULE: TitleBox.c*/



#include <stdarg.h>
#include <stddef.h>

#include "display.h"
#include "TitleBox.h"

#pragma CONST_SEG DEFAULT

#pragma CODE_SEG TIT_BOX

BOX_State TitleBox_ProcKey(void* _self,uchar tecla);
void TitleBox_DefConstructor(void * _self,va_list*args);
void TitleBox_Constructor(void * _self, char*str1,char*str2);

const struct BoxClass TitleBox={
               BOXCLASS_INITIALIZATION(BoxClass,
                          TitleBox,
                          Box,
                          TitleBox_DefConstructor,
                          NULL,
                          NULL,
                          NULL,
                          NULL,
                          TitleBox_ProcKey,
                          NULL) 
};



/*
** ===================================================================
**     Method      :  DataBox_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void TitleBox_Constructor(void * _self, char*str1,char*str2){

  PasarASCII(str1,_DPY_INF); 
  PasarASCII(str2,_DPY_SUP);
    
}
/*
** ===================================================================
**     Method      :  DataBox_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void TitleBox_DefConstructor(void * _self,va_list*args){
  TitleBox_Constructor(_self,va_arg(*args,char*),va_arg(*args,char*));  
}


/*
** ===================================================================
**     Method      :  DataBox_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State TitleBox_ProcKey(void* _self,uchar tecla){

  
  if (tecla=='r' || tecla=='f')
	  return EXIT_BOX;
  
  return STAY_BOX;  

}




