
/*SELECCIONAR UNA VERSION*/

//#include "c-Mydefgener.h"

/* ************ DH 101 C PIR *************** */

//#include "c-dh101-1al-PIR.h" /* Compilado */

//#include "c-dh100-1al-PIR.h" /* Compilado */

/* ************ DH 101 C *************** */

//#include "c-dh101-1al.h" /* Compilado */
//#include "c-dh101-2al.h" /* Compilado */
//#include "c-dh101-3al.h" /* Compilado */

/* ************ DH 101 P *************** */

#include "c-dh101P-1al.h" /* Compilado */
//#include "c-dh101P-2al.h" /* Compilado */
//#include "c-dh101P-3al.h" /* Compilado */

/* ************ DH 101 B *************** */

//#include "c-dh101-B.h" /* Compilado */
//#include "c-dh100-B.h" /* Compilado */

/* ************ DH 101 CCAL *************** */

//#include "c-dh101ccal-1al.h" /* Compilado */
//#include "c-dh100ccal-1al.h" /* Compilado */

/* ************ CD 101 CCAL *************** */

//#include "c-cd101ccal-1al.h" /* Compilado */

/* ************ DH 101P VP *************** */

//#include "c-dh101P-vp-1al.h" /* Compilado */
//#include "c-dh101P-vp-2al.h" /* Compilado */
//#include "c-dh100-vp-2al.h" /* Compilado */


/* ************ CD 101 C *************** */

//#include "c-cd101-1al.h" /* Compilado */
//#include "c-cd101-2al.h" /* Compilado */

/* ************ CD 101 P *************** */

//#include "c-cd101P-1al.h" /* Compilado */
//#include "c-cd101P-2al.h" /* Compilado */


/* ************** HD 90  *************** */

//#include "c-hd90-1al.h" /* Compilado */

/* ************** 2 SP  *************** */

//#include "c-dh101-2SP2AL.h" /* Compilado */

/* ************** HD 91  *************** */

//#include "c-hd91-1al.h" /* Compilado */

/* ************ DH 100 C *************** */

//#include "c-dh100-1al.h" /* Compilado */
//#include "c-dh100-2al.h" /* Compilado */
//#include "c-dh100-3al.h" /* Compilado */

/* ************ DH 100 P *************** */

//#include "c-dh100P-1al.h" /* Compilado */
//#include "c-dh100P-2al.h" /* Compilado */
//#include "c-dh100P-3al.h" /* Compilado */
												
/* ************************************* */

#define _PRINTER
////BLOQUES A GRABAR POR APAGADO DEL APARATO/////
#ifdef programador
  #define FLASH_APAGADO_START (FLASH_PROGRAMADOR_END+1)
  #define FLASH_APAGADO_END   (FLASH_APAGADO_START+511)
#else
  #define FLASH_APAGADO_START (FLASH_PARAMETROS_END+1)
  #define FLASH_APAGADO_END   (FLASH_APAGADO_START+511)
#endif
/////////////////////////////////////////////////

//////////MODIFICACIONES//////////////////
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
#define jony_23_08  /*
                    1_  Agregado de las direcciones de ajuste de sensor
                    */  
#define jony_27_02_08	 /*
											 1_ Se corrigio problema al reestablecer la energia para el Programador
                        */