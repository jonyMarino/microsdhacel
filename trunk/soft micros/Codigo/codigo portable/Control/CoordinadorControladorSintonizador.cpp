#include "CoordinadorControladorSintonizador.hpp"

CoordinadorControladorSintonizador::SintonizadorOptMem::SintonizadorOptMem(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracion,MethodContainer& listenersOnChange):AutoSintonia(sensor,salida,configuracion,listenersOnChange){
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
  crearModo(sensor,salida,configuracionControl);
}


eModoControl  CoordinadorControladorSintonizador::getModo(){
  return modoActual;
}

int CoordinadorControladorSintonizador::getPasoAutosintonia(){
  if(modoActual!=AUTOSINTONIA)
    return -1;
  return ((AutoSintonia*)&poolModo.autoSintonia.sintonizador)->getNumeroEstado();
}

bool CoordinadorControladorSintonizador::getEstadoAutosintonia(){
  if(modoActual!=AUTOSINTONIA)
    return -1;
  return ((AutoSintonia*)&poolModo.autoSintonia.sintonizador)->isDetenido();
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

  
 /* if(onControlChange){
    LinkedList::LinkedListIterator it;
    onControlChange->linkedListIterator(&it); 
    
    onControlChange->executeMethods();
  }*/
   
  //avisa que va fue cambiado el tipo de control.
  onControlChange.executeMethods();   

}



void CoordinadorControladorSintonizador::crearModo(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracionControl){  

  switch(modoActual){
    case CONTROL:
     new((byte*)&poolModo) ControlPIDOptMem(sensor,salida,configuracionControl);        
    break;
    case AUTOSINTONIA:
    default:
      new((byte*)&poolModo.autoSintonia.sintonizador) SintonizadorOptMem(sensor,salida,configuracionControl,onControlChange);  
      AutoSintonia * autoTun = (AutoSintonia*)&poolModo.autoSintonia.sintonizador;
      poolModo.autoSintonia.onChangeAutoTun.pmethod = onChangeAutoTun;
      poolModo.autoSintonia.onChangeAutoTun.obj = this;
      autoTun->addOnChangeListener(poolModo.autoSintonia.onChangeAutoTun);
    break;
  }

}
                             

void CoordinadorControladorSintonizador::addOnControlListener(const struct Method& metodo){
    onControlChange.add((void*)&metodo);
}
void CoordinadorControladorSintonizador::deleteOnControlListener(const struct Method& metodo){
    onControlChange.moveOut((void*)&metodo);
}

static void CoordinadorControladorSintonizador::onChangeAutoTun(void *_self){
  CoordinadorControladorSintonizador * self = (CoordinadorControladorSintonizador *)_self;
  AutoSintonia * autoTun = (AutoSintonia*)&self->poolModo.autoSintonia.sintonizador;

  if(autoTun->getNumeroEstado()==7){ //termino la autosintonia normamente?
    self->setModo(CONTROL);  
  }
}






