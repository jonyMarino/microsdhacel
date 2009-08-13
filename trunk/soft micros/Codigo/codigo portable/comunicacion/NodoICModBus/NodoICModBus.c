
#include "NodoICModBus.h"
#include "Propiedad.h"

void NodoICModBus_defContructor(void * _self,va_list * args);

const struct Class NodoICModBus={
  CLASS_INITIALIZATION(Class,
                       NodoICModBus,
                       Object,
                       NodoICModBus_defContructor,
                       NULL,
                       NULL,
                       NULL)
};

void NodoICModBus_contructor(void * _self,struct Array *getters,struct Object * obj,void* dirIni){
  struct NodoICModBus *self =(struct NodoICModBus *) _self;
  self->getters = getters;
  self->obj = obj;
  self->dirIni = dirIni;

}

void NodoICModBus_defContructor(void * _self,va_list * args){
  NodoICModBus_contructor(_self,va_arg(*args,struct Array *),va_arg(*args,struct Object *),va_arg(*args,void*)); 
}

int NodoICModBus_getDato(const void * _self,void * dir) {
  const struct NodoICModBus *self =(struct NodoICModBus *) _self;
  struct Getter * getter;
  
  if(!NodoICModBus_contieneDireccion(self,dir))  
    return 0; //cambiar: error
  getter= (struct Getter *)Array_get(self->getters, ((size_t)dir - (size_t)self->dirIni) /2);
  return ClassProp_getVal(getter,self->obj);    
}

bool NodoICModBus_contieneDireccion(const void * _self,void * dir) {
  const struct NodoICModBus *self =(struct NodoICModBus *) _self; 
  if(self->dirIni<=dir && NodoICModBus_get_dirFin(_self)>=dir)
    return TRUE;
  return FALSE;
}

bool NodoICModBus_setDato(const void * _self,void * dir,int dato) {
  const struct NodoICModBus *self =(struct NodoICModBus *) _self;
  struct Getter * getter;
  
  if(!NodoICModBus_contieneDireccion(self,dir))  
    return 1; //cambiar: error
  getter=(struct Getter *) Array_get(self->getters, ((size_t)dir - (size_t)self->dirIni)/2);
  if(instanceOf(getter,(const struct Class * const)&PropiedadGenerica))
    return ClassProp_setVal(getter,self->obj,dato); 
  return ERR_OK; 
}

const void * NodoICModBus_get_dirFin(const void * _self) {
  const struct NodoICModBus *self = (struct NodoICModBus *)_self; 
  return (const void *)((size_t)self->dirIni + (size_t) Array_count(self->getters) * 2) ;
}

const void * NodoICModBus_get_dirIni(const void * _self) {
  const struct NodoICModBus *self =(struct NodoICModBus *) _self; 
  return self->dirIni;
}

const struct Array/*<Getter>*/ * NodoICModBus_get_getter(const void * _self) {
  const struct NodoICModBus *self =(struct NodoICModBus *) _self; 
  return self->getters;
}

/*const struct Object*/void * NodoICModBus_get_obj(const void * _self) {
  const struct NodoICModBus *self = (struct NodoICModBus *)_self; 
  return self->obj;
}

