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
    int getPasoAutosintonia();
    bool getEstadoAutosintonia();
    void addOnControlListener(const struct Method& metodo);
    void deleteOnControlListener(const struct Method& metodo);
  
  inline ControlPID* getControl(){
    return (ControlPID *)&(poolModo);
  }
  inline AutoSintonia* getAutoSintonia(){
    return (AutoSintonia *)&(poolModo);
  }
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
      byte control[sizeof(CoordinadorControladorSintonizador::ControlPIDOptMem)];    
      byte sintonizador[sizeof(CoordinadorControladorSintonizador::SintonizadorOptMem)];
    }poolModo;
    
    void crearModo(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracionControl);
    eModoControl modoActual;
    MethodContainer onControlChange;
    Lazo * lazo;
};

#endif
