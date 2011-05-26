#ifndef _PROPIEDAD_GETTER_HPP
#define _PROPIEDAD_GETTER_HPP

#include "Standard/Getter.hpp" 

struct ArgumentosPropiedadGetter{
  int (*get)(void * obj);
}; 
    
class PropiedadGetter:public Getter{ 
  public:      
    PropiedadGetter(void* _obj,const struct ArgumentosPropiedadGetter* _constructor);
    int getVal();
    void * getObjeto();
    void print(OutputStream& os);         
  protected:
    const struct ArgumentosPropiedadGetter* getArgumentos();  
  private:
    const struct ArgumentosPropiedadGetter* pget;
    void * obj;  
};





#endif