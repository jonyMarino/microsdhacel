#include "BoxList.hpp"
#include <stddef.h>
#include "BoxTitle.hpp"
#include "FstBoxPointer.hpp"

/*
** =====================================================================
**    Method      :  getNextBox 
**    Description :  Obtiene el Box correspondiente de la lista
** =====================================================================
*/
Box * BoxList::getNextBox(uchar boxCount)const{
  struct FstBoxPointer *  fb;
  if(boxCount==0)  //ingrese a la lista 
    return (Box*)new BoxTitulo(nombre," -- "); 
  if(boxCount>Array_count(this))
    return NULL;
  
  fb= (struct FstBoxPointer *)Array_get(this,boxCount-1);
  
  return &fb->getNextBox();
}
/*
** =====================================================================
**    Method      :  BoxList_AddBox 
**    Description :  Agrega un box a la lista
** =====================================================================
*/
//void BoxList_AddBox(void*self,void *Cbox,void *Obj,uchar num_obj){
  /*struct BoxList * _list = (struct BoxList *)self;
  struct FstBoxPointer * fb;
  
      fb= _new(&FstBoxPointer,Cbox,Obj,num_obj);
      if(!fb)
        return; //error
      Array_Add(_list,fb);  */
//}
/*
** =====================================================================
**    Method      :  BoxList_addIndexedBox 
**    Description :  Agrega un box a la lista en un lugar determinado
** =====================================================================
*/
//void BoxList_addIndexedBox(void*self,void *Cbox,void *Obj,uchar num_obj,int index){
/*  struct BoxList * _list = (struct BoxList *)self;
  struct FstBoxPointer * fb;
  
      fb= new(&FstBoxPointer,Cbox,Obj,num_obj);
      if(!fb)
        return; //error

      if(Array_count(_list)<index)				//indice fuera de rango?
        Array_Add(_list,fb);
      else
        Array_Put(_list,fb,index);   */
//}

