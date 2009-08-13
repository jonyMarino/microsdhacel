#include "BoxList.h"
#include "stddef.h"
#include "TitleBox.h"
#include "FstBoxPointer.h"

const struct Class BoxList={
      CLASS_INITIALIZATION(Class,
                       BoxList,
                       Array,
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
  struct BoxList * _list = (struct BoxList *)self;
  _list->name=str;
}
/*
** =====================================================================
**    Method      :  List_getNextBox 
**    Description :  Obtiene el Box correspondiente de la lista
** =====================================================================
*/
void BoxList_DefConstructor(void*self,va_list * args){
  super_ctor(&BoxList,self,args);
  BoxList_Constructor(self,va_arg(*args,const char *)); 
}
/*
** =====================================================================
**    Method      :  List_getNextBox 
**    Description :  Obtiene el Box correspondiente de la lista
** =====================================================================
*/
struct Box *List_getNextBox(void*self,uchar box_count){
  struct BoxList * _list = (struct BoxList *)self;
  /*struct FstBoxPointer */ void * fb;
  if(box_count==0)  //estoy en la lista 
    return (struct Box *)_new(&TitleBox,_list->name," -- "); 
  if(box_count>Array_count(_list))
    return NULL;
  
  fb=Array_get(_list,box_count-1);
  
  return FBP_getNextBox(fb);
}
/*
** =====================================================================
**    Method      :  BoxList_AddBox 
**    Description :  Agrega un box a la lista
** =====================================================================
*/
void BoxList_AddBox(void*self,void *Cbox,void *Obj,uchar num_obj){
  /*struct BoxList * _list = (struct BoxList *)self;
  struct FstBoxPointer * fb;
  
      fb= _new(&FstBoxPointer,Cbox,Obj,num_obj);
      if(!fb)
        return; //error
      Array_Add(_list,fb);  */
}
/*
** =====================================================================
**    Method      :  BoxList_addIndexedBox 
**    Description :  Agrega un box a la lista en un lugar determinado
** =====================================================================
*/
void BoxList_addIndexedBox(void*self,void *Cbox,void *Obj,uchar num_obj,int index){
/*  struct BoxList * _list = (struct BoxList *)self;
  struct FstBoxPointer * fb;
  
      fb= new(&FstBoxPointer,Cbox,Obj,num_obj);
      if(!fb)
        return; //error

      if(Array_count(_list)<index)				//indice fuera de rango?
        Array_Add(_list,fb);
      else
        Array_Put(_list,fb,index);   */
}

