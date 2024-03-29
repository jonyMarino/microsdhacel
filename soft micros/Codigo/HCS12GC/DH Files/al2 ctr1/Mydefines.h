
//////////////////// ASIGNACION DE SALIDAS/ENTRADAS /////////////////////////////
#define CANTIDAD_CANALES 1 /*Cantidad de canales */

#define CANTIDAD_SAL_CONTROL   1 /*Cantidad de salidas control*/

#define CANTIDAD_SAL_ALARMA  2 /*Cantidad de salidas alarma */

#define _STR_VERSION "007.2"
///Entradas (Canal de entrada al que est�n asociadas)////////
//// Salidas//////
#define _STR_MODELO "d101"
#define OUT_CNTR_1 0
#define OUT_CNTR_2 3
#define OUT_AL_1 2
#define OUT_AL_2 1
#define OUT_AL_3 3

#define outc1L 0
#define outc2L
#define outa1L 2
#define outa2L 1
#define outa3L 3

//////////////////// Tipo de Aparato /////////////////////////////
//#define debug
//#define HD90
//#define _ADQUISIDOR
#define _DISPLAY_2x4
//#define _PROGRAMADOR
  #ifdef _PROGRAMADOR
    #define prog_viejo
    #ifndef prog_viejo
      #define PROG_SIMPLE_RSTP
    #endif
  #endif
//#define pirani
#define _APARATO_VIEJO
//#define _COLADA_CALIENTE
#define _N_MODBUS
//#define _VP
//#define _SP_EXTERNO		


//#define DOBLE_SET_POINT     //OJO!!!!! actua solo sobre la primera salida de control

#define NUM_SALIDAS  CANTIDAD_SAL_CONTROL+CANTIDAD_SAL_ALARMA
 
#if CANTIDAD_SAL_CONTROL+ CANTIDAD_SAL_ALARMA>8
#error El programa fue pensado para hasta 8 salidas, revisar que modificaciones hay que hacer
#endif

#define FLASH_COM_START 0x4000 /* ep */
#define FLASH_COM_END 0x41FF 
  #ifdef _PROGRAMADOR
  #define FLASH_PROGRAMADOR_START   FLASH_COM_END + 1  /* flash donde estan las adquisiciones */  
  #define FLASH_PROGRAMADOR_END   FLASH_PROGRAMADOR_START + 2560 
    #ifdef  _ADQUISIDOR
    #define FLASH_ADQUISIDOR_START FLASH_PROGRAMADOR_END+1
    #define FLASH_ADQUISIDOR_END 0x5EFF
		#endif
	#else
	  #ifdef _ADQUISIDOR
	  #define FLASH_ADQUISIDOR_START  FLASH_COM_END + 1
    #define FLASH_ADQUISIDOR_END 0x5EFF
    #endif
  #endif
  
////BLOQUES A GRABAR POR APAGADO DEL APARATO/////
#define FLASH_APAGADO_START 0x5F00
#define FLASH_APAGADO_END   0x5FFF
/////////////////////////////////////////////////

#define RAM_COMUNICACION_END	 0x1200 /* donde termina la ram a la que se tiene acceso remoto (empieza en 0x1000) */ 
#define RAM_START 0x1000
#define RAM_END 0x1800
#define RAM_COMUNICACION_START 0x1000   /* donde empieza la ram a la que se tiene acceso remoto (empieza en 0x1000) */ 
#define CANTIDAD_DISPLAYS 4	 /* Numero de displays */

////////////////////VISUALIZACION//////////////////////////////////
#define DIGITOS 4
#define MAX_DIGITOS 10 /* Tama�o del texto m�s largo*/
#define TIME_SCROLL 200 /* multiplicador de tiempo de scroling*/
#define MAIN_TEXT_PERIOD 4000 /* periodo del cambio de mensaje en el display inferior para la pantalla Main*/
#define REFESH_NUMBER 1000 /*periodo en el que se refrescan los valores de los boxes numericos de tiempo real*/
#define MAX_BYTE  255
#define CHANGE_HD90_TEXT 2000
#define MIN_NUMBER_DISP -1999
#define MAX_NUMBER_DISP 9999
#define TRETURN 30000  //tiempo de retorno sin boton en ms


#define _TIEMPO_AD_EN_MILISEGUNDOS 1000

//      MODIFICACIONES  
#define jony_25_06		/*  Teclas para el Programador*/
#define jony_28_06		/*  1_En manual, que no se respete periodo on-off 
													2_Alarmas tengan Periodo igual al control
													3_Mensajes en el Display al poner estados en el Programador
                          4_Agegado de Box para decidir variable a mostrar en el dpy inferior
                      */
#define jony_05_07  /*
											1_ Problemas como funcion de Flash
											2_ Agregado de comportamiento ante Condicion de Emergencia
                      3_ desconectar los rele cuando se desconecta el aparato
                    */
#define jony_06_07 /*
										1_ Problemas al grabar mientras rueda el programa
										2_ Luego de q desaparece el PWSN tiene q mantenerse prendido el aparato 
                    */
#define jony_08_07  /*
											1_ Problemas al reestablecer el programa
                    */
#define jony_13_07  /*
										1_Arreglo SP Externo
										2_Refresh de parametro inferior en Principal1(MainHandler) siempre
                    */
#define jony_18_07 /*
										1_ Cambio de accion en EndP (queda en el final del programa)
										2_ Los Tiempos con los que se calculan la integral y la derivada 
										dependen del tiempo de entrada ente una lectura y otra del mismo canal 
										3_ Agegado de DIF en Version
                    */
#define jony_03_08  /*
                    1_ Problema con CRC de la comunicacion
                    */
#define jony_15_08  /*
										1_  Problema al mostrar Stop
										2_  Problema al restaurar Programador (se aumento tiempo a 2 seg)
										3_  Problema al ingresar mas de 500 minutos en el programador (problema de cast)
                    */
#define jony_17_08  /*
                    1_  Puesta en marcha de prog nuevo
                    */
#define jony_22_08  /*
										1_  Problema al arrancar programador
										2_  Problema en el modulo de la Flash al grabar un Byte
                    */
#define jony_24_08  /*
										1_  Version "ramp to set point(rStP)"
										  Acalraciones: En el programador al tener tolerancia 0 no se da bola a la condicion de emergencia.
										  Mientras que para rtSP fue necesario que si le de bola para que entre la C.E. ya que la tolerancia
										  siempre es 0 
                    */                    
