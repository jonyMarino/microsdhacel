#ifndef _PROGRAMADOR_H
#define _PROGRAMADOR_H
#include "PE_Types.h"
#include "Mydefines.h"
#include "boxes.h"
//////////Forma de mostrar mensajes//////////////////
#define is_cout TRUE   // Si no se quiere mostrar informacion poner FALSE 
#define cout(str)  set_MainText(str) 


//////////Definiciones de Programa///////////////////
#define CONF_NO_PROGRAMA 0	 /* Para programa, límite superior */

#if defined( PROG_SIMPLE_RSTP) && defined(jony_24_08)
  #define MAX_PROGRAMAS 1
  #define MAX_SEGMENTOS 3
#else
  #define MAX_PROGRAMAS 10
  #define MAX_SEGMENTOS 24
#endif

int get_Programa(byte);
byte set_Programa(int val,byte num_cntrl);
int get_LimSup_Programa(void);




/*Estado del Programa*/

typedef enum {
 PROG_STOPED, 
 PROG_RUNNING,
 PROG_RESETED 
}t_prog_state;

void Prog_Stop(void);
void Prog_Continue(void);
void Prog_reset(void);

t_prog_state get_ProgState(byte canal);

/*                    */

#ifdef _PROGRAMADOR

//////////DEFINICIONES DEL PROGRAMA EN GENERAL ///////////
  typedef enum{
    END_KEEPCONECTED,
    END_DISCONECT
  }T_OnEnd;
  #define MAX_VALUE_ON_END 1
  
  typedef enum{
    COND_CONTINUE,
    COND_RESET_SEG,
    COND_RESET_PROG,
    COND_END_PROG,
    COND_NO
  }T_CondEmer;	
  #define MAX_VALUE_COND_GRAL 4
  #define MAX_VALUE_COND  3
  
  typedef enum{
    TTOL_OFF,
    TTOL_LOW,
    TTOL_HI,
    TTOL_BAND,
    TTOL_NO
  }T_Tolerancia;
  #define MAX_VALUE_TIPO_TOL_GRAL 4
  #define MAX_VALUE_TIPO_TOL  3
  
  typedef enum{
    TEMP_INI_SET,
    TEMP_INI_AMBIENTE
  }T_Temperatura_Ini;
  #define MAX_VALUE_TIPO_TEMP_INI 1

/////////// Definiciones para el segmento///////////////////
#define TAMANIO_SEGMENTO 5
#define PROG_PRESICION_VEL  1 // 1 decimal

  typedef enum{
    SEG_END,
    SEG_RMP_T,
    SEG_RMP_V,								
    SEG_MESETA,
    SEG_STEP,
    SEG_JMP
  }T_Segmento;
  #define MAX_VALUE_TIPO_SEGMENTO 5
  							
  typedef struct{
    T_Segmento tipo_segmento;
    T_CondEmer condicion_emer;
    T_Tolerancia tipo_tolerancia;
    int temperatura_f; 
    int tolerancia;
    word tiempo; 
  }TSegmentos;		//9 bytes
  
////////////////////////////////////////////////////////
#define TAMANIO_GENERAL 5 //Sin el Cant_Seg que se graba aparte
typedef struct{
    T_OnEnd OnEnd;
    T_CondEmer condicion_emer;
    T_Tolerancia tipo_tolerancia;
    int temperatura_inicial;    
    int tolerancia;				  
    T_Temperatura_Ini tipo_temperatura_inicial; 
  }Tinfoprograma;  //8 bytes
  
typedef struct{
 Tinfoprograma Gral;
 TSegmentos Segmento[MAX_SEGMENTOS];
 byte nada[5]; //debe haber por lo menos un nada declarada para que se ponga en SEG_END en el segmento 26
}TProgramas;		 //sizeof(TProgramas)= 256 bytes

#define OFFSET_SEG1 1

#define velocidad tiempo 

extern int SetPointPrograma[CANTIDAD_SAL_CONTROL];
extern byte ProgramaActual[];
extern bool Prog_actualizar;

//void Prog_ActualizarSetPoints(void);

byte get_iActualSegment(byte channel);

byte set_ActualSegment(byte val,byte channel);

byte get_iActualProgram(byte channel);

void Prog_Init(void);

bool isProgFinish(byte chan);

byte get_Lim_Seg(byte programa);

//void ActualizarSetPointPrograma(byte canal);

void runPrograma(byte canal,char programa, byte Segmento,long segs);


void ReestablecerPrograma(byte canal);

#define get_SP_Programa(chan) SetPointPrograma[chan]
#define GuardarPrograma() (void)WriteArray(FLASH_APAGADO_START,0, (5+2*MAX_PROGRAMAS)*CANTIDAD_SAL_CONTROL*sizeof(int), (word*)ProgramaActual)

  ////////////  GETs & SETs Program Running////////////
  /*  Tiempo  */
    int get_TiempoMinutos(byte num_cntrl);
    byte set_TiempoMinutos(int val,byte num_cntrl);  
  ////////////  GETs & SETs Program Page///////////////
  /*  Programas */
    //Condicion OnEnd/////////////////
    byte Prg_set_OnEnd(T_OnEnd on_end,byte program);
    T_OnEnd Prg_get_OnEnd(byte program);
    //Temperatura inicial////////////
    byte Prg_set_TempIni(int val,byte program);
    int Prg_get_TempIni(byte program);
    //  Tipo Temperatura inicial  ////////////
    byte Prg_set_TipoTempIni(T_Temperatura_Ini val,byte program);
    T_Temperatura_Ini Prg_get_TipoTempIni(byte program);
    //  Condicion de Emergencia General ///////
    T_CondEmer Prg_get_CondEmerGral(byte program);
    byte Prg_set_CondEmerGral(T_CondEmer val,byte program);
    /// Tolerancia General////////////////////
    int Prg_getToleranciaGral(byte program);
    byte Prg_setToleranciaGral(int val,byte program);
    //  Tipo Tolerancia General //////////////
    T_Tolerancia Prg_getTipoTolGral(byte program);
     byte Prg_setTipoTolGral(T_Tolerancia val,byte program);
  /*  Segmentos */
    ///////Tipo de Segmento///////////
    T_Segmento Prg_get_TipoSeg(byte program,byte segment);
    byte Prg_set_TipoSeg(T_Segmento val,byte program,byte segment);
    ///////Velocidad//////////////////
    byte  Prg_set_Velocity(word val,byte program,byte segment);
    word Prg_get_Velocity(byte program,byte segment);
    ///////Set Point//////////////////
    byte Prg_set_SetPoint(int val,byte program,byte segment);
    int Prg_get_SetPoint(byte program,byte segment);
    ///////Tiempo //////////////////
    byte Prg_set_Time(word val,byte program,byte segment);
    word Prg_get_Time(byte program,byte segment);
    /// Condicion de Emergencia ////
    T_CondEmer Prg_getCondicionEmer(byte program,byte segment);  
    byte Prg_setCondicionEmer(T_CondEmer val,byte program,byte segment);
    /// Tipo Tolerancia ////
    T_Tolerancia Prg_getTipoTol(byte program,byte segment);
    byte Prg_setTipoTol(T_Tolerancia val,byte program,byte segment);
    /// Tolerancia  ////
    int Prg_getTolerancia(byte program,byte segment);
    byte Prg_setTolerancia(int val,byte program,byte segment);
    ///////Jump programa //////////////////
    byte Prg_set_JumpProg(word val,byte program,byte segment);
    word Prg_get_JumpProg(byte program,byte segment);
    /////// Ciclos = Tiempo
    
#endif
#endif