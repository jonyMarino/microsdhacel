#include "BoxLinealVFCondicional.hpp"

const struct BoxLinealVFCondicionalFactory boxLinealVFCondicionalFactory;


BoxLinealVFCondicional::BoxLinealVFCondicional(struct ConstructorBoxLinealVFCondicional * constructor,void*obj,uchar numObjeto):BoxLinealVF((struct ConstructorBoxLinealVF * )constructor){
  setNumProp((*(constructor->getNroProp))(obj));
  mostrarPropiedad(obj,numObjeto);
}


BoxLinealVFCondicional::~BoxLinealVFCondicional(){

}