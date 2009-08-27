/*MODULE: MessagesOut.c
**     Filename  : MessagesOut.C
**     Project   : Controlador
**     Processor : MC9S12GC32CFU
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 23/01/2008, 14:51
**     Abstract  :
**							Este modulo se utiliza para guardar
**     los mensajes a mostrar como un "standard out",
**     Al sacar un mensaje fuera, se puede eliminar el
**     mensaje mediante el puntero al nodo devuelto.
**     La implementacion utiliza una lista doblemente 
**     enlazada. El encargado de mostrar los mensajes 
**     sera otro modulo( por ej.: BoxPrincipal) 
*/

#include <stdarg.h>
#include "DobleList.h"
#include "stddef.h"
#include "MessagesOut.h"

void MessageOut_DefConstructor(void * _self,va_list * args);
void *MessageOut_Destructor(void * _self);

const struct Class TableMessageOut={
        &Class,
  "",
  &Object,
      sizeof(struct MessageOut),
      MessageOut_DefConstructor,
      MessageOut_Destructor,
      NULL, // differ
      NULL // puto
};

const void * const MessageOut=&TableMessageOut;
/*
** ===================================================================
**    Method      :  MessageOut_Constructor 
**    Description :  Constructor del Objeto
** ===================================================================
*/
void MessageOut_Constructor(void * _self){
  struct MessageOut* _m= _self;
  _m->lst=NULL;
}
/*
** ===================================================================
**    Method      :  MessageOut_DefConstructor 
**    Description :  Constructor por defecto del Objeto
** ===================================================================
*/
void MessageOut_DefConstructor(void * _self,va_list * args){
  MessageOut_Constructor(_self);    
}
/*
** ===================================================================
**    Method      :  MessageOut_Destructor 
**    Description :  Destructor del Objeto
** ===================================================================
*/
void *MessageOut_Destructor(void * _self){
  struct MessageOut* _m= _self;
  deleteAndNil(&_m->lst);  
  return _self;    
}
/*
** ===================================================================
**    Method      :  MessageOut_AddMessage 
**    Description :  Agerga un mensaje de salida
** ===================================================================
*/
Message MessageOut_AddMessage(void * _self,char * _str){
  struct MessageOut* _m= _self;
  if(!_m->lst){
    
    _m->lst= _new(&DobleList);
    if(!_m->lst)
      return NULL;  //error
  }
  return DobleList_InsertFirst(_m->lst,_str);
}

/*
** ===================================================================
**    Method      :  MessageOut_DeleteMessage 
**    Description :  Borra el mensaje de la salida
** ===================================================================
*/
uchar MessageOut_DeleteMessage(void * _self,Message _msj){
  struct MessageOut* _m= _self;
  return DobleList_DeleteNodo(_m->lst,_msj);  
}

/*
** ===================================================================
**    Method      :  MessageOut_getMessage 
**    Description :  Obtiene el mensaje a partir del numero pasado
**                  (0-size)
** ===================================================================
*/
char * MessageOut_getMessage(void * _self,uint _msj_num){
  struct MessageOut* _m= _self;
  
  if(!_m->lst)
    return NULL;
  
  return DobleList_getDato(_m->lst,_msj_num);
  
}





