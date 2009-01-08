#ifndef _GRABACION_H
#define _GRABACION_H

#include "PE_Types.h"
#include "IFsh10.h"

typedef void(*Grab_OnErase)(void*,word*);

void Grabacion_Init(void);

void Grabacion_Disable(void);

void Grabacion_Enable(void);

void Grabacion_BorrarPag(word Addr);

void Grabacion_DelaySave(word time);

bool Grabacion_save_ready(void);

void Grabacion_Handler(void);

void Grabacion_OnAble(void);

bool Grabacion_ToSave(void);

/*
** ===================================================================
**    Function    :  Grabacion_AddOnEraseEvent 
**    Description : 
** ===================================================================
*/
void Grabacion_AddOnEraseEvent(Grab_OnErase pmethod,void*Obj);



#endif