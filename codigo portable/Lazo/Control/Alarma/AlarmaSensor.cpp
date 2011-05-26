#include "AlarmaSensor.hpp"

//static void factoryAdaptSalida( TAdaptador adaptSalida);

/**/
void * operator new(size_t size,byte * dir){
  return dir;  
}


AlarmaSensor::AlarmaSensor(ConfiguracionAlarmaSensor& _configuracion,
                           ConfiguracionValorControl&  confValorControl,
                           Sensor&sensor,
                           AdaptadorSalidaConfiguracion& confAdaptadorSalida,
                           ISalida& salida):LazoControl(sensor),configuracion(_configuracion),valorControl(confValorControl,sensor),salidaConPolaridad(salida){
  
  crearAdaptadorSalida( getAdaptadorSalida() );
  LazoControl::valorControl = &valorControl;
  LazoControl::adaptadorSalida = (AdaptadorSalida*)&adaptadorSalida;  
}

/**/
void AlarmaSensor::crearAdaptadorSalida(TipoAdaptadorSalida adaptSalida){
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


/**/
/*void * LazoControlAlSen_destructor(void * _self){
  struct LazoControlAlSen * self = _self;
  //delete(self->adaptadorSalida); destruirAdaptadorSalida()

}  */

TipoAdaptadorSalida  AlarmaSensor::getAdaptadorSalida(){
  return configuracion.getAdaptadorSalida();
}

void AlarmaSensor::setAdaptadorSalida(TipoAdaptadorSalida adaptSalida){
  configuracion.setAdaptadorSalida(adaptSalida);
  crearAdaptadorSalida(adaptSalida);    
}
