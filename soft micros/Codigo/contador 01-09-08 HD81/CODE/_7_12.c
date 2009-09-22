/** ###################################################################
**     Filename  : _12_10.C
**     Project   : _12_10
**     Processor : MC9S12A256BCPV
**     Version   : Driver 01.10
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 13/07/2005, 16:06
**     Abstract  :
**         Main module. 
**         Here is to be placed user's code.
**     Settings  :
**     Contents  :
**         No public methods
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/
/* MODULE _12_10 */

/* Including used modules for compiling procedure */
#include "Cpu.h"
#include "Display1.h"
#include "bits5ULN.h"
#include "bits2ULN.h"
#include "trx.h"
#include "PTSL.h"
#include "PWSN.h"
#include "PUL.h"
#include "RTI.h"
#include "AS1.h"
#include "ADC1.h"
#include "FLASH1.h"
#include "TmDt1.h"
#include "RTI_int.h"
#include "ADC.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "limits.h"

//////////////////mis includes//////////////////////////////
#include "PWMs.h"
#include "Mydefines.h"
#include "boxes.h"
#include "Linealizacion.h"
#include "Comunicacion.h"
#include "Adquisidor.h"
#include "procesamiento.h"
#include "IFsh10.h"
#include "Programador.h"

////////////////////////////////////////////////////////////////////////////
// VARIABLES EN FLASH	 
////////////////////////////////////////////////////////////////////////////

const int PRom[PARAMETROS] @0x4000 ={
1000,       0,          0,        0,    // R_SetPoint 0
0,          0,          0,        0,    // R_ALa 4	 
0,          0,          0,        0,    // R_ALb 8 
0,          0,          0,        0,    // R_H1 12 
0,          0,          0,        0,    // R_HA1 16
0,          0,          0,        0,    // R_Per 20
8,          0,          0,        0,    // R_Sensor 24    /* direccion en Flash del TipoSensor1 
1,          0,          0,        0,    // R_Decimales 28 /* direccion de la cantidad de decimales 
0,          0,          0,        0,    // R_Offset  32   /* direccion en Flash del TipoSensor1 
1000,       1000,       1000,     1000, // R_Gan     36   /* direccion en Flash del TipoSensor1 
0,          0,          0,        0,    // R_ACT 40
0,          0,          0,        0,    // R_AGT 44
0,          0,          0,        0,    // R_ACP 48
0,          0,          0,        0,    // R_AGP 52
0,          0,          0,        0,    // R_ATA 56
0,          0,          0,        0,    // R_T_AL 60
0,          0,          0,        0,    // R_Lim_Inf 64 /*dir lim Inf 
1000,       1000,       1000,     1000, // R_Lim_Sup 68  /*dir lim sup 
0,          0,          0,        0,    // R_ABA1  72				
1,          0,          0,        0,    // R_Tcontrol1  76
0,          0,          0,        0,    // R_Reset  80
200,        0,          0,        0,    // R_AB1 84
0,          0,          0,        0,    // R_IN1 88
0,          0,          0,        0,    // R_DR1 92
0,          0,          0,        0,    // R_Pra 96
0,          0,          0,        0,    // R_Talar1 100
0,          0,          0,        0,    // R_Pot_Inf 104  
10000,      10000,      10000,    10000,// R_Pot_Sup 108  
0,          0,          0,        0,    // R_Tsalcont 112 
0,          0,          0,        0,    // R_Potman 116
0,          0,          0,        0,    // R_Stn 120
-1,         -1,         -1,       -1,   // R_Programa 124
0,          0,          0,        0,    // R_None 128
0,          0,          0,        0,    // R_None 132
0,          0,          0,        0,    // R_None 136
0,          0,          0,        0,    // R_None 140
0,          0,          0,        0,    // R_None 144
0,          0,          0,        0,    // R_None 148
0,          0,          0,        0,    // R_None 152
0,          0,          0,        0,    // R_None 156
0,          0,          0,        0,    // R_None 160
0,          0,          0,        0,    // R_None 164
0,          0,          0,        0,    // R_None 168
0,          0,          0,        0,    // R_None 172
0,          0,          0,        0,    // R_None 176
0,          0,          0,        0,    // R_None 180
0,          0,          0,        0,    // R_None 184
0,          0,          0,        0,    // R_None 188
0,          0,          0,        0,    // R_None 192
0,          0,          0,        0,    // R_None 196
0,          0,          0,        0,    // R_None 200
0,          0,          0,        0,    // R_None 204
0,          0,          0,        0,    // R_None 208
0,          0,          0,        0,    // R_None 212
0,          0,          0,        0,    // R_None 216

0,    // R_SetC 220
0,    // R_Ver  221
1,    // R_Id   222 /* direccion del Id del aparato*/
0,    // R_adq  223
2006, // R_Ano	224
1,    // R_mes	225
1,    // R_dia	226
0,    // R_Hora 227
1     // R_int	228

};

			

////////////////////////////////////////////////////////////////////////////
// VARIABLES GLOBALES
////////////////////////////////////////////////////////////////////////////
int PRam[PARAMETROS];	          //PARAMETROS en Flash

///////VAriables que se ven desde la comunicacion//////
#pragma DATA_SEG MYDATA
int ValFinal[4];
int SetPoint[4];  // Set Point en Ram que se utiliza para el control y los calculos
int duty_cont_ch[4];
int duty_alar_ch[4];
#pragma DATA_SEG DEFAULT
////////////////////////////////////////////////////////////////////////////////
const byte div_dec[]={1,10,100}; // divisores del decimal/////////////////////////



byte  * ptr_ctes;							      // puntero a constantes en la flash
word CNT1_RTI;								      // contador (10 seg) de RTIs usado para la navegacion
//U8  CtrlMode;								// normal / manual
PunteroF PtrTmp;			/* para el manipuleo */

long Vx[CANTIDAD_CANALES];               //Array de los valores que salen del ADC
long ValProv[CANTIDAD_CANALES];           //(0x1000);	variable para entrar a las tablas
byte Result[CANTIDAD_CANALES];						//valor linealizado
int ValProc[CANTIDAD_CANALES];          //variable para el control ajustada con ofset y ganancia
int ValCont [CANTIDAD_CANALES];          //valor que controla el equipo con PID
long TA;		                      //Temperatura ambiente
int duty_aaux_ch1;
int duty_aaux_ch2;
int buffer_deriv[CANTIDAD_CANALES];
int timer_deriv[CANTIDAD_CANALES];
long suminteg[CANTIDAD_CANALES];
int integ[CANTIDAD_CANALES];
int deriv[CANTIDAD_CANALES];

int duty_aux_hist;								//provisorio para guardar cuando histeresis no cambia
//////////VARIABLES DE LOS BOXES////////////////
#ifdef adquisidor
int Estado_Adquisicion;
#endif
byte indice_Flash[PARAMETROS/8+1]; /* Indice de parametros modificados*/
extern bool save_parametros;
////////////////////////////////////////////////

///////////////// variables externas para el teclado /////////////////////////////
byte	KeyEdge=' ';				// teclas presionada. Reset en main
////////////////////////////////////////////////////////////////////////////////////////

////////////// variables de los displays ///////////////////////////////
char  Digitos[CANTIDAD_DISPLAYS][10];	// buffer de caracteres ascii a visualizar en 7 segmentos
char  DigDpy[CANTIDAD_DISPLAYS][10];	// caracteres decodificados del buffer ascii
byte DotNum[CANTIDAD_DISPLAYS];			/* punto decimal a encender */
unsigned int cont;					//contadores para scrolling
/////////////////////////////////////////////////////////////

/////////////LEDS//////////////////////
bool led_c[CANTIDAD_SAL_CONTROL],led_al[CANTIDAD_SAL_ALARMA];
///////////////////////////////////

///////////PWM/////////////
word RatioStore[4];
//////////////////////////
/////////////COMUNICACION///////////////////////
extern bool AS1_Tx;
int duty;
extern byte msn[16];
extern byte Step;
////////////MEMORIZACION/////////////////////////
#ifdef adquisidor
extern bool Date_EnUser;
#endif
bool Mostrar_Proc;

////////////AUTO SINTONIA //////////////////////
dword St_Counter[CANTIDAD_SAL_CONTROL+CANTIDAD_SAL_ALARMA];
byte St_Step[CANTIDAD_SAL_CONTROL+CANTIDAD_SAL_ALARMA];
int prev_val,St_val_max;
#define St_T_MAX 2000000
#define St_T_MIN 6000
#define St_Hist 2
////////////////////////////////////////////////
/////////////////FUNCION PRINCIPAL//////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////				
 #if  PARAMETROS>256
	 #error los parametros a grabar son mas del tamaño de una pagina, hay que modificar las funciones de FLASH!!
 #endif
 #if CANTIDAD_CANALES <1
  #error como minimo un canal
 #endif
 #if CANTIDAD_CANALES >2
  #error todavia no implementado
 #endif
 #if CANTIDAD_DISPLAYS != 2
  #error todavia no implementado
 #endif
 
void main(void)
{ 
  byte i;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
	
/* Write your code here */   
  RTI_Init();			 //inicializacion Timer
  #ifdef adquisidor
  TmDt1_Init(); 	 // Inicializacion Fecha y Hora 
  #endif
  PWM01_Init();		 // Inicializacion PWM
  PWM23_Init();		 // Inicializacion PWM
  PWM45_Init();		 // Inicializacion PWM    
    
 		A_Sensor(0,PRom[R_Sensor],PRom[R_Decimales]);									//Limites para el sensor y dec y el PTSL
	#if CANTIDAD_CANALES==2
		A_Sensor(1,PRom[R_Sensor+1],PRom[R_Decimales+1]);									//Limites para el sensor y dec y el PTSL
	#endif
  
    setPWM_period((byte)PRom[R_Per],0);		// Setear Periodo Canal1
  	setPWM_period((byte)PRom[R_Pra],2); // Setear Periodo Alarma1
  	PtrTmp=&Principal1.DirProc;		            // Empezar en Principal
  	
 #ifdef adquisidor
		Setup_index();	 // Busca el indice para grabar parametros adquiridos
		 	
  	if (PRom[R_adq]==1) {		 // la adquisición quedo en si al apagarse el equipo?								  
  	  Escribir_Powerdown();  // Header que indica que hubo un corte de Energia durante la adquisición
  	  Estado_Adquisicion = 2;// Cartel en HLT (hult) por corte de energia
  	  EscribirParametro(R_adq,0);		 // Poner la adquisición en no
    	}
 #endif 	
/////////////////// LOOP CONTINUO /////////////////////////
  for(;;)
  { 
  (*PtrTmp)();            // Funcion para el box correspondiente; llama a Num Handler, TextHandler, etc.	
  //WDog1_Clear();					// resetear Watch dog
   
//normalizo para entrar en la tabla de linealizacion. Ajusta cero y offset del ad
//el ajuste de cero es absoluto y el de ganancia porcentual

   #define valnorm(i) ((Vx[i]+PRom[R_ACT+i])*(1000+PRom[R_AGT+i])/1000)  
   
      if (AD_proc)									 // esta el flag de procesar los resultados del AD??
   		{

        
////////////////// ELECCION DE SET POINTS ////////////////
     for (i=0;i<CANTIDAD_SAL_CONTROL;i++){
        if (PRom[R_Stn+i]== Stc) SetPoint[i] = PRom[R_SetPoint+i]; 
        #ifndef programador
        else SetPoint[i] = PRom[R_SetPoint+i];
        #else
		    else if(PRom[R_Programa+i]!=-1) SetPoint[i] = (int)SetPointPrograma[i] ;
		    else SetPoint[i] = PRom[R_SetPoint+i]; 
        #endif
     }
//////////////////////////////////////////////////////////
        
/////////////////// Calculos para los canales leidos//////////  

        for(i=0;i<CANTIDAD_CANALES;i++){// recorrer todos los canales
        Result[i]=Linealizar(valnorm(i),(byte)PRom[R_Sensor+i],&ValProc[i]);
          if (PRom[R_Sensor+i]<7)
          ValProc[i]=(int)(ValProc[i]+ TA + PRom[R_ATA]);   
          if ((PRom[R_Sensor+i]<7)&& (PRom[R_Decimales+i]<2))
          ValProc[i]/= div_dec[1-PRom[R_Decimales+i]];
          else if ((PRom[R_Sensor+i]==8)&& (PRom[R_Decimales+i]<3))
          ValProc[i]/= div_dec[2-PRom[R_Decimales+i]];
          if (ValProc[i]>9999) 
          Result[i]=ERR_OF;
					else if (ValProc[i]<-1999) 
					Result[i]=ERR_UF;
				ValProv[i]=ValProc[i]+PRom[R_Offset+i];         //preciso para pasar a long
				ValProv[i]=ValProv[i]*PRom[R_Gan]/1000;					//no anda todo en una linea
		
				ValFinal[i]=(int) ValProv[i];
				
        (void) integral(SetPoint[i],
                        (int)ValProv[i],
                        PRom[R_AB1+i],
												PRom[R_IN1+i],
												PRom[R_Tcontrol1+i],
												&suminteg[i],
                        &integ[i]
												);
 
        (void) derivada   ( (int)ValProv[i],
                            PRom[R_AB1+i],
                            PRom[R_DR1+i],
                            PRom[R_Tcontrol1+i],
							              &buffer_deriv[i],
								            &timer_deriv[i],
                            &deriv[i] 
								            );

        ValCont[i] =(int)ValProv[i]+integ[i]+deriv[i];
					
        }
 
           
        
        if (!PRom[R_Stn]== Stc){
			      // calculo el duty del canal 1. Primero veo onoff o PID
////////////////CONTROL 1//////////////////////////////////
        if (PRom[R_Tcontrol1] == 1 )		//Estoy en PID y no en autosintonia ???
        duty_cont_ch[0] = duty_prop(SetPoint[0], 
                                  ValCont[0], 
                                  PRom[R_AB1],  
                                  PRom[R_Reset],
															    PRom[R_Pot_Inf],
															    PRom[R_Pot_Sup],
                                  0);
        else {duty_aux_hist = duty_onoff(SetPoint[0], 
                              ValCont[0], 
                              PRom[R_H1],  
                              PRom[R_Reset],
                              0);
        if (duty_aux_hist != -10)         
				duty_cont_ch[0] = duty_aux_hist;
        };

// ahora veo cal, ref o manual

		    if (PRom[R_Tsalcont] == _ref)
		    duty_cont_ch[0] = 10000-duty_cont_ch[0];
		    else if (PRom[R_Tsalcont] == _man)
		    duty_cont_ch[0] = PRom[R_Potman]*10; 

      PWM_SetRatio16(duty_cont_ch[0],0);


//////////////ALARMA  1////////////////////////////////////

      duty_aux_hist =	 v_cont_al (PRom[R_T_AL],
                                  PRom[R_Talar1],
                                  (int)ValProv[0],
                                  SetPoint[0],
                                  PRom[R_ALa],
                                  PRom[R_Reset],
                                  PRom[R_HA1],
                                  PRom[R_ABA1] 
                                  );
    
        if (duty_aux_hist != -10)              //el duty es siempre positivo uso el -10 para avisar que estoy en zona de histeresis        
				duty_alar_ch[0] = duty_aux_hist;


      PWM_SetRatio16(duty_alar_ch[0],2);  
        }else
////////// AUTO SINTONIA ////////////////////////////////////////////////
//      for(i=0;i<)  		
   		{
				//Control 1//
				duty_aux_hist = duty_onoff(SetPoint[0], 
                              ValCont[0], 
                              St_Hist,  
                              PRom[R_Reset],
                              0);
        if (duty_aux_hist != -10)         
				duty_cont_ch[0] = duty_aux_hist;

        PWM_SetRatio16(duty_cont_ch[0],0);
				// Step Action //
				
	      if (St_Counter[0]>St_T_MAX)
	      EscribirParametro(R_Stn,St_Err);

	      switch(St_Step[0]){
        case 0: if (ValProv[0]> SetPoint[0]){  //espero a estar arriba
            St_Step[0]++;
            St_Counter[0]=0;
            main_text[3]='1';
            }
            break;
        case 1: if (ValProv[0]< SetPoint[0]){ //espero a estar abajo 
                St_Step[0]++;
      			    main_text[3]='2';
      			    prev_val= (int)ValProv[0];
      			    St_Counter[0]=0;
                }
      			   break;
        case 2: if (prev_val<ValProv[0]){
              St_Step[0]++; //encontre el minimo??
              main_text[3]='3';
              St_Counter[0]=0;
              prev_val=(int)ValProv[0];//actualizar valor
              } else prev_val=(int)ValProv[0]; //no,actualizar valor 
      				break;
	      case 3: if (ValProv[0]> SetPoint[0]){	      //espero a estar arriba
              St_Step[0]++;
	            main_text[3]='4';
	            }
	            break;
        case 4: if (prev_val>ValProv[0]){
              St_Step[0]++; //encontre el maximo??
              main_text[3]='5';
              St_val_max=(int)ValProv[0];
              prev_val=(int)ValProv[0];//actualizar valor
              } else prev_val=(int)ValProv[0]; //no,actualizar valor 
      				break;
	      case 5: if (ValProv[0]< SetPoint[0]){       //espero a estar abajo 
              St_Step[0]++;
	            main_text[3]='6';
	            }
	            break;
        case 6: if (prev_val<ValProv[0]){
               //encontre el minimo?? Si->termine
              Cpu_DisableInt();
							  if(St_Counter[0]<St_T_MIN){
	              EscribirParametro(R_Stn,St_Err);
	              }else{
	              EscribirParametro(R_ABA1,(int)((St_val_max-ValProv[0])*1.5));
	              EscribirParametro(R_IN1,(int)(St_Counter[0]/1000));
	              EscribirParametro(R_DR1,(int)(St_Counter[0]/10000));
	              EscribirParametro(R_Stn,St_Ok);
	              }
              Cpu_EnableInt();
              show_main_text=FALSE;
							} else prev_val=(int)ValProv[0]; //No->actualizar valor 
	      }
   		}
////////////////////////////////////////////////////////////////////////	
      AD_proc=FALSE;			// deshabilitar proceso de resultado de AD
      Mostrar_Proc=TRUE;  //Mostrar los valores en la pantalla principal (se procesa en Main Handler)
   		}

////////////////////////Comunicacion /////////////////////
    if (AS1_Tx==TRUE)						//Hay algo para enviar??
	  AS1_TxChar();						// Enviar
		
    if ( AS1_RecvChar(&msn[Step])==ERR_OK)  //Recibi algo????		
	  AS1_OnRxChar();											// Procesar

/////////////// Veo si hubo un overflow en el timer////////////////
    #ifdef adquisidor
    if (TFLG2_TOF==1){	 // el free counter runing dio una vuelta??
    TFLG2_TOF=1; //clear bit  free counter runing
      if (Date_EnUser) // se esta llevando la cuenta de la hora y el dia???
      TmDt1_Inc();   // Llamar a la funcion de tiempo
    }
    #endif
///////// veo si vuelvo a la pantalla principal/////////////
	  if(CNT1_RTI==0 && PtrTmp!=&Principal1.DirProc)		// PAsaron 10 segundos fuera de la pantalla principal??
	  { 
	  PtrTmp=&Principal1.DirProc;											//Volver a la pantalla principal
	  FstTime=TRUE;
	  }
	      	 
  }

  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
}/*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/


/* END _12_10 */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/

