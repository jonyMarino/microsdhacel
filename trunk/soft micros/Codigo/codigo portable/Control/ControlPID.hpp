#ifndef _CONTROL_HPP
#define _CONTROL_HPP

#include "PE/include/PE_Types.h"

#include "OOC/lang/reflect/lib_cpp/Method.hpp"
#include "Salida/ISalida.hpp"
#include "Sensor/Sensor.hpp"
#include "Timer/MethodTimer/MethodTimer.hpp"
#include "MethodContainer/MethodContainer.hpp"
#include "Lazo/Lazo.hpp"

#pragma DATA_SEG DATA                                            
#pragma CODE_SEG CODE
#pragma CONST_SEG DEFAULT 

#define MIN_POTENCIA  0
#define MAX_POTENCIA  1000

#define MAX_VALUE_TIPO_CONTROL 1
#define MAX_VALUE_TIPO_SALIDA 2
#define MAX_INTEGRAL 9999
#define MAX_DERIVADA 600

#warning poner como parametro de sensor:
#define DELTAT 1000


#define ControlDefaultConf {			\
  10,															\
  0,															\
  1700,														\
  0,															\
  0,														  \
  /*CNTR_ONOFF*/0,											\
	/*_CAL*/0,														\
	0,															\
	0,															\
	0,															\
	1000,														\
	0 															\
}																	\

    
    
class ConfiguracionControl{
  public:
    virtual int getSetPoint()=0;
    virtual void setSetPoint(int)=0;
    virtual int getLimiteInferiorSetPoint()=0;
    virtual void setLimiteInferiorSetPoint(int val)=0;
    virtual int getLimiteSuperiorSetPoint()=0;
    virtual void setLimiteSuperiorSetPoint(int val)=0;
    virtual int getReset()=0;
    virtual void setReset(int val)=0;
    virtual int  getTipoControl()=0;
    virtual void setTipoControl(int tc)=0;
    virtual int getTipoSalida()=0;
    virtual void setTipoSalida(int val)=0;
    virtual int getHisteresis()=0;
    virtual void setHisteresis(int val)=0;
    virtual int getIntegral()=0;
    virtual void setIntegral(int val)=0;
    virtual int getDerivada()=0;
    virtual void setDerivada(int val)=0;
    virtual int getLimiteInferiorPotencia()=0;
    virtual void setLimiteInferiorPotencia(int val)=0;
    virtual int getLimiteSuperiorPotencia()=0;
    virtual void setLimiteSuperiorPotencia(int val)=0;
    virtual int getPotenciaManual()=0;
    virtual void setPotenciaManual(int val)=0;
    friend class ControlPID;
};    

class ControlPID:public Lazo{
  public:
    typedef enum{
     _CAL, 
     _REF, 
     _MAN 
    }TSalida;
    
    
    typedef enum{
      CNTR_ONOFF,
      CNTR_PID
    }TTipoControl;
    

     
    ControlPID(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracion);
    
    void addOnTipoSalidaListener(struct Method& metodo);
    /*
    ** ===================================================================
    **     Method      :  Disconect 
    **     Description :  Desactiva la salida del PID
    ** ===================================================================
    */
    void desconectar();

    /*
    ** ===================================================================
    **     Method      :  Conect 
    **     Description :  Activa la salida del PID
    ** ===================================================================
    */												
    void conectar();  
    /*
    ** ===================================================================
    **     Method      :  isConnected 
    **     Description :  Activa la salida del PID
    ** ===================================================================
    */
    bool isConectado();

    /*
    ** ===================================================================
    **     Method      :  es_pid 
    **     Description :  Determina si se esta como PID o on-off
    ** ===================================================================
    */
    bool isPID();

    /*
    ** ===================================================================
    **     Method      :  setDutyControl 
    **     Description :  Setea el duty de salida
    ** ===================================================================
    */
    void setDutyControl();
    /*
    ** ===================================================================
    **     Method      :  getDuty 
    **     Description :  Obtiene el duty de salida
    ** ===================================================================
    */
    int getDuty();
    /*
    ** ===================================================================
    **     Method      :  getSal 
    **     Description :  Obtiene un puntero a la salida
    ** ===================================================================
    */
    ISalida& getSalida();
    /*
    ** ===================================================================
    **     Method      :  getSensor 
    **     Description :  Obtiene el sensor utilizado por el control
    ** ===================================================================
    */
   // Sensor& getSensor();
    /*
    ** ===================================================================
    **     Method      :  setTipoControl 
    **     Description :  Funcion para setear el tipo de salida en on-off (salida independiente del periodo)
    ** ===================================================================
    */

    TTipoControl getTipoControl();

    void setTipoControl(TTipoControl tipoControl);

    /*
    ** ===================================================================
    **     Method      :  getModSal 
    **     Description :  MAN - REF -CAL
    ** ===================================================================
    */
    TSalida getModoSalida();

    /*
    ** ===================================================================
    **     Method      :  getModSal 
    **     Description :  MAN - REF -CAL
    ** ===================================================================
    */
    void setModoSalida(TSalida val);

    /*
    ** ===================================================================
    **     Method      :  getValControl 
    **     Description :  Obtiene el valor de control (In+Dr+Pr)
    ** ===================================================================
    */
    int getValorControl();
    /*
    ** ===================================================================
    **     Method      :  getDec 
    **     Description :  Obtiene los decimales del sensor usado
    ** ===================================================================
    */
    uchar getDecimales();
    /*
    ** ===================================================================
    **     Method      :  getConfSP 
    **     Description :  Set Point Configuracion
    ** ===================================================================
    */
    int getLimiteInferiorSetPoint();

    int getLimiteSuperiorSetPoint();


    int getConfiguracionSetPoint();


    void setConfiguracionSetPoint(int valor);
    /*
    ** ===================================================================
    **     Method      :  getOP_SP 
    **     Description :  Obtiene el valor del set point que se utiliza 
    **     para las  OPeraciones de calculo del control
    ** ===================================================================
    */
    int getSetPointOperativo();

    /*
    ** ===================================================================
    **     Method      :  set_LimInf_SP 
    **     Description :  Lim Inf y Sup del SP
    ** ===================================================================
    */
    void setLimiteInferiorSetPoint(int val);

    void setLimiteSuperiorSetPoint(int val);
    
    int getLimiteInferiorSensor();

    int getLimiteSuperiorSensor();

    int getLimiteInferiorDelLimiteSuperiorSetPoint();

    int getLimiteSuperiorDelLimiteSuperiorSetPoint();
    /*
    ** ===================================================================
    **     Method      :  get_Reset 
    **     Description :  
    ** ===================================================================
    */

    int getReset();

    void setReset(int val);

    /*
    ** ===================================================================
    **     Method      :  get_TipoControl 
    **     Description :  Tipo de control
    ** ===================================================================
    */
    int  getConfiguracionTipoControl();

    void setConfiguracionTipoControl(int tc);

    /*
    ** ===================================================================
    **     Method      :  get_SalControl 
    **     Description :  Tipo de salida de Control
    ** ===================================================================
    */
    int getTipoSalida();

    void setTipoSalida(int val);

    /*
    ** ===================================================================
    **     Method      :  get_H_Control 
    **     Description :  Histeresis
    ** ===================================================================
    */
    int getHisteresis();
    void setHisteresis(int val);

    /*
    ** ===================================================================
    **     Method      :  get_integral 
    **     Description :  Constante de integracion
    ** ===================================================================
    */
    int getIntegral();

    void setIntegral(int val);

    int getLimiteSuperiorIntegral();

    /*
    ** ===================================================================
    **     Method      :  get_derivada 
    **     Description :  Constante de derivacion
    ** ===================================================================
    */
    int getDerivada();

    void setDerivada(int val);

    //MAX_DERIVADA:
    //int getLimiteSuperiorDerivada();
    /*
    ** ===================================================================
    **     Method      :  get_PotenciaInf 
    **     Description :  Limite Inferior de Potencia de Salida
    ** ===================================================================
    */
    int getLimiteInferiorPotencia();

    void setLimiteInferiorPotencia(int val);

    int getLimiteInferiorDelLimiteInferiorPotencia();
    int getLimiteSuperiorDelLimiteInferiorPotencia();

    /*
    ** ===================================================================
    **     Method      :  get_PotenciaSup 
    **     Description :  Limite Superior de Potencia de Salida
    ** ===================================================================
    */
    int getLimiteSuperiorPotencia();

    void setLimiteSuperiorPotencia(int val);

    int getLimiteInferiorDelLimiteSuperiorPotencia();
    int getLimiteSuperiorDelLimiteSuperiorPotencia();

    /*
    ** ===================================================================
    **     Method      :  get_PotenciaManual 
    **     Description :  Valor de la Potencia de Salida en Manual
    ** ===================================================================
    */
    int getPotenciaManual();
    void setPotenciaManual(int val);
    int getLimiteInferiorPotenciaManual();
    int getLimiteSuperiorPotenciaManual();
       
    inline const ConfiguracionControl& getConfiguracion(){return configuracion;}
  protected:
    virtual void onNuevoValorSensor();
  private:
    const ConfiguracionControl& configuracion;
    ISalida& salida;
    //TTipoControl tipoControl;
    int valorControl;
    TSalida modoSalida;
    int valorAnterior;
    long bufferDerivada;
    long sumatoriaIntegral;
  //  struct MethodTimer * timerDesconexion;
    MethodContainer * onTipoSalidaChange;
    
    
    void actualizarValorControl();
};

 
#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT


#endif

