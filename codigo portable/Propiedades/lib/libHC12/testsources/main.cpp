#include "ConstructorPropiedadGetter.hpp"
#include "PropGetterVisual.hpp"

/*
const ConstructorGetter c = {
  (void*)0,
  (void*)0
};

const ConstructorGetterEspecializado  c2={
  (void*)0,
  (void*)0,
  (void*)0
};   */
struct A{
 /* int get0()const{
    return 0;
  }  */
};

struct B:public A{
  const struct A *a;
 /* int get1()const{
    return 1;
  }    */
};

//const struct B
int get0(void*a){
  return 0;
}

const struct PropiedadGetterFactory f;
const struct ConstructorPropiedadGetter c={
  &f,
  get0
}; 

const struct PropGetterImprimibleFactory f2;
const struct ConstructorPropGetterImprimible c2={
  &f2,
  get0,
  "hola"
};

void main(void){
  PropiedadGetter& p=c.getPropiedad((void*)0);
  int a=p.get();
  PropiedadGetter& p2=((ConstructorPropiedadGetter*)&c2)->getPropiedad((void*)0);
  a = p2.get();
}