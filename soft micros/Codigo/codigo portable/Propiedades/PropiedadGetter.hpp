#ifndef _PROPIEDAD_GETTER_HPP
#define _PROPIEDAD_GETTER_HPP


#include "ConstructorPropiedadGetter.hpp"

class PropiedadGetter{ 
  public:  
    class ConstructorPropiedadGetter{
      public:
       // struct PropiedadGetterFactory * factory;  
        void* (*creator)(void* _obj,ConstructorPropiedadGetter* _constructor);
        int (*get)(void * obj);
    };
    
    PropiedadGetter(void* _obj,ConstructorPropiedadGetter* _constructor);
    int get();
    void * getObjeto();
    

    
    /*struct PropiedadGetterFactory{
      public:
        virtual PropiedadGetter& getPropiedad(void*obj,struct ConstructorPropiedadGetter& args)const;
    };*/
    
    static  PropiedadGetter* creator(void* _obj,ConstructorPropiedadGetter* _constructor);
    
    
    
   // static Getter * getGetter(ConstructorPropiedadGetter * self,void * obj);
    
  protected:
    ConstructorPropiedadGetter* getConstructor();  
  private:
    const ConstructorPropiedadGetter* constructor;
    void * obj;  
};





#endif