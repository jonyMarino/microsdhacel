#ifndef _SENSORTERMOPT100_HPP
#define _SENSORTERMOPT100_HPP


#include "Sensor/Sensor.hpp"
#include "FshTypeSizes.h"
#include "IAdc.hpp"
#include "Adc.hpp"
#include "Sensores.h"
#include "Memoria/ManejadorMemoria.hpp" 


#define STPT_DEF_CONF { \
  SENSOR_JA,						\
  0,										\
  0,										\
  0,										\
  1000,									\
  0,										\
  0,										\
  0,										\
  0  									  \
}



class SensorTermoPT100 : public Sensor {
  public:
    typedef struct {
        unsigned int sensor;

        unsigned int decimales;
        
        unsigned int filtro;

        int offset;

        int ganancia;

        int ceroTermopar;

        int gananciaTermopar;

        int ceroPT100;

        int gananciaPT100;

    }TConfSensor;
    
   
    
  SensorTermoPT100(Adc & _adc_, const TConfSensor & _conf, struct ManejadorMemoria & _manejadorMemoria);
  
  static void setConfiguracionTemperaturaAmbiente(int * ta);
  
  unsigned char getDecimales();
  
  void setDecimales (int val);

  Sensor::TSensorState getEstado();

  int getLimiteInferior();

  int getLimiteSuperior();

  int getVal();

  /**
   * reesmplazo de SenTPT_Handler
   */
  bool checkADC();

  void print(OutputStream& os);

  unsigned int getSensor();

  void setSensor(unsigned int);

  fbyte getLimSupSensor();

  unsigned char getFiltro();

  void setFiltro(unsigned char filtro);

  int getOffset();

  void setOffset(int);

  int getGanancia();

  void setGanancia(int);

  int getCeroTermopar();

  void setCeroTermopar(int);

  int getGananciaTermopar();

  void setGananciaTermopar(int);

  int getCeroPT100();

  void setCeroPT100(int);

  int getGananciaPT100();

  void setGananciaPT100(int);

  int getAjusteTemperaturaAmbiente();

  void setAjusteTemperaturaAmbiente(int);

  int getTiempoMuestreo();
  
  void addOnNuevoValorListener(const struct Method* metodo);
  
  private:
    Adc & _adc;
    
    IAdc & adc;
    
    ManejadorMemoria &manejadorMemoria;

    const TConfSensor& configuracion;

    int valor;

    long bufferFiltro;

    Sensor::TSensorState estado;
    
    static int * compensacionTempAmb;
    
    char onSensorChange(fbyte);
    
    void procesar();
};
#endif
