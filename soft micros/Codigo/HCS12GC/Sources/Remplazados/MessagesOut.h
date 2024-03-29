#ifndef _MESSAGES_OUT_H
#define _MESSAGES_OUT_H

#include "NodoDoble.h"

struct MessageOut{
  struct Object super;
  struct DobleList * lst;
};

extern const void * const MessageOut;

typedef struct NodoDbl * Message;
/*
** ===================================================================
**    Function    :  MessageOut_AddMessage 
**    Description :  Agerga un mensaje de salida
** ===================================================================
*/
Message MessageOut_AddMessage(void * _self,char * _str);

/*
** ===================================================================
**    Function    :  MessageOut_DeleteMessage 
**    Description :  Borra el mensaje de la salida
** ===================================================================
*/
uchar MessageOut_DeleteMessage(void * _self,Message _msj);

/*
** ===================================================================
**    Function    :  MessageOut_getMessage 
**    Description :  Obtiene el mensaje a partir del numero pasado
**                  (0-size)
** ===================================================================
*/
char * MessageOut_getMessage(void * _self,uint _msj_num);


#endif