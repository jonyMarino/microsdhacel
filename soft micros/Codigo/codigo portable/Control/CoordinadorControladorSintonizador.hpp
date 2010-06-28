#ifndef _COORDINADOR_CONTROL_AUTOSINTONIA_HPP
#define _COORDINADOR_CONTROL_AUTOSINTONIA_HPP

#include "ControlPID.hpp"
#include "AutoSintonia.hpp"

 
typedef enum{
  CONTROL,
  AUTOSINTONIA
}eModoControl;

class CoordinadorControladorSintonizador{
  public:
    CoordinadorControladorSintonizador(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracionControl);
    eModoControl getModo();
    void setModo(eModoControl); //valores posibles: CONTROL,AUTOSINTONIA
    ControlPID* getControl();
    int getPasoAutosintonia();
    void addOnNuevoModoControlListener(const struct Method* metodo);
    void deleteOnNuevoModoControlListener(const struct Method * metodo);
 
  //private:
    
    class SintonizadorOptMem:public AutoSintonia{
      public:
        SintonizadorOptMem(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracion);
        void * operator new(size_t size,byte * dir);

        void operator delete(void *ptr);
    };
    
    class ControlPIDOptMem:public ControlPID{
      public:
        ControlPIDOptMem(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracion);
        void * operator new(size_t size,byte * dir);
        void operator delete(void *ptr);
    };
    
    union{
      byte sintonizador[sizeof(CoordinadorControladorSintonizador::SintonizadorOptMem)];
      byte control[sizeof(CoordinadorControladorSintonizador::ControlPIDOptMem)];    
    }poolModo;
    
    void crearModo(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracionControl);
    eModoControl modoActual;
    MethodContainer listeners;
};

#endif
