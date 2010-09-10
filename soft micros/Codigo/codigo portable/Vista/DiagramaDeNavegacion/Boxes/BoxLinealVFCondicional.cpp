#include "BoxLinealVFCondicional.hpp"
#include "BoxLinealVF.hpp"

const struct BoxLinealVFCondicionalFactory boxLinealVFCondicionalFactory;


BoxLinealVFCondicional::BoxLinealVFCondicional(struct ConstructorBoxLinealVFCondicional * _constructor,void*_obj,uchar _numObjeto):BoxLinealVF((struct ConstructorBoxLinealVF * )_constructor),constructor(_constructor),obj(_obj),numObj(_numObjeto){
 if((*(constructor->getNroProp))(obj)<3){
  
  setNumProp((*(constructor->getNroProp))(obj));
  mostrarPropiedad(obj,numObj);
 }
}



BoxLinealVFCondicional::~BoxLinealVFCondicional(){

}

