#ifndef _SET_HPP
#define _SET_HPP

#include "OOC/util/lib_cpp/LinkedList.hpp"

//un Set no agrega el dato si los datos son iguales.
class Set: public LinkedList{
  public:
    virtual bool add(void *dato);
    virtual bool aniadir(void *dato);
};

#endif