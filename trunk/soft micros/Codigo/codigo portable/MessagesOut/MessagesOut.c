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
#include "stddef.h"
#include "MessagesOut.h"

void MessageOut_DefConstructor(void * _self,va_list * args);
void MessageOut_Destructor(void * _self);

const struct Class TableMessageOut={
      CLASS_INITIALIZATION(Class,MessageOut,Object,MessageOut_DefConstructor,MessageOut_Destructor,Object_differ,Object_puto)
     
};

const void * const MessageOut=&TableMessageOut;
/*
** ===================================================================
**    Method      :  MessageOut_Constructor 
**    Description :  Constructor del Objeto
** ===================================================================
*/
void MessageOut_Constructor(void * _self){
  struct MessageOut* _m= (struct MessageOut*)_self;
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
void MessageOut_Destructor(void * _self){
  struct MessageOut* _m=(struct MessageOut*)_self;
  deleteAndNil(&_m->lst);  
      
}
/*
** ===================================================================
**    Method      :  MessageOut_AddMessage 
**    Description :  Agerga un mensaje de salida
** ===================================================================
*/
Message MessageOut_AddMessage(void * _self,char * _str){
  struct MessageOut* _m=(struct MessageOut*)_self;
  if(!_m->lst){
    
    _m->lst= new DobleList();
    if(!_m->lst)
      return NULL;  //error
  }
  return _m->lst->insertFirst(_str);
}

/*
** ===================================================================
**    Method      :  MessageOut_DeleteMessage 
**    Description :  Borra el mensaje de la salida
** ===================================================================
*/
uchar MessageOut_DeleteMessage(void * _self,Message _msj){
  struct MessageOut* _m=(struct MessageOut*)_self;
  return _m->lst->deleteNodo(_msj);  
}

/*
** ===================================================================
**    Method      :  MessageOut_getMessage 
**    Description :  Obtiene el mensaje a partir del numero pasado
**                  (0-size)
** ===================================================================
*/
char * MessageOut_getMessage(void * _self,uint _msj_num){
  struct MessageOut* _m=(struct MessageOut*)_self;
  
  if(!_m->lst)
    return NULL;
  
  return (char *)_m->lst->getDato(_msj_num);
  
}





