#ifndef _REGISTRADOR_SD_HPP
#define _REGISTRADOR_SD_HPP

#include "Registrador/Registrador.hpp"
#include "SD/Fat/SDFat.hpp"
#include "Aparatos/System.hpp"

class RegistradorSD: public Registrador{
  public:
    RegistradorSD(const struct Array& serializables,ConfiguracionRegistrador& configuracion,SDFat& sd);
  protected:
    virtual void registrar();
    SDFat& sd;
  private:  
    static void cambioFecha(void * self);
    static byte nombreArchivo[16];
};

#endif