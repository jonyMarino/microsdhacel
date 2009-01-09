/*MODULE: page_save.c*/
/*
La analogia de este modulo es el de un archivo que se guarda, para su 
posterior uso.
Al caer la alimentacion se guarda un identificador y el tamanio guardado 
de informacion utilizando la direccion asignada en OnPowDown.h
Este identificador debe ser un string.
Luego del tiempo asignado en OnPowDown.h, la pagina de grabacion se borra

*/
#include <string.h>

#include "page_save.h"
#include "IFsh10.h"
#include "Grabacion.h"

static word pos=PAGE_SAVE_FLASH_ADDR;
static word size;
static word sub_page_pos;
/*
** ===================================================================
**     Method     : PageSave_Init 
**    Description : Inicializacion del modulo  
** ===================================================================
*/
void PageSave_Init(void){
  pos=PAGE_SAVE_FLASH_ADDR;
}
/*
** ===================================================================
**    Method      : PageSave_open 
**    Description : Abre la sub-pagina para obtener los valores guardados
**    Returns     : 0  - OK
**                  !0 - la sub-pagina no existe     
** ===================================================================
*/
uchar PageSave_open(char * desc){
  word init_pos = pos;
  bool restart=FALSE;
  size_t length;
  while(strcmp(desc,(char*)pos)){
    length=strlen(desc);
    pos+=length+1;
    if(!(length&1))		 // es par
      pos++;
    if(*(word *)pos==0xFFFF){ // no fue grabado
      if(init_pos==PAGE_SAVE_FLASH_ADDR)
        return ERR_RANGE;
      else{  
        pos=PAGE_SAVE_FLASH_ADDR;
        init_pos = pos;
      	restart=TRUE;
      	continue;
      }  
    }
    pos+=*(word *)pos;	 /* sumo size */
    if(pos>=FLASH_APAGADO_END){  
      pos=PAGE_SAVE_FLASH_ADDR;
    	restart=TRUE;
    }
    if(restart && pos>=init_pos)
      return ERR_RANGE;
  }
  length=strlen(desc);
  if(!(length&1))		 // es par
    pos++;
  pos+=length+1;
  size=*(word *)pos;
  pos+=2;
  
  sub_page_pos=pos;
  
  return 0;   
}

/*
** ===================================================================
**     Method     : PageSave_get 
**    Description : Obtiene valor de la pagina abierta
** ===================================================================
*/
TError PageSave_get(uint * data){
  if( pos-sub_page_pos >= size )
    return ERR_RANGE;
  *data=*(word*)pos; 
  pos+=2;  
  return ERR_OK;
}

/*
** ===================================================================
**     Method     : PageSave_WriteOpen 
**    Description : Abre la sub-pagina para escribir los valores a 
**                guardar
** ===================================================================
*/
void PageSave_WriteOpen(char * desc,size_t _size){
  byte i;
  for(i=0;desc[i]!='\0' && desc[i+1]!='\0';i+=2){
    WriteWord((void*)pos,*(word*)&desc[i]);
    pos+=2;  
  }
  if(desc[i]=='\0')
    WriteWord((void*)pos,desc[i]<<8);  
  else
    WriteWord((void*)pos,*(word*)&desc[i]);
     
  
  pos+=2;
  WriteWord((void*)pos,_size);
  size= _size;
  pos+=2;
  sub_page_pos=pos;  
}

/*
** ===================================================================
**     Method     : PageSave_put 
**    Description : Escribe el valor de la pagina abierta para escritura
** ===================================================================
*/
TError PageSave_put(uint data){
  if( pos-sub_page_pos >= size )
    return ERR_RANGE;
  WriteWord((void*)pos,data); 
  pos+=2;  
  return ERR_OK;
}
/*
** ===================================================================
**     Method     : PageSave_ClrAll 
**    Description : Borra toda la pagina
** ===================================================================
*/
void PageSave_ClrAll(void){
  EraseSectorInternal(PAGE_SAVE_FLASH_ADDR);
  pos=PAGE_SAVE_FLASH_ADDR;
}