/*MODULE: BoxAccess.c*/



#include <stdarg.h>
#include <stddef.h>

#include "display.h"
#include "BoxAccess.h"

  
#pragma DATA_SEG BOX_ACCESS_DATA                                            
#pragma CODE_SEG BOX_ACCESS_CODE
#pragma CONST_SEG DEFAULT

BOX_State BoxAccess_ProcKey(void* _self,uchar tecla);
void BoxAccess_DefConstructor(void * _self,va_list*args);

const struct BoxClass BoxAccess={
      BOXCLASS_INITIALIZATION(BoxClass,
                          BoxAccess,
                          Box,
                          BoxAccess_DefConstructor,
                          NULL,
                          NULL,
                          NULL,
                          NULL,
                          BoxAccess_ProcKey,
                          NULL)
}; 



/*
** ===================================================================
**     Method      :  DataBox_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxAccess_Constructor(void * _self, char*str1,int Code){
  struct BoxAccess * _box = (struct BoxAccess *)_self;
  _box->ValorTmp=0;
  _box->Code=Code;
  PasarASCII(str1,_DPY_INF); 
  Pasar_Numero(0,_DPY_SUP,0);   
}
/*
** ===================================================================
**     Method      :  DataBox_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxAccess_DefConstructor(void * _self,va_list*args){
  BoxAccess_Constructor(_self,va_arg(*args,char*),va_arg(*args,int));  
}


/*
** ===================================================================
**     Method      :  DataBox_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State BoxAccess_ProcKey(void* _self,uchar tecla){
  struct BoxAccess * _box=(struct BoxAccess *)_self;
  
  if(tecla=='u' || tecla=='d'){
    if(tecla=='d')
      _box->ValorTmp--;
    else
      _box->ValorTmp++;
    Pasar_Numero(_box->ValorTmp,_DPY_SUP,0);
  }else if (tecla=='r')
	  return EXIT_BOX;
  else if(tecla=='f'){
    if(_box->ValorTmp== _box->Code)
      return EXIT_BOX;
    else{
      _box->ValorTmp=0;
      Pasar_Numero(0,_DPY_SUP,0);  
    } 
  }
  
  
  return STAY_BOX;  

}

#pragma CODE_SEG BOX_ACCESS_CODE 


