#ifndef _BOX_LIST_H_
#define _BOX_LIST_H_ 

#include "ArrayList.h"

struct BoxList{										 // sabe get_new_box
  struct ArrayList/*<FstBoxPointer>*/ _base; //Array Para abajo
  const char * name; 
};

extern const struct Class BoxList;

void BoxList_Constructor(void * self,const char *str);
void BoxList_DefConstructor(void*self,va_list * args);
struct Box *List_getNextBox(void*self,uchar box_count);
bool BoxListComparatorByName_Equals(void * _self,void * _boxList);
void BoxList_AddBox(void*self,void *Cbox,void *Obj,uchar num_obj);
void BoxList_addIndexedBox(void*self,void *Cbox,void *Obj,uchar num_obj,int index);


#define NEW_BOX_LIST(NAME,arrayFstBoxes,STR_NAME)  \
  struct BoxList NAME ={									\
    INITIALIZATION_ARRAY_LIST(BoxList,arrayFstBoxes),  \
    STR_NAME																								\
  }
#endif