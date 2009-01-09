#ifndef _COM_EVENTS_H
#define _COM_EVENTS_H

#include "PE_Types.h"
#include "PropiedadGenerica.h"
#include "NodoICModBus.h"

#pragma CODE_SEG COM_EVENTS_CODE
/*
** ===================================================================
**    Function    : com_Init 
**    Description : Inicializa la comunicacion
** ===================================================================
*/
void com_Init(void);
void com_initialization(struct ArrayList * arrayGetters);

/*
** ===================================================================
**    Function    : com_addNodo 
**    Description : Agrega un nodo de comunicacion a la comunicacion
** ===================================================================
*/
void com_addNodo(struct NodoICModBus * nodo);

/*
** ===================================================================
**    Function    : com_Add 
**    Description : Asocia propiedades o getters a direcciones de la 
**              comunicacion
** ===================================================================
*/
struct NodoICModBus * com_Add(const struct ClassPropiedad ** prop,void * Obj,word dir_ini,word dir_end);
/*
** ===================================================================
**    Function    : com_Handler 
**    Description : Manejador de la comunicacion. Verifica si hay 
**              alguna propiedad para escribir.
** ===================================================================
*/
void com_Handler(void);

byte DhacelRead(byte * data);

byte DhacelWrite(byte * data);

byte ModBusRead(byte * data);

byte ModBusWrite(byte * data);

/*
** ===================================================================
**    Function    : com_Recognize 
**    Description : Devuelve las opciones de compilacion
** ===================================================================
*/
void com_Recognize(byte * data);

#pragma CODE_SEG DEFAULT

#endif