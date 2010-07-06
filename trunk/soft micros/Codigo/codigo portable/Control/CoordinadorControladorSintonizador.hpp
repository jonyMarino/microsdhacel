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
    void addOnControlListener(struct Method& metodo);
    void addOnNuevoModoControlListener(const struct Method* metodo);
    void deleteOnNuevoModoControlListener(const struct Method * metodo);
  
  inline ControlPID* getControl(){
    //return (ControlPID *)&(poolModo);
      return (ControlPID *)lazo;
  }
  inline AutoSintonia* getAutoSintonia(){
    //return (AutoSintonia *)&(poolModo);
    return (AutoSintonia *)lazo;
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
    MethodContainer listeners;
    MethodContainer * onControlChange;
    Lazo * lazo;
};

#endif
