#ifndef _MENSAJES_H
#define _MENSAJES_H

#include "PE_Types.h"

#define ERR_OK 0
#define ERR_ARGS 1
#define ERR_PRIORIDAD 2

byte SetMessage(byte Display,byte iMensaje);
/*
** ===================================================================
**     Funcion      :  SetMessage (byte Display,byte iMensaje)
**
**     Description :
**         Esta funcion selecciona un mensaje definido en Mensajes.c,
**         en el array MENSAJES, de 1 a CANTIDAD_MENSAJES(Macro) para 
**         atribuirselo algun display, de 0 a CANTIDAD_DISPLAYS-1.
**         La funcion no muestra en el display nada solo deja en un buffer
**         posibles capturas de mensajes con GetMessage(byte Display).  
**     Parameters  : Display: Display al que se le quiere atribuir el Mensaje
**                   iMensaje:Numero del mensaje en el array MENSAJES que se 
**                   quiere atribuir al display
**     Returns     : ERR_ARGS - error en el valor de los argumentos
**                   ERR_PRIORIDAD - mensaje de menor prioridad que el actual
**                   ERR_OK - Seteo exitoso
** ===================================================================
*/
char* GetMessage(byte Display);
/*
** ===================================================================
**     Funcion      :  GetMessage (byte Display,byte iMensaje)
**
**     Description :
**         Esta funcion devuelve un puntero a la cadena de un mensaje 
**         definido en Mensajes.c, en el array MENSAJES, atribuido a 
**         algun display, de 0 a CANTIDAD_DISPLAYS-1.
**         La funcion no muestra en el display nada solo devuelve el mensaje
**         que seguramente se desea mostrar.
**         En caso de no haber ningun mensaje atribuido la función devuelve 
**         NULL.
**     Parameters  : Display: Display  que tiene atribuido el Mensaje
**     Returns     : NULL - Si no hay mensaje
**                   puntero a cadena - del mensaje atribuido al display
** ===================================================================
*/
#endif
