#include "BoxLinealVFCondicional.hpp"
#include "BoxLinealVF.hpp"

const struct BoxLinealVFCondicionalFactory boxLinealVFCondicionalFactory;


BoxLinealVFCondicional::BoxLinealVFCondicional(struct ConstructorBoxLinealVFCondicional * _constructor,void*_obj,uchar _numObjeto):BoxLinealVF((struct ConstructorBoxLinealVF * )_constructor),constructor(_constructor),obj(_obj),numObj(_numObjeto){
 if((constructor->super).propiedades[(*(constructor->getNroProp))(obj)]){    //la propiedad es distinta de NULL??
  
  setNumProp((*(constructor->getNroProp))(obj));
  mostrarPropiedad(obj,numObj);
 }
}



BoxLinealVFCondicional::~BoxLinealVFCondicional(){

}

