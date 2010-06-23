#ifndef _AUTO_SINTONIA_HPP
#define _AUTO_SINTONIA_HPP

#include "ControlPID.hpp"
#include "LazoControl.hpp"
#include "SalidaBanda.hpp"
#include "ValorControlProporcional.hpp"
#include "Timer/FlagTimer/FlagTimer.hpp"

class AutoSintonia:public LazoControl{
  public:
    //Empieza el proceso de autosintonia
    AutoSintonia(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracion);
    void detener(); //detiene el proceso de autosintonia sin realizar cambios
    int getNumeroEstado();
    inline const ConfiguracionControl& getConfiguracion(){return confControl;}

  protected:
    void onNuevoValorSensor();
  private:
    class ConfValControl:public ConfiguracionValorControl{
      public:
        //ConfValControl(int setPointControl);
        virtual int getValorControlador();
      private:
        int setPointControl;
        friend class AutoSintonia;  
    }confValControl;
    class ConfAdaptSalida:public AdaptadorSalidaConfiguracion{
      public:
        virtual int getHisteresis();
        virtual TipoSalida getTipoSalida();      
    }confAdaptSalida;
    SalidaBanda adaptSalida;
    ValorControlProporcional valControl;
    const ConfiguracionControl&confControl;
    byte paso;
    int valorPrevio,maximo,minimo;
    FlagTimer contadorTiempoAbierto;
};

#endif