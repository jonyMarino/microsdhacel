#ifndef _LAZO_CONTROL_HPP
#define _LAZO_CONTROL_HPP

#include "Lazo.hpp"
#include "ValorControl.hpp"
#include "AdaptadorSalida.hpp"

class LazoControl: public Lazo{
  public:
    LazoControl(ValorControl& valorControl,AdaptadorSalida& adaptadorSalida);
    LazoControl(Sensor&sensor);
    AdaptadorSalida& getAdaptadorSalida();
    virtual ISalida& getSalida(); 
  protected:
    virtual void onNuevoValorSensor();  
    ValorControl * valorControl; 
    AdaptadorSalida * adaptadorSalida;

};


#endif