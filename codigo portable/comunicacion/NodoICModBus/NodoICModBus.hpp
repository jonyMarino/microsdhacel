#ifndef _NODOICMODBUS_HPP
#define _NODOICMODBUS_HPP


#include "PropGetterVisual.hpp"
#include "PE_Types.h"
#include "Array.h"

//se encuentra en una version no de produccion, buscar "problema" en el codigo para ver el codigo comprometido 

typedef struct{
  const struct Array/*<ConstructorPropGetterVisual*>*/ * arrayConstructores;
  bool isPropiedad;
}GetsProps;

class NodoICModBus {
  public:
    inline NodoICModBus(void* _dirIni, const GetsProps& _getProps,void * _obj):dirIni(_dirIni),getsProps(_getProps),obj(_obj){}
    int getDato(void * dir);
    bool contieneDireccion(void * dir);
    bool setDato(void * dir,int dato) ;  //no debe utilizarse en interrupcion, utiliza un new
    bool isEscribible();
    const void * getDirFin();
    const void * getDirIni();
    const struct Array * getGetter();
    void * getObj();  
  private:
    void* dirIni;
    const GetsProps& getsProps;
    void * obj;
};




#endif

