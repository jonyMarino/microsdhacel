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
  
  //avisa que va a ser cambiado el tipo de control.
  listeners.executeMethods();
  delete lazo;
  modoActual = modo;
  crearModo(sensor,salida,*confControl);
  
  if(onControlChange){
    LinkedList::LinkedListIterator it;
    onControlChange->linkedListIterator(&it); 
    
    while(it.hasNext()){    
      const struct Method* mo= (const struct Method*)it.next();
      (*(void(*)(void*,void*))mo->pmethod)(mo->obj,this);
    }
  }
   
}



void CoordinadorControladorSintonizador::crearModo(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracionControl){  

  switch(modoActual){
    case CONTROL:
     lazo = new((byte*)&poolModo) ControlPIDOptMem(sensor,salida,configuracionControl);        
    break;
    case AUTOSINTONIA:
    default:
      lazo = new((byte*)&poolModo) SintonizadorOptMem(sensor,salida,configuracionControl);  
    break;
  }

}
                             

void CoordinadorControladorSintonizador::addOnNuevoModoControlListener(const struct Method* metodo){
    listeners.add((void*)metodo);
}
void CoordinadorControladorSintonizador::deleteOnNuevoModoControlListener(const struct Method * metodo){
    listeners.moveOut((void*)metodo);
}

/*
** ===================================================================
**     Method      :  ControlPID::AddOnControlChange 
**     Description :  Agrega evento de cambio del control
** ===================================================================
*/

void CoordinadorControladorSintonizador::addOnControlListener(struct Method& metodo){
  if(!onControlChange)
    onControlChange=new MethodContainer(); 
   
  onControlChange->add((void*)&metodo);
}




