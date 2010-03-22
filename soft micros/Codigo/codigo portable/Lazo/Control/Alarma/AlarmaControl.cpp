#include "AlarmaControl.hpp"


void * operator new(size_t size,byte * dir){
  return dir;  
}


AlarmaControl::AlarmaControl(ConfiguracionAlarmaControl& _configuracion,
                           ConfiguracionValorControl&  confValorControl,
                           AdaptadorSalidaConfiguracion& confAdaptadorSalida,
                           ControlPID& _control,
                           ISalida&salida):LazoControl(_control.getSensor()),getterSP(_control),configuracion(_configuracion),salidaConPolaridad(salida),_salida(salida){
  
  crearAdaptadorSalida( getAdaptadorSalidaAlarm() , confAdaptadorSalida);
  crearTipoControl( getTipoControl() , confValorControl);
  LazoControl::valorControl = (ValorControl*)&valorControlPull;
  LazoControl::adaptadorSalida = (AdaptadorSalida*)&adaptadorSalidaPull;  
}

/**/
void AlarmaControl::crearAdaptadorSalida(TipoAdaptadorSalida adaptSalida,AdaptadorSalidaConfiguracion& confAdaptadorSalida){
  switch(adaptSalida){
    case SALIDA_RETENIDA:
        salidaConPolaridad.setPolaridad(TRUE);
        LazoControl::adaptadorSalida =new((byte*)&adaptadorSalidaPull) SalidaRetenida(salidaConPolaridad, confAdaptadorSalida);        
        break;
    case SALIDA_DEFECTO_RETENIDA:
        salidaConPolaridad.setPolaridad(FALSE);
        LazoControl::adaptadorSalida =new((byte*)&adaptadorSalidaPull) SalidaRetenidaBajo(salidaConPolaridad, confAdaptadorSalida); 
        break;
    case SALIDA_DEFECTO_BLOQUEADA:
        salidaConPolaridad.setPolaridad(TRUE);
        LazoControl::adaptadorSalida =new((byte*)&adaptadorSalidaPull) SalidaBloqueada(salidaConPolaridad, confAdaptadorSalida); 
        break;
    case SALIDA_DEFECTO:         
        salidaConPolaridad.setPolaridad(FALSE);       
        LazoControl::adaptadorSalida =new((byte*)&adaptadorSalidaPull) SalidaBanda(salidaConPolaridad, confAdaptadorSalida); 
      break;
    case SALIDA_EXCESO:
    default:  //error
        salidaConPolaridad.setPolaridad(TRUE);
        LazoControl::adaptadorSalida =new((byte*)&adaptadorSalidaPull) SalidaBanda(salidaConPolaridad, confAdaptadorSalida);
      break;      
  }
}

TipoAdaptadorSalida  AlarmaControl::getAdaptadorSalidaAlarm(){
  return configuracion.getAdaptadorSalidaAlarm();
}

void AlarmaControl::setAdaptadorSalidaAlarm(TipoAdaptadorSalida adaptSalida){
  configuracion.setAdaptadorSalidaAlarm(adaptSalida);
  crearAdaptadorSalida(adaptSalida,((AdaptadorSalida*)&adaptadorSalidaPull)->getConfiguracion());    
}

void AlarmaControl::crearTipoControl(TipoControl tipoControl,ConfiguracionValorControl&  confValorControl){
  switch(tipoControl){             
    case CONTROL_PROPORCIONAL:               
        LazoControl::valorControl=new((byte*)&valorControlPull)ValorControlProporcionalInvertido( confValorControl,getterSP.control.getSensor());        
      break;
    case CONTROL_RELATIVO: 
        LazoControl::valorControl=new((byte*)&valorControlPull)ValorControlRelativo( confValorControl,getterSP.control.getSensor(),getterSP);        
         //ValorControlRelativo valorControl( confValorControl,getterSP.control.getSensor(),getterSP);
      break;
    case CONTROL_BANDA: 
    default:  //error 
        LazoControl::valorControl=new((byte*)&valorControlPull)ValorControlBanda(confValorControl,getterSP.control.getSensor(),getterSP);        
      break;      
  } 
}

/**/
TipoControl  AlarmaControl::getTipoControl(){
    return configuracion.getTipoControl();
}
/**/
void AlarmaControl::setTipoControl(TipoControl tipo){
  configuracion.setTipoControl(tipo);

  //delete &tipoControl;
  crearTipoControl(tipo,((ValorControl*)&valorControlPull)->getConfiguracion());    
}
//GetterSP
AlarmaControl::GetterSP::GetterSP(ControlPID& _control):control(_control){
}

int AlarmaControl::GetterSP::getVal(){
  return control.getConfiguracionSetPoint();
}


void AlarmaControl::GetterSP::print(OutputStream&os){
}

ISalida& AlarmaControl::getSalida(){
  return _salida;
 //return salidaConPolaridad;
}


