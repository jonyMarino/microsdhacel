#include "VistaSetContrasenia.hpp"

const struct ConstructorPropNumLFPF VistaSetContrasenia::cPropiedadSetContrasenia={
  &propNumLFPFFactory,VistaSetContrasenia::getCodigo,"SetC",VistaSetContrasenia::setCodigo,0,9999,0
};


int VistaSetContrasenia::getCodigo(void*_self){
  VistaSetContrasenia * self = (VistaSetContrasenia *)_self; 
  return self->memoria->getWord((uint*)self->pCodigo);
}

void VistaSetContrasenia::setCodigo(void*_self,int codigo){
  VistaSetContrasenia * self = (VistaSetContrasenia *)_self;
  self->memoria->setWord((uint*)self->pCodigo,codigo);
}


static const struct ConstructorBoxPropiedad VistaSetContrasenia::cBoxSetContrasenia={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&VistaSetContrasenia::cPropiedadSetContrasenia  
};
        