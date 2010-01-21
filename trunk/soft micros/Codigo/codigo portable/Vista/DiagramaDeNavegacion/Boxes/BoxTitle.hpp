#ifndef _BOX_TITULO_HPP
#define _BOX_TITULO_HPP


#include <stdtypes.h>
#include "Box.hpp"


class BoxTitulo:public Box{
  public:
    BoxTitulo(const char * str1,const char * str2);
    virtual ~BoxTitulo(){}
    virtual Box * procesarTecla(uchar tecla,TEstadoBox& estado);
      
};


#endif 