#ifndef _BOX_HPP
#define _BOX_HPP


#include <stdtypes.h>
#include "OOC/ooc/lib_cpp/OutputStream.hpp"

class Box{
  public:
    Box(){}
    virtual ~Box(){}
    typedef enum{
      STAY_BOX,
      EXIT_BOX
    }TEstadoBox;
    /*
    ** ===================================================================
    **     Method      :  refresh 
    **     Description :  Funcion para refrescar los valores del Box
    ** ===================================================================
    */
    virtual void refresh(){};
    /*
    ** ===================================================================
    **     Method      :  procesarTecla 
    **     Description :  Funcion que procesa la tecla del Box
    **     Returns:     - STAY_BOX Sigue el mismo Box (si la tecla es de salida
    **                    devuelve NULL ya que no tiene información del siguiente Box)
    **                  - EXIT_BOX si el Box esta en condición de salida.
    **                  - Constructor del siguiente box
    ** ===================================================================
    */
    virtual Box * procesarTecla(uchar tecla,TEstadoBox& estado)=0;    
    inline uchar getNumObjeto(){return numObjeto;}
  private:
    uchar numObjeto;
};

struct BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const=0;
};

struct ConstructorBox{
  const struct BoxFactory * factory;
  Box& getBox(void*obj,uchar numObjeto)const;
};


 
    
#endif