#ifndef _AUTO_SINTONIA_HPP
#define _AUTO_SINTONIA_HPP

#include "ControlPID.hpp"
#include "LazoControl.hpp"
#include "SalidaBanda.hpp"
#include "ValorControlProporcional.hpp"
#include "Timer/FlagTimer/FlagTimer.hpp"
#include "MethodContainer.hpp"

#define MODO_CONTROL 7                                       
class AutoSintonia:public LazoControl{
  public:
    //Empieza el proceso de autosintonia
    AutoSintonia(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracion);
    AutoSintonia(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracion,MethodContainer& listenersOnChange);
    bool isDetenido(); // indica si la autusintonia esta en el estado 5 o 6 (termino o error respectivamente)
    int getNumeroEstado();
    inline const ConfiguracionControl& getConfiguracion(){return confControl;}
    int getConfiguracionSetPoint();
    void setConfiguracionSetPoint(int val);

    int getLimiteInferiorSetPoint();
    int getLimiteSuperiorSetPoint();
    void setLimiteInferiorSetPoint(int val);
    void setLimiteSuperiorSetPoint(int val);
    int getLimiteInferiorPotencia();
    void setLimiteInferiorPotencia(int val);
    int getLimiteSuperiorPotencia();
    void setLimiteSuperiorPotencia(int val);
    uchar getDecimales();

    void addOnChangeListener(const struct Method& metodo);
    void deleteOnChangeListener(const struct Method& metodo);
    

    
  protected:
    void onNuevoValorSensor();
  private:
    void init(const ConfiguracionControl& configuracion);
    
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
    MethodContainer onChange;
};

#endif