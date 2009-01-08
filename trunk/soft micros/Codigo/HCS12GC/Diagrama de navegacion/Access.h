#ifndef _ACCESS_H_
#define _ACCESS_H_

#include "ArrayList.h"
#include "BoxList.h"

struct Access{											 // sabe get_new_box
  struct ArrayList/*<BoxList>*/ _base;				 
  int * Codigo;
  const char * name;
};

extern const struct Class Access;

void Access_Constructor(void*self,const char *str,int * Cod);
void Access_AddBox(void*self,const char *str,void *Cbox,void *Obj,uchar num_obj);
void Access_addIndexedBox(void*self,const char *str,void *Cbox,void *Obj,uchar num_obj,int index);
struct Box *Access_getNextBox(void*self,uchar list_count,uchar box_count);


#define NEW_ACCESS(name,arrayBoxList,strName,pCodigo)  \
  struct Access name={                                  \
    INITIALIZATION_ARRAY_LIST(Access,arrayBoxList),  \
    pCodigo,																							\
    strName  																							\
}

#endif