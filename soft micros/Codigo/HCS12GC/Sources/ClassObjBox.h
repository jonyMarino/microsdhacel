#ifndef _CLASS_BOX_OBJ_H
#define _CLASS_BOX_OBJ_H

/*  CLASE PURA  */
#include <stdtypes.h>

#include "ClassBox.h"


struct ObjBox{
  struct Box _box;
  uchar NumObj;
};

extern const struct BoxClass ObjBox;


/*
** ===================================================================
**     Method      :  ObjBox_Constructor 
**     Description :  Constructor del Box para Objetos
** ===================================================================
*/
void ObjBox_Constructor(void * _self, uchar NumObj);

/*
** ===================================================================
**     Method      :  ObjBox_PrintDescription 
**     Description :  Imprime la descripción pasada del Box con su número
**                    de objeto.
** ===================================================================
*/
void ObjBox_PrintDescription(void * _self,const char * str,uchar num_display);


#endif