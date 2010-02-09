#include "BoxLinealCondicional.hpp"

const struct BoxLinealCondicionalFactory boxLinealCondicionalFactory;


BoxLinealCondicional::BoxLinealCondicional(struct ConstructorBoxLinealCondicional * constructor,void*obj,uchar numObjeto):BoxLineal((struct ConstructorBoxLineal * )constructor){
  setNumProp((*(constructor->getNroProp))(obj));
  mostrarPropiedad(obj,numObjeto);
}


BoxLinealCondicional::~BoxLinealCondicional(){

}