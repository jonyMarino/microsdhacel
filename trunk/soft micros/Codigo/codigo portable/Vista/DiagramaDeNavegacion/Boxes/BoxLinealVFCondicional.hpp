#ifndef _BOX_LINEAL_VF_CONDICIONAL_HPP
#define _BOX_LINEAL_VF_CONDICIONAL_HPP

#include "BoxLinealVF.hpp"

struct ConstructorBoxLinealVFCondicional{
  struct ConstructorBoxLinealVF super; 
  uchar (*getNroProp)(void * obj);    
};

class BoxLinealVFCondicional:public BoxLinealVF{
  public:
    BoxLinealVFCondicional(struct ConstructorBoxLinealVFCondicional * constructor,void*obj,uchar numObjeto);  
    ~BoxLinealVFCondicional();   
    
};


struct BoxLinealVFCondicionalFactory:public BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const{
    return *new BoxLinealVFCondicional((struct ConstructorBoxLinealVFCondicional *)args,obj,numObjeto);
  }
};

extern const struct BoxLinealVFCondicionalFactory boxLinealVFCondicionalFactory;



#endif
