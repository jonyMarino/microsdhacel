#ifndef _CLASS_BOX_H
#define _CLASS_BOX_H

#include <stdarg.h>
#include "Object.h"
#include "stdtypes.h"

struct Box{
  void * _box;
};

struct BlockBoxConstruct{
  void * _box;  
};

typedef enum{
  STAY_BOX,
  EXIT_BOX
}BOX_State;

/*
** ========================================================================
**     Function     :  vBoxes_Construct 
**     Type         :  Polimorfica
**     Description  :  Constructor de Boxes recibiendo un Bloque Constructor
**     Arguments    :
**      * pBlockConst   - puntero a Bloque constructor con la info que necesita el Box
**      * Obj           - puntero al Objeto que debe manejar el Box
** ========================================================================
*/
void * vBoxes_Construct(void * pBlockConst,void * Obj,uchar numObj);

/*
** ===================================================================
**     Method      :  vBox_Refresh 
**     Type         : Virtual
**     Description :  Funcion Para refrescar los valores del Box
** ===================================================================
*/
void vBox_Refresh(void * _self);

/*
** ===================================================================
**     Method      :  vBox_ProcKey 
**     Type        :  Virtual
**     Description :  Funcion que procesa la tecla del Box
**     Returns:     - STAY_BOX Sigue el mismo Box (si la tecla es de salida
**                    devuelve NULL ya que no tiene información del siguiente Box)
**                  - EXIT_BOX si el Box esta en condición de salida.
**                  
** ===================================================================
*/
BOX_State vBox_ProcKey(void * _self,uchar tecla);

/*
** ===================================================================
**     Method      :  vBox_getNextBlockConstr 
**     Type        :  Virtual
**     Description :  Funcion que devuelve el Bloque Constructor del siguiente Box
**     
**     Returns:     - NULL  (si 
**                    devuelve NULL es porque no tiene información del siguiente Box)
**                  - Puntero a Bloque Constructor del siguiente Box si ocurrio una salida.
**                  
** ===================================================================
*/
struct BlockConstruct * vBox_getNextBlockConstr(void * _self,uchar tecla);


//Definicion de la vTable
struct BoxClass{
  struct Class super;
  void(*Refresh)(void*);
  BOX_State(*ProcKey)(void*,uchar);
  struct BlockBoxConstruct *(*get_NextBlockConstr)(void*,uchar); 
};

#define BOXCLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto,refresh,procKey,getNextBlock)\
    CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto),  \
    refresh,   \
    procKey,  \
    getNextBlock

extern const struct Class BoxClass;
extern const struct BoxClass Box;  
    
#endif