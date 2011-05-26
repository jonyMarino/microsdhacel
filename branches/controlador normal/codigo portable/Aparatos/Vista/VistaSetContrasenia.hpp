#ifndef _VISTA_SET_CONTRASENIA_HPP
#define _VISTA_SET_CONTRASENIA_HPP

#include "BoxPropiedad.hpp"
#include "PropNumLFPF.hpp"
#include "Memoria/ManejadorMemoria.hpp"

class VistaSetContrasenia{
  public:
    const int * pCodigo;
    const ManejadorMemoria * memoria;
    static const struct ConstructorBoxPropiedad cBoxSetContrasenia;  
    static const struct ConstructorPropNumLFPF cPropiedadSetContrasenia;
    static int getCodigo(void*self);
    static void setCodigo(void*self,int codigo); 
};


extern const struct ConstructorPropNumLFPF cPropiedadSetContrasenia;

#endif
