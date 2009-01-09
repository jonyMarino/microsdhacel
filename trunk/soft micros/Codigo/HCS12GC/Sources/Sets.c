/*MODULE: Sets.c*/
#include <stddef.h>

#include "DiagramaNavegacion.h"
#include "Errores.h"
#include "PropWithInc.h"
#include "BoxPropBase.h"
#include "IFsh10.h"
#include "ManejadorMemoria.h"
#include "Configuracion.h"
#include "Sets.h"


#pragma CONST_SEG PARAMETERS_PAGE
volatile const int SetC;
#pragma CONST_SEG DEFAULT

/*Codigo*/
int Sets_getCodigo(void * self);
TError Sets_setCodigo(void * self, int Val);


const struct ConstructorPropWInc ParSetC= {
  &PropiedadGenerica,Sets_getCodigo,Sets_setCodigo,get_0,NULL,&PropWInc,"SetC"
};

const struct GetterGenerico * codGetters[]={
  &ParSetC
};

const NEW_ARRAY(arrayCodGetters,codGetters);

const struct BlockConstBoxPropBase CBoxSetC={
      &BoxPropBase,									/* funcion que procesa al box*/
      &ParSetC												
}; 



void Sets_Init(void){
  DN_AddAccess("Cod ",&SetC);  
}

void Sets_Init2(uint nListas){
  DN_AddSizedAccess("Cod ",&SetC,nListas);  
}								

int Sets_getCodigo(void * self){
  return SetC;
}

TError Sets_setCodigo(void * self, int Val){
  return _MANEJADOR_MEMORIA_SET_WORD(pFlash,&SetC,Val);
}

void Sets_AddBoxes(void){
  DN_AddBox(0,"Set ",&CBoxSetC,NULL,0);
}






