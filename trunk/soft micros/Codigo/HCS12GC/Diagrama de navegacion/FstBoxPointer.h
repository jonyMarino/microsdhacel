#ifndef _FST_BOX_POINTER_H_
#define _FST_BOX_POINTER_H_

#include "stdtypes.h"
#include "Object.h"

struct FstBoxPointer{		// sabe get_new_box
  void * Class;
  struct BlockBoxConstruct* Cbox;
  void* Obj;
  uchar num_obj;
};

extern const struct Class FstBoxPointer;

struct Box *FBP_getNextBox(void * self);


#define NEW_FST_BOX_POINTER(NAME,P_BOXCONSTRUCT,P_OBJ,NUM_OBJ) \
  struct FstBoxPointer NAME ={  \
    &FstBoxPointer,					\
    P_BOXCONSTRUCT,							\
    P_OBJ,											\
    NUM_OBJ  										\
  }


#endif