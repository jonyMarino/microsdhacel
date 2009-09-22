#ifndef Boxes_H
#define Boxes_H
/* archivos include */
#include "display.h"
#include "cnfbox.h"
#include "PE_Error.h"
#include "PWMs.h"
#include "TmDt1.h"
#include "Adquisidor.h"
#include "IFsh10.h"
#include "Masks.h"
#include "TECLAS3.h"
#include "Mensajes.h"
#include "Display1.h"
#include "Display2.h"
/////////////LEDS//////////////////////
extern bool Date_EnUser;
///////////////////////////////////
#pragma CODE_SEG DEFAULT
#pragma DATA_SEG DEFAULT
static char main_text[]="St  ";
bool show_main_text;

#pragma CONST_SEG DEFAULT

long ValorTmpNum;
byte ValorTmpTxt;
bool Save;
extern PunteroF PtrTmp;
extern byte b,d;
extern unsigned int cont;
extern byte KeyEdge;
extern word CNT1_RTI;

/* variables de uso temporal por los boxes cuando se activan */
bool FstTime=TRUE;	/* set cuando se ejecuto al menos una vez el procesador */


/* Drivers para simular el hardware */
/************************************/
extern byte DotNum[CANTIDAD_DISPLAYS];			/* punto decimal a encender */
extern char	DigitoParpadeante;	

//////////////Funciones internas//////////////////////
void Exit(void);					 // Salir a pantalla principal
void Salir_num(char RF);	 // Salir por toque rapido o sostenido en pantalla numérica
void A_Cod(long Numero);
void A_ResetTot(byte number);
void A_ModoCuenta(byte Modo);
void ResetCuenta(void);
#ifdef adquisidor
void A_Adquiriendo (void); // Accion al poner si o no en el adquisidor
#endif
/* Procesadores de los boxes */
/*****************************/

/* maneja titulos: carga buffer de
   los display sup.e inf., con los
   textos de los boxes */
         
void TitleHandler(void){
		
	
// Primer Ingreso
	if (FstTime){					// es la primera vez que ingresa??
		FstTime=FALSE;			// sacar primera vez
		PtrBox.Tit=(Titulo*)PtrTmp;	 // Poner el puntero PtrBox.Tit con el valor del Box actual
		PasarASCII(&PtrBox.Tit->TxtDpy[0],1);    //mostrar display inferior
		PasarASCII(&PtrBox.Tit->TxtDpySup[0],0); //mostrar display superior	
	
		};
		
//T0QUE RÁPIDO  O MANTENIDO

	if (KeyEdge=='r'|| KeyEdge=='f') 				// Se presiono tecla rapida o mantenida??? y no hay nada para guardar??
	{ PunteroF Proximo;
	  if (KeyEdge=='r'){
	    if (PtrBox.Tit->VdeNavegacion==NULL)									// Existe variable selectora del proximo estado	 ???
 		  Proximo=(PunteroF)PtrBox.Tit->Teclar; // Cargar proximo Box por toque rapido
	    else 										 //no hay variable selectora
		  Proximo=PtrBox.Tit->Teclar[*(PtrBox.Tit->VdeNavegacion)];	 // Cargar proximo Box por toque rapido
	  }else
		Proximo=PtrBox.Tit->Teclaf;	 // Cargar proximo Box por toque sostenido
		
	if ((Proximo)!=NULL)		 // Se cargo un box existente???
		{ 
		b=d=0;								 //resetear variables de SCROLL
		cont=SCROLL*2;					 //resetear variables de SCROLL
		PtrTmp=Proximo;				 //Cargar puntero a la funcion correspondiente (TitleHandler, NumHandler, etc.)
		FstTime=TRUE;					 //Setear Primera vez
		};
			
			
	KeyEdge=' ';						 //Borrar tecla presionada
			
	};

// EXIT 

	if (KeyEdge== 'k') Exit();	 // Boton de Exit
}


     

/* Procesador de los boxes de Estado*/
/************************************/

void EstadoHandler (void)
{

// Primer Ingreso
if (FstTime){													 // es la primera vez que ingresa?? 
		FstTime=FALSE;										 // sacar primera vez
		PtrBox.Txt=(Textual*)PtrTmp;		   // Poner el puntero PtrBox.Txt con el valor del Box actual 
		PasarASCII(PtrBox.Txt->TxtDpy,1);     //Mostrar DisplayInf
		PasarASCII((char*)(PtrBox.Txt->TxtDpy0+ *(PtrBox.Txt->Fdir)),0);    // Mostrar DisplaySup		 
  };

// T0QUE RÁPIDO Y MANTENIDO

	if (KeyEdge=='r' || KeyEdge=='f')		// Se presiono tecla rapida o mantenida???	
	{ PunteroF Proximo;
	  if (KeyEdge=='r'){
	    if (PtrBox.Txt->VdeNavegacion==NULL) // Existe variable selectora de los Proximos Estados?? 
 		  Proximo=(PunteroF)PtrBox.Txt->Teclar; // Cargar proximo Box por toque rapido
		  else 
		  Proximo=PtrBox.Txt->Teclar[*(PtrBox.Txt->VdeNavegacion)];	 // Cargar proximo Box por toque sostenido
		}else  Proximo=PtrBox.Txt->Teclaf;  // Cargar proximo Box por toque sostenido
		
		if ((Proximo)!=NULL)  // Se cargo un box existente???
		{ 										
		b=d=0;								//resetear variables de SCROLL
		cont=SCROLL*2;					//resetear variables de SCROLL
		PtrTmp=Proximo;				//Cargar puntero a la funcion correspondiente (TitleHandler, NumHandler, etc.)
		FstTime=TRUE;					//Setear Primera vez
		};
						
	KeyEdge=' ';						//Borrar tecla presionada
			
	};
		
// EXIT

	if (KeyEdge== 'k') Exit();  // Boton de Exit
}


/* Procesador de los textos*/
/***************************/

/* de acuerdo a la tecla que se presiona, se incrementa o decrementa los valores
   de las variables numericas de los boxes  y 
   convierte el valor int a ascii, guardandolos en buffer DigitosSup */ 
void TxtHandler(void){
byte err;
// PRIMER INGRESO 		
	if (FstTime){					 // es la primera vez que ingresa??
		FstTime=FALSE;			 // sacar primera vez
		Save=FALSE;
		PtrBox.Txt=(Textual*)PtrTmp;	// Poner el puntero PtrBox.Txt con el valor del Box actual	    
	  ValorTmpTxt= *(PtrBox.Txt->Fdir); // Cargar el valor de la variable correspondiente al Box en el buffer
		PasarASCII(PtrBox.Txt->TxtDpy,1);             //Mostrar DisplayInf
		PasarASCII((char*)(PtrBox.Txt->TxtDpy0+ValorTmpTxt),0);  //Mostrar DisplaySup		 
  };


// TECLAS UP Y DOWN
if (KeyEdge=='u' || KeyEdge=='d'){					 // Se Presiono la tecla UP o Down??
	/* proceso tecla UP */
	if (KeyEdge=='u'){												 // Se Presiono la tecla UP??
		if (++ValorTmpTxt>=PtrBox.Txt->CantTxts)		 // Aumentar Buffer, no esta dentro de los limites???
		ValorTmpTxt=PtrBox.Txt->CantTxts-1;				 // Poner en el maximo valor
		}
	/* proceso tecla down */
	else if (KeyEdge=='d'){										 // Se Presiono la tecla Down???
		if (ValorTmpTxt>0)													 // el Buffer es mayor que 0???
			ValorTmpTxt--;														 // Decrementar Buffer
		else ValorTmpTxt=0;												 // si no poner Buffer en 0
		
		};
    PasarASCII((char*)(PtrBox.Txt->TxtDpy0+ValorTmpTxt),0);     // Mostrar DisplaySup
		Save=TRUE;																				 // Activar Flag de guardar valor
		KeyEdge=' ';																		 // Borrar tecla presionada
}

// T0QUE RÁPIDO O MANTENIDO

if (KeyEdge=='r' || KeyEdge=='f')				
	{PunteroF Proximo;
		
  if (KeyEdge=='r'){
    if (Save){																					 
			Display1_PutVal(0);
      Display2_PutVal(0);
			err=IFsh10_Setbyte((word)PtrBox.Txt->Fdir,ValorTmpTxt);
			if (err)
			  SetMessage(DISPLAY1,err);
			/*	funciones especiales de cada box */
		  #ifdef adquisidor
		  else if (PtrBox.Txt==&Adquiriendo) A_Adquiriendo();
		  #endif
		}
  }
  
  if (KeyEdge=='r'){
	  if (PtrBox.Txt->VdeNavegacion==NULL) // Existe variable selectora de los Proximos Estados??
 		Proximo=(PunteroF)PtrBox.Txt->Teclar; // Cargar proximo Box por toque rapido
		else 
		Proximo=PtrBox.Txt->Teclar[*(PtrBox.Txt->VdeNavegacion)];	 // Cargar proximo Box por toque sostenido
  }else  Proximo=PtrBox.Txt->Teclaf;  // Cargar proximo Box por toque sostenido
		
		if ((Proximo)!=NULL)  // Se cargo un box existente???
		{ 										
		b=d=0;								//resetear variables de SCROLL
		cont=SCROLL*2;					//resetear variables de SCROLL
		PtrTmp=Proximo;				//Cargar puntero a la funcion correspondiente (TitleHandler, NumHandler, etc.)
		FstTime=TRUE;					//Setear Primera vez
		};						
	KeyEdge=' ';						//Borrar tecla presionada
	};

/////////////////////// EXIT //////////////////////////

	if (KeyEdge== 'k') Exit(); // Boton de Exit

  
}

/* Procesador de los textos en Ram*/
/***************************/
void TxtHandlerRam(void){ 			
	
	if (FstTime){					 // es la primera vez que ingresa??
		FstTime=FALSE;			 // sacar primera vez
		PtrBox.Txt=(Textual*)PtrTmp;	// Poner el puntero PtrBox.Txt con el valor del Box actual	    
	  ValorTmpTxt= *(PtrBox.Txt->Fdir); // Cargar el valor de la variable correspondiente al Box en el buffer
		PasarASCII(PtrBox.Txt->TxtDpy,1);             //Mostrar DisplayInf
		PasarASCII((char*)(PtrBox.Txt->TxtDpy0+ValorTmpTxt),0);  //Mostrar DisplaySup		 
  };


// TECLAS UP Y DOWN
if (KeyEdge=='u' || KeyEdge=='d'){					 // Se Presiono la tecla UP o Down??
	/* proceso tecla UP */
	if (KeyEdge=='u'){												 // Se Presiono la tecla UP??
		if (++ValorTmpTxt>=PtrBox.Txt->CantTxts)		 // Aumentar Buffer, no esta dentro de los limites???
		ValorTmpTxt=PtrBox.Txt->CantTxts-1;				 // Poner en el maximo valor
		}
	/* proceso tecla down */
	else if (KeyEdge=='d'){										 // Se Presiono la tecla Down???
		if (ValorTmpTxt>0)													 // el Buffer es mayor que 0???
			ValorTmpTxt--;														 // Decrementar Buffer
		else ValorTmpTxt=0;												 // si no poner Buffer en 0
		
		};
    PasarASCII((char*)(PtrBox.Txt->TxtDpy0+ValorTmpTxt),0);     // Mostrar DisplaySup
		KeyEdge=' ';																		 // Borrar tecla presionada
}

// T0QUE RÁPIDO O MANTENIDO

if ((KeyEdge=='r' || KeyEdge=='f'))				
	{PunteroF Proximo;
	 if (KeyEdge=='r'){
	  *(PtrBox.Txt->Fdir)=ValorTmpTxt;
	  if (PtrBox.Txt == &B_ResetTot1 && ValorTmpTxt) A_ResetTot(0);
    else if (PtrBox.Txt == &B_ResetTot2 && ValorTmpTxt) A_ResetTot(1);
	  else if(PtrBox.Txt ==&B_ResetCuenta && ValorTmpTxt) ResetCuenta();
	  
	  if (PtrBox.Txt->VdeNavegacion==NULL) // Existe variable selectora de los Proximos Estados??
 		Proximo=(PunteroF)PtrBox.Txt->Teclar; // Cargar proximo Box por toque rapido
		else 
		Proximo=PtrBox.Txt->Teclar[*(PtrBox.Txt->VdeNavegacion)];	 // Cargar proximo Box por toque sostenido
  }else  Proximo=PtrBox.Txt->Teclaf;  // Cargar proximo Box por toque sostenido
		
		if ((Proximo)!=NULL)  // Se cargo un box existente???
		{ 										
		b=d=0;								//resetear variables de SCROLL
		cont=SCROLL*2;					//resetear variables de SCROLL
		PtrTmp=Proximo;				//Cargar puntero a la funcion correspondiente (TitleHandler, NumHandler, etc.)
		FstTime=TRUE;					//Setear Primera vez
		};						
	KeyEdge=' ';						//Borrar tecla presionada
	};     

/////////////////////// EXIT //////////////////////////

	if (KeyEdge== 'k') Exit(); // Boton de Exit

  
}
/* Procesador de los boxes numéricos*/
/************************************/
void NumHandler(void){	
static long incrementador,Digito;

	if (FstTime){				// es la primera vez que ingresa??	
		  FstTime=FALSE;  // sacar primera vez
			Save=FALSE;
			PtrBox.Num=(Numerico*)PtrTmp;	 // Poner el puntero PtrBox.Num con el valor del Box actual
	    ValorTmpNum=*(PtrBox.Num->Fdir);	 // Cargar el valor de la variable correspondiente al Box en el buffer
//			ValorTmpNum|=(*(PtrBox.Num->Fdir+2)<<16);
		  if ((PtrBox.Num->Dot)>=DECIMALES_CANAL1) // El punto decimal depende del Sensor??
        DotNum[0]=(byte)PuntoDecimal[PtrBox.Num->Dot-DECIMALES_CANAL1];
			else											 // sino
			  DotNum[0]=PtrBox.Num->Dot; // Cargar PD que indica el Box				  
      /* mando mensajes	*/						
		  PasarASCII(PtrBox.Num->TxtDpy,1);     //Mostrar DisplayInf
			Pasar_Numero(ValorTmpNum,0);		          //Mostrar DisplaySup
			DigitoParpadeante=DIGITOS_DISPLAY;
			incrementador=1;
	}

/* TECLA  DOWN */
  if (KeyEdge=='d') {
    if (DigitoParpadeante>0){
      DigitoParpadeante--;
      incrementador*=10;
    } else{
      DigitoParpadeante=DIGITOS_DISPLAY;
      incrementador=1;
    }
    KeyEdge=' ';							//Borrar tecla presionada
  }

/* proceso tecla UP */
  if (KeyEdge=='u'){ // Fue presionada una Tecla UP o Down???
	  if(ValorTmpNum==(*PtrBox.Num->Sup) && incrementador*10>ValorTmpNum)
	    ValorTmpNum%=incrementador;
	  else{																				
	    
	    ValorTmpNum+=incrementador;
		  Digito=ValorTmpNum/incrementador;
		  Digito%=10;
		  if (Digito==0)
		    ValorTmpNum-=(incrementador*10);
		
		  if (ValorTmpNum>*PtrBox.Num->Sup)             // El Buffer es meNOR que el LimiteSup?? Si-> Incrementar Buffer
				ValorTmpNum = *PtrBox.Num->Sup;						 // No-> Poner Buffer en maximo valor
	    else if (ValorTmpNum<*PtrBox.Num->Inf)
				ValorTmpNum = *(PtrBox.Num->Inf);				
	  
	  }
	  cont= SCROLL*4;
	  Pasar_Numero(ValorTmpNum,0); // Mostrar DisplaySup
		KeyEdge=' ';							//Borrar tecla presionada

	}
																						

/////////////////////// T0QUE RÁPIDO //////////////////////////

	if (KeyEdge=='r')	{
 		
		if (ValorTmpNum!=*(PtrBox.Num->Fdir))
  		{			    		  
  		  Display1_PutVal(0);
        Display2_PutVal(0);
  		  IFsh10_SetLong((word)PtrBox.Num->Fdir,ValorTmpNum);
  		  /*	funciones especiales de cada box */
  		  #ifdef adquisidor
  		  else if (PtrBox.Num==&intervalo)if (Estado_Adquisicion!=1)  (void)TmDt1_SetAlarm(Valor_Tmp_Num);				 
  		  #endif  		  		
  		}
  Salir_num('r');		// funcion de salida
			
	};
		
/////////////////////// TOQUE MANTENIDO ////////////////////////

if (KeyEdge=='f')	Salir_num('f');	 // funcion de salida

/////////////////////// EXIT //////////////////////////

	if (KeyEdge== 'k') Exit();	 // Boton de Exit
}


/* Procesador de los boxes numéricos*/
/************************************/ 
void Num_realtime_Handler(void){
static long Valant;
// Primer Ingreso	
	if (FstTime){				// es la primera vez que ingresa??	
		  FstTime=FALSE;  // sacar primera vez
			PtrBox.Num=(Numerico*)PtrTmp;	 // Poner el puntero PtrBox.Num con el valor del Box actual

		if ((PtrBox.Num->Dot)>=DECIMALES_CANAL1) // El punto decimal depende del Sensor??
      DotNum[0]=(byte)PuntoDecimal[PtrBox.Num->Dot-DECIMALES_CANAL1];
			else											 // sino
			DotNum[0]=PtrBox.Num->Dot; // Cargar PD que indica el Box		
// mando mensajes
		  Valant = *(PtrBox.Num->Fdir); 
		  PasarASCII(PtrBox.Num->TxtDpy,1);     //Mostrar DisplayInf
			Pasar_Numero(Valant,0);		          //Mostrar DisplaySup					
	}
	
	if(Valant != *(PtrBox.Num->Fdir)){
	 Valant = *(PtrBox.Num->Fdir);
	 Pasar_Numero(Valant,0);
	}
/////////////////////// T0QUE RÁPIDO //////////////////////////

	if (KeyEdge=='r')  Salir_num('r');		// funcion de salida
			
		
/////////////////////// TOQUE MANTENIDO ////////////////////////

if (KeyEdge=='f')	Salir_num('f');	 // funcion de salida

/////////////////////// EXIT //////////////////////////

	if (KeyEdge== 'k') Exit();	 // Boton de Exit
}

/* Procesador del  ingreso de Programa  */
/****************************************/
void NumHandlerRam(void){	
static long incrementador,Digito;

	if (FstTime){				// es la primera vez que ingresa??	
		  FstTime=FALSE;  // sacar primera vez
			Save=FALSE;
			PtrBox.Num=(Numerico*)PtrTmp;	 // Poner el puntero PtrBox.Num con el valor del Box actual
	    ValorTmpNum=*(PtrBox.Num->Fdir);	 // Cargar el valor de la variable correspondiente al Box en el buffer
//			ValorTmpNum|=(*(PtrBox.Num->Fdir+2)<<16);
		  if ((PtrBox.Num->Dot)>=DECIMALES_CANAL1) // El punto decimal depende del Sensor??
        DotNum[0]=(byte)PuntoDecimal[PtrBox.Num->Dot-DECIMALES_CANAL1];
			else											 // sino
			  DotNum[0]=PtrBox.Num->Dot; // Cargar PD que indica el Box				  
      /* mando mensajes	*/						
		  PasarASCII(PtrBox.Num->TxtDpy,1);     //Mostrar DisplayInf
			Pasar_Numero(ValorTmpNum,0);		          //Mostrar DisplaySup
			DigitoParpadeante=DIGITOS_DISPLAY;
			incrementador=1;
	}

/* TECLA  DOWN */
  if (KeyEdge=='d') {
    if (DigitoParpadeante>0){
      DigitoParpadeante--;
      incrementador*=10;
    } else{
      DigitoParpadeante=DIGITOS_DISPLAY;
      incrementador=1;
    }
    KeyEdge=' ';							//Borrar tecla presionada
  }

/* proceso tecla UP */
  if (KeyEdge=='u'){ // Fue presionada una Tecla UP o Down???
	  if(ValorTmpNum==(*PtrBox.Num->Sup) && incrementador*10>ValorTmpNum)
	    ValorTmpNum%=incrementador;
	  else{																				
	    
	    ValorTmpNum+=incrementador;
		  Digito=ValorTmpNum/incrementador;
		  Digito%=10;
		  if (Digito==0)
		    ValorTmpNum-=(incrementador*10);
		
		  if (ValorTmpNum>*PtrBox.Num->Sup)             // El Buffer es meNOR que el LimiteSup?? Si-> Incrementar Buffer
				ValorTmpNum = *PtrBox.Num->Sup;						 // No-> Poner Buffer en maximo valor
	    else if (ValorTmpNum<*PtrBox.Num->Inf)
				ValorTmpNum = *(PtrBox.Num->Inf);				
	  
	  }
	  cont= SCROLL*4;
	  Pasar_Numero(ValorTmpNum,0); // Mostrar DisplaySup
		KeyEdge=' ';							//Borrar tecla presionada

	}
																						

/////////////////////// T0QUE RÁPIDO //////////////////////////

	if (KeyEdge=='r' && PtrBox.Num!=&B_Codigo)	{
    if (Save)
      *(PtrBox.Num->Fdir)=ValorTmpNum;	
    Salir_num('r');
	};	
/////////////////////// TOQUE MANTENIDO ////////////////////////

if (KeyEdge=='f')	Salir_num('f');	 // funcion de salida

/////////////////////// EXIT //////////////////////////

	if (KeyEdge== 'k') Exit();	 // Boton de Exit
}



/* Procesador del  ingreso de fechas    */
/****************************************/

#ifdef adquisidor

void DiaHandler(void){
static byte Max_day;

if (KeyEdge=='u' || KeyEdge=='d'){
	if (KeyEdge=='u'){
  		if (ValorTmp < Max_day)
		    ValorTmp++;
 	    else ValorTmp=Max_day; 
	} else if (KeyEdge=='d'){
	if (ValorTmp > 1)
		ValorTmp--;
	else ValorTmp=1;
	
	}
	Pasar_Numero(ValorTmp,0);		           //DisplaySup
  save_parametros=TRUE;
  KeyEdge=' ';
}
	
	if (FstTime){
		  FstTime=FALSE;
		  Max_day = TmDt1_GetMaxday(PRom[R_Ano],(byte)PRom[R_mes]);		
			PtrBox.Num=(Numerico*)PtrTmp;
			
	    ValorTmp=*(PtrBox.Num->Fdir);
			DotNum[0]=PtrBox.Num->Dot;		
		  
		  PasarASCII(PtrBox.Num->TxtDpy,1);     //DisplayInf
			Pasar_Numero(ValorTmp,0);		           //DisplaySup
					
	}
	
/////////////////////// T0QUE RÁPIDO //////////////////////////

	if (KeyEdge=='r'){
	      if (save_parametros){
	  		  *(PtrBox.Num->Fdir)=ValorTmp;
	        if (Estado_Adquisicion!=1)(void)TmDt1_SetDate(PRom[R_Ano],(byte) PRom[R_mes],(byte)ValorTmp);
	       }
	        Salir_num('r');
	      
	}
		
/////////////////////// TOQUE MANTENIDO ////////////////////////

if (KeyEdge=='f')	Salir_num('f');
/////////////////////// EXIT //////////////////////////

if (KeyEdge== 'k') Exit();

}

/*   Procesador del  ingreso de hora    */
/****************************************/

void HoraHandler (void) {
  if (KeyEdge=='u' || KeyEdge=='d'){
	if (KeyEdge=='u'){
  		if (ValorTmp < 2359){
  		   ValorTmp++;
  			 if (((ValorTmp%100)%60)==0 && ValorTmp!=0) ValorTmp +=40;
  		}
 	    else ValorTmp=0; 
	} else if (KeyEdge=='d'){
	if (ValorTmp > 0){
	  
		if (((ValorTmp%100)%60)==0) ValorTmp-=40;
		ValorTmp--; 
	}
	else ValorTmp=2359;
	
	}
	Pasar_Numero(ValorTmp,0);		           //DisplaySup
  save_parametros=TRUE;
  KeyEdge=' ';
}
	
	if (FstTime){
		  FstTime=FALSE;	
			
			PtrBox.Num=(Numerico*)PtrTmp;
			
	    ValorTmp=*(PtrBox.Num->Fdir);
			DotNum[0]=PtrBox.Num->Dot;		
		  
		  PasarASCII(PtrBox.Num->TxtDpy,1);     //DisplayInf
			Pasar_Numero(ValorTmp,0);		           //DisplaySup
					
	}
	
/////////////////////// T0QUE RÁPIDO //////////////////////////

	if (KeyEdge=='r'){
	if (save_parametros){
	  
	  *(PtrBox.Num->Fdir)=ValorTmp;
	  if (Estado_Adquisicion!=1){
	    (void)TmDt1_SetTime((byte)(ValorTmp/100),(byte)(ValorTmp%100));
	    TmDt1_Enable(TRUE);
	  }
	}
	
	Salir_num('r');
	}
		
/////////////////////// TOQUE MANTENIDO ////////////////////////

if (KeyEdge=='f')	Salir_num('f');
/////////////////////// EXIT //////////////////////////

if (KeyEdge== 'k') Exit();


}

#endif


/* Procesador de la pantalla principal */
/***************************************/
void MainHandler(void){
static long Valant[2];
byte i;
char * Mensaje;
static char * MensajeMostrado[CANTIDAD_DISPLAYS];
static bool texto[CANTIDAD_DISPLAYS];
extern word screen_cont;		
extern long ValDisp;
/* ejecuto si es la primera vez que se llama al manejador */

	if (FstTime){													 // es la primera vez que ingresa??
	FstTime=FALSE; 												 // sacar primera vez
  DotNum[0]=(byte)PuntoDecimal[0];
  DotNum[1]=(byte)PuntoDecimal[0];
	PtrBox.Num=(Numerico*)PtrTmp;					 // Poner el puntero PtrBox.Num con el valor del Box actual
	Valant[0]=ValDisp;
	Valant[1]=*(PtrBox.Num->Fdir);
	Pasar_Numero(ValProc,0);
	Pasar_Numero(Valant[1],1);
	};
	
/* muestro en la pantalla superior el valor del proceso o ERROR de Conteo*/		
  for (i=0;i<CANTIDAD_DISPLAYS;i++){
    
    Mensaje=GetMessage(i);
    if(screen_cont<MAIN_TEXT_TIME && Mensaje!=NULL){
      
      if (!texto[i] || MensajeMostrado[i]!=Mensaje ){
        texto[i]=TRUE;
        MensajeMostrado[i]=Mensaje;
        PasarASCII(Mensaje,i);  
      }
    }
    else {
      switch(i){
        case 0:
          if (texto[0] || Valant[0]!=ValDisp){
            texto[0]=FALSE;
            Valant[0]=ValDisp;
            DotNum[0]=(byte)PuntoDecimal[0];
            Pasar_Numero(ValDisp,0);						 //Mostrar Variable del Proceso
          }
          break;
        case 1:
 	        if (texto[1] || Valant[1]!=*(PtrBox.Num->Fdir)){
 	          texto[1]=FALSE;
 	          Valant[1]=*(PtrBox.Num->Fdir);
 	          Pasar_Numero(Valant[1],1);
 	        }
      }
    }
  }
/* T0QUE RÁPIDO o MANTENIDO */
  if (KeyEdge=='r' || KeyEdge=='f')Salir_num(KeyEdge);							

  if (KeyEdge=='d'){
    KeyEdge=' ';
    ResetCuenta();
  }
}


///////////////////////////Funciones internas /////////////
///////////////////////////////////////////////////////////
void Exit(void){	// Funcion Boton de Exit 
		DigitoParpadeante=NO_DIGIT;
		KeyEdge=' ';
		CNT1_RTI=0;
}

void Salir_num(char RF){		// Funcion de Salida por toque mantenido o rapido
 PunteroF Proximo;	/* Proximo estado con toque sostenido */
 
 if(RF=='r'){  
  if (PtrBox.Num->VdeNavegacion== NULL)// Existe variable selectora de los Proximos Estados??
		 Proximo=(PunteroF)PtrBox.Num->Teclar; // Cargar proximo Box por toque sostenido
	else  Proximo=PtrBox.Num->Teclar[*(PtrBox.Num->VdeNavegacion)];		 // Cargar proximo Box por toque rapido
 }else Proximo=PtrBox.Num->Teclaf;  // Cargar proximo Box por toque sostenido

		
	if (Proximo!=NULL) {	// Se cargo un box existente???  
		  {
		  cont=SCROLL*2;		 //resetear variables de SCROLL
		  DigitoParpadeante=NO_DIGIT;
		  b=d=0;					 //resetear variables de SCROLL
		  PtrTmp=Proximo;  //Cargar puntero a la funcion correspondiente (TitleHandler, NumHandler, etc.)
		  FstTime=TRUE;		 //Setear Primera vez
		  }
	
	}
 KeyEdge=' ';		//Borrar tecla presionada
}

//////////////////////////////funciones de accion al entrar/////////
void A_ResetTot(byte number){  
  switch (number){
    case 0:
           TotCuenta=0;
           OverflowFlags&= ~OF_TOT1_MASK;
           ContFlags&= ~ TOT_CNT_STOP_MASK;
           PreTotalizador=-Cnt_getCuenta(); 
            break;
    case 1:
    			TotOnSPP=0;
          OverflowFlags&= ~OF_TOT2_MASK; 
          ContFlags&= ~ TOT_ON_SPP_STOP_MASK;
  }
}

void A_Cod(long Numero){
  if (!(Numero==SetC) && !(Numero==2602))
  PtrTmp=&B_Principal1.DirProc; 
}
#ifdef adquisidor
void A_Adquiriendo(void)
{
 if ((Estado_Adquisicion==0 || Estado_Adquisicion==2)&& ValorTmp==1 && Date_EnUser){			//de no a si
 TmDt1_EnDiAlarm(TRUE);
 Estado_Adquisicion=1;
 } else if (Estado_Adquisicion==3 && ValorTmp==1 && Date_EnUser) {
 
  		  Borrar_Adquisicion();
  		  TmDt1_EnDiAlarm(TRUE);
 				Estado_Adquisicion=1;
 } else if (ValorTmp==0 || !Date_EnUser) {
  TmDt1_EnDiAlarm(FALSE);
  if (Estado_Adquisicion==1)Estado_Adquisicion=0;
 }
}
#endif 

#endif