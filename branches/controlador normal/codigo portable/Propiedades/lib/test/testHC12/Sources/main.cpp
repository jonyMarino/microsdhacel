#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
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

};

int get1(void*a){
  return 1;
}    

//const struct B
int get0(void*a){
  return 0;
}

const struct PropiedadGetterFactory f;
const struct ConstructorPropiedadGetter c={
  &f,
  get0
}; 

const struct PropGetterVisualFactory f2;
const struct ConstructorPropGetterVisual c2={
  &f2,
  get1,
  "hola"
};

void main(void) {
  /* put your own code here */
  const char* str;
  PropiedadGetter& p=c.getPropiedad((void*)0);
  int a=p.getVal();
  PropiedadGetter& p2tmp=((ConstructorPropiedadGetter*)&c2)->getPropiedad((void*)0);
  PropGetterVisual& p2 =  *(PropGetterVisual*)&p2tmp;
  a = p2.getVal();  
  str=p2.getDescripcion();

	EnableInterrupts;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}