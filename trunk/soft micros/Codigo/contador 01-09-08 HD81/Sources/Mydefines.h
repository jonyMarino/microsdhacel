//////////////////// Tipo de Aparato /////////////////////////////
//#define TEST_MODE
//#define adquisidor
//#define _UN_SET_POINT
#define CANTIDAD_CANALES 1 /*Cantidad de canales */

#define _APARATO_VIEJO
#define _NMODBUS		 // no modbus

#define jony_23_08

#define DEBOUNCE_TIME 100  /* en ms tiempo de MICROSWITCH*/

#define MAX_INDICACION_DISP 999999
#define FLASH_PARAMETROS_START 0xC100 /* ep */
#define FLASH_PARAMETROS_END 0xC1FF 
	  #ifdef adquisidor
	  #define FLASH_ADQUISIDOR_START  FLASH_PARAMETROS_END + 1
    #define FLASH_ADQUISIDOR_END 0x7EFF
    #endif
////BLOQUES A GRABAR POR APAGADO DEL APARATO/////
#define FLASH_APAGADO_START 0x7F00
#define SECCION_PROGRAMA    140
#define FLASH_APAGADO_END   0x7FFF
/////////////////////////////////////////////////

#define RAM_COMUNICACION_END	 0x3FFF /* donde termina la ram a la que se tiene acceso remoto (empieza en 0x1000) */ 
#define RAM_COMUNICACION_START 0x3800   /* donde empieza la ram a la que se tiene acceso remoto (empieza en 0x1000) */ 
#define CANTIDAD_DISPLAYS 2	 /* Numero de displays */
#define DIGITOS_DISPLAY 5
////////////////////VISUALIZACION//////////////////////////////////
#define SCROLL 500 /* multiplicador de tiempo de scroling*/
#define MAIN_TEXT_PERIOD 4000 /* periodo del cambio de mensaje en el display inferior para la pantalla Main*/
#define MAIN_TEXT_TIME 1000 /* tiempo que estará el mensaje en el display inferior para la pantalla Main*/
//////////////////////////////////////////////////////////////////

///////////////TESTS//////////////
//#define TEST_CUENTA_CALCULADA