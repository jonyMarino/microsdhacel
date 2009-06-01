/*  MODULE com_events*/
#include <stdlib.h>

#include "Configuracion.h"
#include "modbus.h"
#include "Mydefines.h"
#include "PropiedadGenerica.h"
#include "Grabacion.h"
#include "ArrayList.h"
#include "CompilationOptions.h"
#include "PromBkp.h"

#include "com_events.h"

#pragma DATA_SEG COM_EVENTS_DATA                                            
#pragma CODE_SEG COM_EVENTS_CODE 




/*EscrituraDemorada*/
struct EscrituraDemorada{
  struct Object super;
  struct NodoICModBus * nodo;
  void * dir;
  uint dato;
};

void EscrituraDemorada_defConstructor(void * _self,va_list *args){
  struct EscrituraDemorada* self = _self;
  self->nodo = va_arg(*args,void*);
  self->dir = va_arg(*args,void*);
  self->dato = va_arg(*args,int); 
}

void EscrituraDemorada_escribir(void * _self){
  struct EscrituraDemorada* self = _self;
  NodoICModBus_setDato(self->nodo,self->dir,self->dato);  
}

const struct Class EscrituraDemorada={
  CLASS_INITIALIZATION(Class,
                       EscrituraDemorada,
                       Object,
                       EscrituraDemorada_defConstructor,
                       NULL,
                       NULL,
                       NULL
                       )
};

/*FIN EscrituraDemorada*/

/* Atributos*/
struct ArrayList/*<NodoICModBus>*/ *comProps;
struct EscrituraDemorada escrituraDemorada;
struct EscrituraDemorada * pEscrituraDemorada=NULL;
 
/*
** ===================================================================
**    Function    : com_Init 
**    Description : Inicializa la comunicacion
** ===================================================================
*/
void com_Init(void){
  Comu_Init();
  comProps=new(&ArrayList);
}
/*
** ===================================================================
**    Function    : com_Init 
**    Description : Inicializa la comunicacion
** ===================================================================
*/
void com_initialization(struct ArrayList * arrayGetters){
  Comu_Init();
  comProps = arrayGetters; 
}
/*
** ===================================================================
**    Function    : com_Add 
**    Description : Asocia propiedades o getters a direcciones de la 
**              comunicacion
** ===================================================================
*/
struct NodoICModBus * com_Add(const struct ClassPropiedad ** prop,void * Obj,word dir_ini,word dir_end){
  struct Array * getters = new(&Array,dir_end - dir_ini + 1);
  struct NodoICModBus * p_tmp;
  int i;
  
  for(i=0;i< dir_end - dir_ini +1;i++){
    Array_set(getters,i,prop[i]);
  }
  
  p_tmp=new(&NodoICModBus,getters,Obj,dir_ini,dir_end);
  

  com_addNodo(p_tmp);   
   
  return p_tmp;
}

/*
** ===================================================================
**    Function    : com_addNodo 
**    Description : Agrega un nodo de comunicacion a la comunicacion
** ===================================================================
*/
void com_addNodo(struct NodoICModBus * nodo){
  
  if(nodo)    //cambiar error
    ArrayList_Add(comProps,nodo);    

}

/*
** ===================================================================
**    Function    : com_Handler 
**    Description : Manejador de la comunicacion. Verifica si hay 
**              alguna propiedad para escribir.
** ===================================================================
*/
//cambiar
#warning cambiar por una unica (o N) posible propiedad y la especificacion de que el main loop debe tardar como maximo 1 recive + 1 send + 3 ms	(15 ms a 9600 baud) (o * N)
void com_Handler(void){
  if(pEscrituraDemorada){
    EscrituraDemorada_escribir(pEscrituraDemorada);
    deleteAlloced(pEscrituraDemorada);
    pEscrituraDemorada = NULL;
  }
}

word ModBus_getAddressData(word address){
  byte i;  
  byte count = ArrayList_count(comProps);
    for(i=0;i<count;i++){	
      void * nodo = ArrayList_get(comProps,i);															
      if(NodoICModBus_contieneDireccion(nodo,address))
        return NodoICModBus_getDato(nodo,address);
    }
    if(i==count)				// no es la dir de un parametro?
      return *(word*)address;
}

#if FLASH_COM_END < RAM_COMUNICACION_START
  #error revisar abajo
#endif

byte ModBus_writeAddress(word address,int dato){
  byte i; 
  byte count = ArrayList_count(comProps);
    
  for(i=0;i<count;i++){	
      void * nodo = ArrayList_get(comProps,i);																	
      if(NodoICModBus_contieneDireccion(nodo,address)){
       // if(instanceOf(getter,&PropiedadGenerica))     cambiar: poner aqui
        if(pEscrituraDemorada)
          return 1; //cambiar : error no alcanzo el tiempo
        newAlloced(&escrituraDemorada,&EscrituraDemorada,nodo,address,dato);
        pEscrituraDemorada = &escrituraDemorada;
        PromBkp_demorarGrabado(pFlash,30);
        return ERR_OK;       
      }
    }
    if(i==count){                
      if(address >= RAM_COMUNICACION_START && address <= RAM_COMUNICACION_END)        
        *(volatile word*)address =dato;													
      else if((address >= FLASH_COM_START && address <= FLASH_COM_END)){
        PromBkp_demorarGrabado(pFlash,30);
        (void) _MANEJADOR_MEMORIA_SET_WORD(pFlash,(word*)address,dato);
      } else
        return ERR_ADDR;     
    }
}

byte ModBusRead(byte * data){
    word Address;
    
    if (data[4]!=0 || data[5]!=1)
      return ERR_VALUE;
    Address=*((word *)&data[2]);
    data[2]=data[5]*2;

    *((word *)&data[3])=ModBus_getAddressData(Address); 
 
    return ModBus_Send(data,5);
}



byte ModBusWrite(byte * data){

    word Address=*((word *)&data[2]);
    int Data = *(int *)&data[4];
 		byte err;
 		
    err=ModBus_writeAddress(Address,Data);
    if(err)
      return err;
    
    return ModBus_Send(data,6); 
           
}

#ifdef _N_MODBUS

byte DhacelRead(byte * data){
  word Address=*((word *)&data[2]);

  *((word *)&data[4])=ModBus_getAddressData(Address); 

  return ModBus_Send(data,6);
}

byte DhacelWrite(byte * data){
  return ModBusWrite(data);
}

#endif

/*
** ===================================================================
**    Function    : com_Recognize 
**    Description : Devuelve las opciones de compilacion
** ===================================================================
*/
void com_Recognize(byte * data){
  *(long*)&data[2]=_COMP_OPTIONS;
  ModBus_Send(data,6);  
}