#ifndef _METHOD_CONTAINER_HPP
#define _METHOD_CONTAINER_HPP


#include "OOC/util/lib_cpp/Set.hpp"


class MethodContainer:public Set{
  public:
    MethodContainer();
    virtual bool add(void*);
    void executeMethods();    
};

#endif