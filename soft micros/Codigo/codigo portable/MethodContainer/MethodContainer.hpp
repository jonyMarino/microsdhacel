#ifndef _METHOD_CONTAINER_HPP
#define _METHOD_CONTAINER_HPP


#include "OOC/util/lib_cpp/LinkedList.hpp"


class MethodContainer:public LinkedList{
  public:
    MethodContainer();
    virtual bool add(void*);
    void executeMethods();    
};

#endif