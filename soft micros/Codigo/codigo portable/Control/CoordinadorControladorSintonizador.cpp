#include "CoordinadorControladorSintonizador.hpp"

CoordinadorControladorSintonizador::SintonizadorOptMem::SintonizadorOptMem(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracion):AutoSintonia(sensor,salida,configuracion){
}

void * CoordinadorControladorSintonizador::SintonizadorOptMem::operator new(size_t size,byte * dir){
  return dir;  
}

void CoordinadorControladorSintonizador::SintonizadorOptMem::operator delete(void *ptr){
  return;  
}

CoordinadorControladorSintonizador::ControlPIDOptMem::ControlPIDOptMem(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracion):ControlPID(sensor,salida,configuracion){
}

void * CoordinadorControladorSintonizador::ControlPIDOptMem::operator new(size_t size,byte * dir){
  return dir;  
}

void CoordinadorControladorSintonizador::ControlPIDOptMem::operator delete(void *ptr){
  return;  
}

CoordinadorControladorSintonizador::CoordinadorControladorSintonizador( Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracionControl):modoActual(CONTROL){
  onControlChange=NULL;
  crearModo(sensor,salida,configuracionControl);
}


eModoControl  CoordinadorControladorSintonizador::getModo(){
  return modoActual;
}

int CoordinadorControladorSintonizador::getPasoAutosintonia(){
  if(modoActual!=AUTOSINTONIA)
    return -1;
  return ((AutoSintonia*)&poolModo)->getNumeroEstado();
}

bool CoordinadorControladorSintonizador::getEstadoAutosintonia(){
  if(modoActual!=AUTOSINTONIA)
    return -1;
  return ((AutoSintonia*)&poolModo)->isDetenido();
}

void CoordinadorControladorSintonizador::setModo(eModoControl modo){
  if(modo>1)
    return;
 
  lazo = ((Lazo*)&poolModo);
  
  ISalida &salida = (ISalida&)lazo->getSalida();
  Sensor  &sensor = (Sensor&)lazo->getSensor();
  const ConfiguracionControl* confControl = &((modoActual==CONTROL)?((ControlPID*)lazo)->getConfiguracion():((AutoSintonia*)lazo)->getConfiguracion());
  

  delete lazo;
  modoActual = modo;
  crearModo(sensor,salida,*confControl);
  //avisa que va fue cambiado el tipo de control.
  listeners.executeMethods();   
}



void CoordinadorControladorSintonizador::crearModo(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracionControl){  

  switch(modoActual){
    case CONTROL:
     new((byte*)&poolModo) ControlPIDOptMem(sensor,salida,configuracionControl);        
    break;
    case AUTOSINTONIA:
    default:
      new((byte*)&poolModo) SintonizadorOptMem(sensor,salida,configuracionControl);  
    break;
  }

}
                             

void CoordinadorControladorSintonizador::addOnControlListener(const struct Method& metodo){
    listeners.add((void*)&metodo);
}
void CoordinadorControladorSintonizador::deleteOnControlListener(const struct Method& metodo){
    listeners.moveOut((void*)&metodo);
}






