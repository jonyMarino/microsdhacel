#include <string.h>

#include "Access.hpp"
#include <stddef.h>
#include "BoxAccess.hpp"

/*class BoxListComparatorByName:public Comparator{
  public:
    bool equals(void * obj);
    int compare(void*);
    const char * str;  
};
   */



/*
** =====================================================================
**    Method      :  Access_AddBox 
**    Description :  Agrega un box a la lista del acceso
** =====================================================================
*/
//void Access_addIndexedBox(void*self,const char *str,void *Cbox,void *Obj,uchar num_obj,int index){
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
//}

//void Access_AddBox(void*self,const char *str,void *Cbox,void *Obj,uchar num_obj){
 // Access_addIndexedBox(self,str,Cbox,Obj,num_obj,LIST_LAST_POSITION);  
//}

/*
** =====================================================================
**    Method      :  Access_getNextBox 
**    Description :  Obtiene el Box correspondiente del acceso
** =====================================================================
*/
Box *Access::getNextBox(uchar list_count,uchar box_count)const{

  struct BoxList * boxList;
  
  if(list_count==0)		 //mostrar acceso
    return  (Box*)new BoxAccess(name,*codigo);  				 // MODIFICAR!,debe ser variable

  if(list_count>Array_count((void*)this)) // se paso de la cantidad de listas
    return NULL;
  
  boxList= (struct BoxList *)Array_get((void*)this,list_count-1);
  return boxList->getNextBox(box_count);
      
}

/*
** =====================================================================
**    Method      :  BoxListComparatorByName_Equals 
**    Description :  pregunta si son iguales
** =====================================================================
*/
/*bool BoxListComparatorByName::equals(void * obj){
  struct BoxList * boxList = (struct BoxList *)obj; 
 
  return !strcmp(boxList->name, str);     
}

int BoxListComparatorByName::compare(void*){
  return 1;
}
     */