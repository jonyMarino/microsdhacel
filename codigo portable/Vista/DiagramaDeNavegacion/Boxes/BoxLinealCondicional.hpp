#ifndef _BOX_LINEAL_CONDICIONAL_HPP
#define _BOX_LINEAL_CONDICIONAL_HPP

#include "BoxLineal.hpp"

struct ConstructorBoxLinealCondicional{
  struct ConstructorBoxLineal super; 
  uchar (*getNroProp)(void * obj);    
};

class BoxLinealCondicional:public BoxLineal{
  public:
    BoxLinealCondicional(struct ConstructorBoxLinealCondicional * constructor,void*obj,uchar numObjeto);  
    ~BoxLinealCondicional();   
    
};


struct BoxLinealCondicionalFactory:public BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const{
    return *new BoxLinealCondicional((struct ConstructorBoxLinealCondicional *)args,obj,numObjeto);
  }
};

extern const struct BoxLinealCondicionalFactory boxLinealCondicionalFactory;



#endif
