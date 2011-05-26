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
#include <stddef.h>
#include "MessagesOut.hpp"


/*
** ===================================================================
**    Method      :  MessageOut_AddMessage 
**    Description :  Agerga un mensaje de salida
** ===================================================================
*/
MessagesOut::Message MessagesOut::addMessage(const char * _str){
  return lst.insertFirst((void*)_str);
}

/*
** ===================================================================
**    Method      :  MessageOut_DeleteMessage 
**    Description :  Borra el mensaje de la salida
** ===================================================================
*/
uchar MessagesOut::deleteMessage(Message msj){
  return lst.deleteNodo(msj);  
}

/*
** ===================================================================
**    Method      :  MessageOut_getMessage 
**    Description :  Obtiene el mensaje a partir del numero pasado
**                  (0-size)
** ===================================================================
*/
char * MessagesOut::getMessage(uint _msj_num){  
  return (char *)lst.getDato(_msj_num);
  
}





