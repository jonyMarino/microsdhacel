#ifndef _BOX_ACCESS_HPP
#define _BOX_ACCESS_HPP

#include <stdtypes.h>

#include "Box.hpp"

class BoxAccess:public Box{
  public:
    BoxAccess(const char*desc,int codigo); 
    virtual Box * procesarTecla(uchar tecla,TEstadoBox& estado);
  private:
    int valorTmp;
    int codigo;
};


#endif