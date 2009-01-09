#include "BoxList.h"
#include "stddef.h"
#include "TitleBox.h"
#include "FstBoxPointer.h"

const struct Class BoxList={
      CLASS_INITIALIZATION(Class,
                       BoxList,
                       Object,
                       BoxList_DefConstructor,
                       NULL,
                       NULL,
                       NULL)   
};


/*
** =====================================================================
**    Method      :  List_getNextBox 
**    Description :  Obtiene el Box correspondiente de la lista
** =====================================================================
*/
void BoxList_Constructor(void * self,const char *str){
  struct BoxList * _list = self;
  
  ArrayList_Constructor(self);
  _list->name=str;
}
/*
** =====================================================================
**    Method      :  List_getNextBox 
**    Description :  Obtiene el Box correspondiente de la lista
** =====================================================================
*/
void BoxList_DefConstructor(void*self,va_list * args){
  BoxList_Constructor(self,va_arg(*args,const char *)); 
}
/*
** =====================================================================
**    Method      :  List_getNextBox 
**    Description :  Obtiene el Box correspondiente de la lista
** =====================================================================
*/
struct Box *List_getNextBox(void*self,uchar box_count){
  struct BoxList * _list = self;
  struct FstBoxPointer * fb;
  if(box_count==0)  //estoy en la lista 
    return new(&TitleBox,_list->name," -- "); 
  if(box_count>ArrayList_count(_list))
    return NULL;
  
  fb=ArrayList_get(_list,box_count-1);
  
  return FBP_getNextBox(fb);
}
/*
** =====================================================================
**    Method      :  BoxList_AddBox 
**    Description :  Agrega un box a la lista
** =====================================================================
*/
void BoxList_AddBox(void*self,void *Cbox,void *Obj,uchar num_obj){
  struct BoxList * _list = self;
  struct FstBoxPointer * fb;
  
      fb= new(&FstBoxPointer,Cbox,Obj,num_obj);
      if(!fb)
        return; //error
      ArrayList_Add(_list,fb);
}
/*
** =====================================================================
**    Method      :  BoxList_addIndexedBox 
**    Description :  Agrega un box a la lista en un lugar determinado
** =====================================================================
*/
void BoxList_addIndexedBox(void*self,void *Cbox,void *Obj,uchar num_obj,int index){
  struct BoxList * _list = self;
  struct FstBoxPointer * fb;
  
      fb= new(&FstBoxPointer,Cbox,Obj,num_obj);
      if(!fb)
        return; //error

      if(ArrayList_count(_list)<index)				//indice fuera de rango?
        ArrayList_Add(_list,fb);
      else
        ArrayList_Put(_list,fb,index);
}

