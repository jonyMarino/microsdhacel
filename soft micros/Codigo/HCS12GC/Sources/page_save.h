#ifndef _PAGE_SAVE_H
#define _PAGE_SAVE_H

#include "stddef.h"
#include "stdtypes.h"
#include "Errores.h"
#include "Mydefines.h"

#define PAGE_SAVE_FLASH_ADDR FLASH_APAGADO_START
/*
** ===================================================================
**     Method     : PageSave_open 
**    Description : Abre la sub-pagina para obtener los valores guardados
**    Returns     : 0  - OK
**                  !0 - la sub-pagina no existe     
** ===================================================================
*/
uchar PageSave_open(char * desc);

/*
** ===================================================================
**     Method     : PageSave_get 
**    Description : Obtiene valor de la pagina abierta
** ===================================================================
*/
TError PageSave_get(uint *);

/*
** ===================================================================
**     Method     : PageSave_WriteOpen 
**    Description : Abre la sub-pagina para escribir los valores a 
**                guardar
** ===================================================================
*/
void PageSave_WriteOpen(char * desc,size_t);

/*
** ===================================================================
**     Method     : PageSave_put 
**    Description : Escribe el valor de la pagina abierta para escritura
** ===================================================================
*/
TError PageSave_put(uint);
/*
** ===================================================================
**     Method     : PageSave_ClrAll 
**    Description : Borra toda la pagina
** ===================================================================
*/
void PageSave_ClrAll(void);

#endif 