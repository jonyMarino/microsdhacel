#include <string.h>

#include "Access.h"
#include "stddef.h"
#include "BoxAccess.h"

void Access_DefConstructor(void*self,va_list * args);
bool BoxListComparatorByName_Equals(void * _self,void * _boxList);


const struct Class Access={
    CLASS_INITIALIZATION(Class,
                       Access,
                       Object,
                       Access_DefConstructor,
                       NULL,
                       NULL,
                       NULL)    
};


class BoxListComparatorByName:public Comparator{
  public:
    bool equals(void * obj);
    int compare(void*);
    const char * str;  
};

/*
** =====================================================================
**    Method      :  Access_Constructor 
**    Description :  Agrega un box a la lista del acceso
** =====================================================================
*/
void Access_Constructor(void*self,const char *str,int * Cod){
/*  struct Access * acceso = (struct Access *) self;
  newAlloced(self,&Array,1);
  acceso->name=str;
  acceso->Codigo=Cod;   */
}

/*
** =====================================================================
**    Method      :  Access_DefConstructor 
**    Description :  Constructor por defecto de la lista de acceso
** =====================================================================
*/
void Access_DefConstructor(void*self,va_list * args){
  Access_Constructor(self,va_arg(*args,char*),va_arg(*args,int*));
}
/*
** =====================================================================
**    Method      :  Access_AddBox 
**    Description :  Agrega un box a la lista del acceso
** =====================================================================
*/
void Access_addIndexedBox(void*self,const char *str,void *Cbox,void *Obj,uchar num_obj,int index){
 /* struct Access * acceso=(struct Access *) self;  
  byte i;
  void * boxList_tmp; 
  BoxListComparatorByName myBoxListComparatorByName;
  

  myBoxListComparatorByName.str=str;
  
  boxList_tmp= Array_search((struct Array*)self,&myBoxListComparatorByName);
  
  if(boxList_tmp!=NULL){
      BoxList_addIndexedBox(boxList_tmp,Cbox,Obj,num_obj,index);
      return;
  }
    
  boxList_tmp=_new(&BoxList,str);
  if(!boxList_tmp)
    return; //error
  BoxList_addIndexedBox(boxList_tmp,Cbox,Obj,num_obj,index);
  Array_add(self,boxList_tmp);
  
  deleteAlloced(&myBoxListComparatorByName);
  */
}

void Access_AddBox(void*self,const char *str,void *Cbox,void *Obj,uchar num_obj){
 // Access_addIndexedBox(self,str,Cbox,Obj,num_obj,LIST_LAST_POSITION);  
}

/*
** =====================================================================
**    Method      :  Access_getNextBox 
**    Description :  Obtiene el Box correspondiente del acceso
** =====================================================================
*/
struct Box *Access_getNextBox(void*self,uchar list_count,uchar box_count){
  struct Access * acceso=(struct Access *) self;
  /*struct BoxList*/void * tmp_list;
  
  if(list_count==0)		 //mostrar acceso
    return (struct Box *) _new(&BoxAccess,acceso->name,*acceso->Codigo);  				 // MODIFICAR!,debe ser variable

  if(list_count>Array_count(acceso)) // se paso de la cantidad de listas
    return NULL;
  
  tmp_list= Array_get(acceso,list_count-1);
  return List_getNextBox(tmp_list,box_count);
      
}

/*
** =====================================================================
**    Method      :  BoxListComparatorByName_Equals 
**    Description :  pregunta si son iguales
** =====================================================================
*/
bool BoxListComparatorByName::equals(void * obj){
  struct BoxList * boxList = (struct BoxList *)obj; 
 
  return !strcmp(boxList->name, str);     
}

int BoxListComparatorByName::compare(void*){
  return 1;
}
