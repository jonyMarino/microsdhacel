#include "FstBoxPointer.h"
#include "ClassBox.h"

void FstBoxPointer_DefConstructor(void*self,va_list * args);


const struct Class FstBoxPointer={
  CLASS_INITIALIZATION(Class,
                       FstBoxPointer,
                       Object,
                       FstBoxPointer_DefConstructor,
                       NULL,
                       NULL,
                       NULL)   
}; 


/*
** =====================================================================
**    Method      :  FBP_Constructor 
**    Description :  Constructor del fst box pointer
** =====================================================================
*/
void FBP_Constructor(void * self,void * CBox,void * Obj,uint num_obj){
  struct FstBoxPointer * _fbp = self;  
  
  _fbp->Cbox=CBox;
  _fbp->Obj=Obj;
  _fbp->num_obj= num_obj;
}
/*
** =====================================================================
**    Method      :  FBP_Constructor 
**    Description :  Constructor por defecto del fst box pointer
** =====================================================================
*/
void FstBoxPointer_DefConstructor(void*self,va_list * args){
  FBP_Constructor(self,va_arg(*args,void*),va_arg(*args,void*),va_arg(*args,uint));  
}
/*
** =====================================================================
**    Method      :  FBP_getNextBox 
**    Description :  Obtiene el Box inicial del fst box pointer
** =====================================================================
*/
struct Box *FBP_getNextBox(void * self){
  struct FstBoxPointer * _fbp = self;
  
  return vBoxes_Construct(_fbp->Cbox,_fbp->Obj,_fbp->num_obj);  
}
