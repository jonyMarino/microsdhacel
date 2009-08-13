#ifndef _DIAGRAMA_NAVEGACION_H
#define _DIAGRAMA_NAVEGACION_H

#include "Object.h"
#include "ClassBox.h"
#include "Errores.h"
#include "BoxPrincipal.h"

#pragma DATA_SEG DIAGRAMA_NAVEGACION_DATA 
#pragma CODE_SEG DIAGRAMA_NAVEGACION_CODE
#pragma CONST_SEG DEFAULT

#define _VERSION_TIME 1000

/*
** =====================================================================
**    Function      :  DN_StaticInit 
**    Description :    Inicializa el Diagrama de Navegacion con listas
**                    y accesos  ya inicializados y constanter
** =====================================================================
*/
void DN_staticInit(struct BoxList *BoxesOp,struct Array *accesos);
/*
** =====================================================================
**    Function      :  DN_Init 
**    Description :    Inicializa el Diagrama de Navegacion
** =====================================================================
*/
void DN_Init(struct BlockBoxConstruct * pri);
void DN_InitSized(struct BlockBoxConstruct * pri,int nParametrosOperador);
/*
** =====================================================================
**    Function      :  DN_AddBox 
**    Description :    Agrega los Boxes a una lista de parametros
** =====================================================================
*/
void DN_AddBox(uchar access,const char * str,struct BlockBoxConstruct* Cbox,void * Obj,uchar num_obj);
void DN_AddIndexedBox(uchar access,const char * str,struct BlockBoxConstruct* Cbox,void * Obj,uchar num_obj,int index);
uchar DN_addBoxList(uchar access,const char * str,int nBoxes);
/*
** =====================================================================
**    Function      :  DN_SetCodigo 
**    Description :    Setea el Codigo de entrada a las listas
** =====================================================================
*/
TError DN_SetCodigo(uchar access,int Cod);
/*
** =====================================================================
**    Function      :  DN_Proc 
**    Description :    Procesa el Box Actual y le pasa el valor de la tecla
** =====================================================================
*/
void DN_Proc(uchar tecla);
/*
** =====================================================================
**    Function      :  DN_AddAccess 
**    Description :    Agrega un nuevo acceso
** =====================================================================
*/
uchar DN_AddAccess(const char * str,int * Cod);
uchar DN_AddSizedAccess(const char * str,int * Cod,uint nListas);
/*
** =====================================================================
**    Function      :  DN_Refresh 
**    Description :    Refresca los valores del Box Actual
** =====================================================================
*/
void DN_Refresh(void);

#pragma DATA_SEG DEFAULT 
#pragma CODE_SEG DEFAULT

#endif