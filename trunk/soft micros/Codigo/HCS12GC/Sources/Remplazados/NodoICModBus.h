#ifndef _NODOICMODBUS_H
#define _NODOICMODBUS_H

#include "Object.h"
#include "Getter.h"
#include "PE_Types.h"
#include "PropiedadGenerica.h"
#include "Array.h"

struct NodoICModBus {
  struct Object super;  
//%-  
  void* dirIni;
  struct Array /*<Getter>*/ * getters;
  struct Object * obj;
};

extern const struct Class NodoICModBus;

int NodoICModBus_getDato(const void * _self,void * dir);
bool NodoICModBus_contieneDireccion(const void * _self,void * dir);
bool NodoICModBus_setDato(const void * _self,void * dir,int dato) ;

const void * NodoICModBus_get_dirFin(const void * _self);

const void * NodoICModBus_get_dirIni(const void * _self);

const struct Array * NodoICModBus_get_getter(const void * _self);

const struct Object * NodoICModBus_get_obj(const void * _self);


#define NEW_NODO_IC_MODBUS(name,getters,dirIni,obj) \
  struct NodoICModBus name={        \
    &NodoICModBus,                        \
    dirIni,                               \
    getters,                              \
    obj                                   \
  }


#endif

