#ifndef _LAZO_CONTROL_HPP
#define _LAZO_CONTROL_HPP

#include "Lazo.hpp"
#include "ValorControl.hpp"
#include "AdaptadorSalida.hpp"

class LazoControl: public Lazo{
  public:
    LazoControl(ValorControl& valorControl,AdaptadorSalida& adaptadorSalida);
    AdaptadorSalida& getAdaptadorSalida();
  protected:
    virtual void onNuevoValorSensor();
    virtual ISalida& getSalida(); 
    ValorControl * valorControl; 
    AdaptadorSalida * adaptadorSalida;

};


#endif