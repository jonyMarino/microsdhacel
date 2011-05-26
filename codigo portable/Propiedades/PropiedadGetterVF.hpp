#ifndef _PROPIEDAD_GETTER_VF_HPP
#define _PROPIEDAD_GETTER_VF_HPP

#include "Standard/Getter.hpp" 

struct ArgumentosPropiedadGetterVF{
  int (*get)(void * obj,int);
}; 
    
class PropiedadGetterVF:public Getter{ 
  public:      
    PropiedadGetterVF(void* _obj,int _Vtmp,const struct ArgumentosPropiedadGetterVF* _constructor);
    int getVal();
    void * getObjeto();
    int getNumero();
    void print(OutputStream& os);         
  protected:
    const struct ArgumentosPropiedadGetterVF* getArgumentos();  
  private:
    const struct ArgumentosPropiedadGetterVF* pget;
    int Vtmp;
    void * obj;  
};





#endif