#include "AlarmaControl.hpp"


void * operator new(size_t size,byte * dir){
  return dir;  
}


AlarmaControl::AlarmaControl(ConfiguracionAlarmaControl& _configuracion,
                           ConfiguracionValorControl&  confValorControl,
                           AdaptadorSalidaConfiguracion& confAdaptadorSalida,
                           ControlPID& _control,
                           ISalida&salida):LazoControl(_control.getSensor()),getterSP(_control),configuracion(_configuracion),salidaConPolaridad(salida){
  
  crearAdaptadorSalida( getAdaptadorSalida() );
  crearTipoControl( getTipoControl() );
  LazoControl::valorControl = (ValorControl*)&valorControl;
  LazoControl::adaptadorSalida = (AdaptadorSalida*)&adaptadorSalida;  
}

/**/
void AlarmaControl::crearAdaptadorSalida(TipoAdaptadorSalida adaptSalida){
  switch(adaptSalida){
    case SALIDA_RETENIDA:
        salidaConPolaridad.setPolaridad(FALSE);
        LazoControl::adaptadorSalida =new((byte*)&adaptadorSalida) SalidaRetenida(salidaConPolaridad, ((AdaptadorSalida*)&adaptadorSalida)->getConfiguracion());        
        break;
    case SALIDA_DEFECTO_RETENIDA:
        salidaConPolaridad.setPolaridad(TRUE);
        LazoControl::adaptadorSalida =new((byte*)&adaptadorSalida) SalidaRetenidaBajo(salidaConPolaridad, ((AdaptadorSalida*)&adaptadorSalida)->getConfiguracion()); 
        break;
    case SALIDA_DEFECTO_BLOQUEADA:
        salidaConPolaridad.setPolaridad(FALSE);
        LazoControl::adaptadorSalida =new((byte*)&adaptadorSalida) SalidaBloqueada(salidaConPolaridad, ((AdaptadorSalida*)&adaptadorSalida)->getConfiguracion()); 
        break;
    case SALIDA_DEFECTO:         
        salidaConPolaridad.setPolaridad(TRUE);       
        LazoControl::adaptadorSalida =new((byte*)&adaptadorSalida) SalidaBanda(salidaConPolaridad, ((AdaptadorSalida*)&adaptadorSalida)->getConfiguracion()); 
      break;
    case SALIDA_EXCESO:
    default:  //error
        salidaConPolaridad.setPolaridad(FALSE);
        LazoControl::adaptadorSalida =new((byte*)&adaptadorSalida) SalidaBanda(salidaConPolaridad, ((AdaptadorSalida*)&adaptadorSalida)->getConfiguracion());
      break;      
  }
}

TipoAdaptadorSalida  AlarmaControl::getAdaptadorSalida(){
  return configuracion.getAdaptadorSalida();
}

void AlarmaControl::setAdaptadorSalida(TipoAdaptadorSalida adaptSalida){
  configuracion.setAdaptadorSalida(adaptSalida);
  crearAdaptadorSalida(adaptSalida);    
}

void AlarmaControl::crearTipoControl(TipoControl tipoControl){
  switch(tipoControl){             
    case CONTROL_PROPORCIONAL:               
        new((byte*)&adaptadorSalida)ValorControlProporcionalInvertido( ((ValorControl*)&tipoControl)->getConfiguracion(),getterSP.control.getSensor());        
      break;
    case CONTROL_RELATIVO: 
        new((byte*)&adaptadorSalida)ValorControlRelativo( ((ValorControl*)&tipoControl)->getConfiguracion(),getterSP.control.getSensor(),getterSP);        
      break;
    case CONTROL_BANDA: 
    default:  //error 
        new((byte*)&adaptadorSalida)ValorControlBanda( ((ValorControl*)&tipoControl)->getConfiguracion(),getterSP.control.getSensor(),getterSP);        
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
  crearTipoControl(tipo);    
}
//GetterSP
AlarmaControl::GetterSP::GetterSP(ControlPID& _control):control(_control){
}

int AlarmaControl::GetterSP::getVal(){
  return control.getConfiguracionSetPoint();
}


void AlarmaControl::GetterSP::print(OutputStream&os){
}

