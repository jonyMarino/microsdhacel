
//////////////////// ASIGNACION DE SALIDAS/ENTRADAS /////////////////////////////
#define CANTIDAD_CANALES 1 /*Cantidad de canales */

#define CANTIDAD_SAL_CONTROL   0 /*Cantidad de salidas control*/

#define CANTIDAD_SAL_ALARMA  0 /*Cantidad de salidas alarma */

#define _STR_VERSION "007.2"
///Entradas (Canal de entrada al que están asociadas)////////
//// Salidas//////
#define _STR_MODELO " CAU.101" 
//////////////////// Tipo de Aparato /////////////////////////////
#define _DISPLAY_2x4
#define _APARATO_VIEJO

#define NUM_SALIDAS  CANTIDAD_SAL_CONTROL+CANTIDAD_SAL_ALARMA
 
#if CANTIDAD_SAL_CONTROL+ CANTIDAD_SAL_ALARMA>8
#error El programa fue pensado para hasta 8 salidas, revisar que modificaciones hay que hacer
#endif


#define FLASH_COM_START 0x4000 /* ep */
#define FLASH_COM_END 0x41FF 
/////////////////////////////////////////////////
#define RAM_COMUNICACION_END	 0x1200 /* donde termina la ram a la que se tiene acceso remoto (empieza en 0x1000) */ 
#define RAM_START 0x1000
#define RAM_END 0x1800
#define RAM_COMUNICACION_START 0x1000   /* donde empieza la ram a la que se tiene acceso remoto (empieza en 0x1000) */ 
#define CANTIDAD_DISPLAYS 2	 /* Numero de displays */

////////////////////VISUALIZACION//////////////////////////////////
#define DIGITOS 4
#define MAX_DIGITOS 10 /* Tamaño del texto más largo*/
#define TIME_SCROLL 200 /* multiplicador de tiempo de scroling*/
#define MAIN_TEXT_PERIOD 4000 /* periodo del cambio de mensaje en el display inferior para la pantalla Main*/
#define REFESH_NUMBER 1000 /*periodo en el que se refrescan los valores de los boxes numericos de tiempo real*/
#define MAX_BYTE  255
#define CHANGE_HD90_TEXT 2000
#define MIN_NUMBER_DISP -1999
#define MAX_NUMBER_DISP 9999
#define TRETURN 30000  //tiempo de retorno sin boton en ms


#define _TIEMPO_AD_EN_MILISEGUNDOS 250                   
