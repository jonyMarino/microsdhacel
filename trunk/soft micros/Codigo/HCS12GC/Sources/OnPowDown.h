/*MODULE: OnPowDown (on power down and rise)

¡¡¡¡NO SOPORTA MULTITHREAD!!!

  Este objeto, actua ante una caida de alimentacion detectada 
mediante un modulo de menor nivel, y actua ante la subida de alimentacion.
La analogia de este modulo es el de un archivo que se guarda, para su 
posterior uso.
Al caer la alimentacion se guarda un identificador y el tamanio guardado 
de informacion utilizando la direccion asignada en OnPowDown.h
Este identificador debe ser un string.
Luego del tiempo asignado en OnPowDown.h, la pagina de grabacion se borra
*/

#ifndef _ON_POW_H
#define _ON_POW_H


#include "Object.h"
#include "Errores.h"
#include "stddef.h"


/*
** ===================================================================
**     Event       :  OnPowDown_enable
**     Description :
** ===================================================================
*/
void OnPowDown_enable(void * _self);

/*
** ===================================================================
**     Event       :  OnPowDown_getInstance
**     Description :
** ===================================================================
*/
void* OnPowDown_getInstance(void);

/*
** ===================================================================
**     Event       :  OnPowDown_handler
**     Description :
**         Funcion a llamar ante caida de energia
** ===================================================================
*/
void OnPowDown_handler(void * _self);

/*
** ===================================================================
**     Event       :  OnPowDown_AddMethod 
**     Description :
**         Agrega un metodo a llamar ante caida de energia
** ===================================================================
*/
void OnPowDown_addPowDownListener(void * _self,struct Method *metodo);
/*
** ===================================================================
**     Method      :  OnPowDown_Destructor
**     Description :  Destructor  del objeto
** ===================================================================
*/
void * OnPowDown_Destructor(void * _self);



#endif 