 #ifndef _PROM_BKP_HPP
 #define _PROM_BKP_HPP 
 
#include "ManejadorMemoria.hpp"
#include "LinkedList.hpp" 





 class PromBkp: public ManejadorMemoria{
  public:
    PromBkp();
    virtual byte borrarProm(void*);
    virtual void * grabarProm();
    bool listoParaGrabarOBorrar();
    bool grabacionOBorradoEnEspera();
    byte borrarPagina(void * address);
    void deshabilitar();
    void habilitar();
    void demorarGrabado(word time);
    byte grabarOBorrar();
    static bool estaEnPagina(void * address,void* pagina); //funcion para checkeo
  protected:
    void setAGrabar(bool valor);
    bool getAGrabar();
  private:
    bool aGrabar;									 //indica si hay para grabar en espera
    Timer * timer;
    word disableCont;  
    LinkedList listaDireccionesABorrar;
    //LinkedList * preBorrarListenerContainer;
    //LinkedList * postBorrarListenerContainer;
    //LinkedList * postEscribirListenerContainer;  
 };
 

/* 
byte PromBkp_addPreBorrarListener(void*,void * promListener);
byte PromBkp_deletePreBorrarListener(void*,void * promListener);
byte PromBkp_addPostBorrarObserver(void*,void * promListener);
byte PromBkp_deletePostBorrarObserver(void*,void * promListener);
byte PromBkp_addPostEscribirListener(void*,void * promListener);
byte PromBkp_deletePostEscribirListener(void*,void * promListener);
*/
//void * PromBkp_promListener(word address,void * pmethod,void*Obj); 
/* 
#define INITIALIZATION_PROM_BKP(_class)                     \
    INITIALIZATION_MANEJADOR_MEMORIA(_class),	          		\
    FALSE,																			\
    NULL,                                       \
    0,                                          \
    INICIALITATION_LINKED_LIST()																																									
  */
    
#endif