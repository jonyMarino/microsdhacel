/* archivos include */
#include "display.h"
#include "PE_Error.h"
#include "PWM.h"
#include "TmDt1.h"
#include "Adquisidor.h"
#include "IFsh10.h"
#include "cnfbox.h"
#include "Timer.h"
#include "Sensores.h"
#include "PTSL.h"
#include "cnfbox.h"
#include "Programador.h"
#include "boxesprog.h"
#include "boxesset.h"
#include "parametros.h"
#include "Grabacion.h"
#include "Control.h"
#include "boxes.h"


#pragma CODE_SEG DEFAULT
#pragma DATA_SEG DEFAULT

static char main_text[5];

#pragma CONST_SEG DEFAULT

static byte Tecla;
static byte numero_elemento;			// empezando de 0

static int LimInf;
static int LimSup;							

static bool save;

/* variables de uso temporal por los boxes cuando se activan */
static PunteroF PtrTmp;
static int Valor_Tmp;				// Buffer del parametro procesado

static bool FstTime;	/* set cuando se ejecuto al menos una vez el procesador */

#ifdef _PROGRAMADOR
static enum {NOPROGRAMA,PROGRAMA}BoxAnterior; // Para saber desde donde se entro al BOx de Segmento
#endif

//////////////Funciones internas//////////////////////
void Main_Mostrar2_canales(void);
void Main_Mostrar_canal(void);
void Exit(void);					 // Salir a pantalla principal
void procesar_up_down(byte tecla,int * valor_tmp);
void prepare_proximo(void){
 // ResetScroll();
  FstTime=TRUE;
}
static void set_proximo_box(byte num_elem,PunteroF proximo){
  if(numero_elemento+1==num_elem){   
    numero_elemento = 0;
    set_proximo(proximo);
  }else{
     numero_elemento++;
     prepare_proximo();    
  }
}

void boxes_refresh_value(void){
  if(Box_is_actual((PunteroF)&Principal1))
    prepare_proximo();  
}


void Boxes_Init(void){
  Display_Init(); 
  set_proximo((PunteroF)&Principal1);
}

void ProcesarBox(byte tecla){
  Tecla=tecla;
  (*PtrTmp)(PtrTmp);            // Funcion para el box correspondiente; llama a Num Handler, TextHandler, etc.	
}

void Box_set_new(PunteroF ppf){
  if(ppf!=PtrTmp)
    set_proximo(ppf);
}

bool Box_is_actual(PunteroF ppf){
  return ppf==PtrTmp;
}

/* Procesadores de los boxes */
/*****************************/

/* Procesador de Base box */
/**************************/
void BoxProc(TBox * box)
{
	if (FstTime){					// es la primera vez que ingresa??
		FstTime=FALSE;			// sacar primera vez
		PasarASCII(box->TxtDpy,1); //mostrar display inferior	
  };	
  
  // EXIT 
	if (Tecla== 'k') Exit();	 // Boton de Exit
  
}

/* Procesador de Base Parametro */
/********************************/
void ParametroProc(TParametro * parametro){
  if (FstTime){					// es la primera vez que ingresa??
    BoxProc(&parametro->Box);
    //Corregir numero del titulo
    if(numero_elemento>0){
      const char str[MAX_DIGITOS];
      int i;
      for(i=0;(parametro->Box).TxtDpy[i];i++)
        str[i]=(parametro->Box).TxtDpy[i];
      str[i-1]= numero_elemento+'1';
      str[i]='\0';
      PasarASCII(str,1); //mostrar display inferior	
    }
    //Setear variables
    Valor_Tmp = get_ValParametro(numero_elemento,parametro->sDato);
    LimInf= 		get_LimInfParametro(numero_elemento,parametro->sDato);
    LimSup=			get_LimSupParametro(numero_elemento,parametro->sDato);
    save=FALSE;  
    
  }
  
  BoxProc(&parametro->Box);
  
  if ((Tecla=='u') || (Tecla=='d')){ // Fue presionada una Tecla UP o Down???
        procesar_up_down(Tecla,&Valor_Tmp);
			  save=TRUE;							            // Grabar parametros
  }
    
  if (Tecla=='r'){
    if(save)
      set_ValParametro(Valor_Tmp,numero_elemento,parametro->sDato);
  }

    
}

/* Procesador de Base Textual   */
/********************************/
void ProcTTextual(Ttextual * text_box){

  if(FstTime){
     ParametroProc(&text_box->Parametro);
     PasarASCII(text_box->TxtDpy0[Valor_Tmp],0);    //mostrar display superior
  }
  
  ParametroProc(&text_box->Parametro);

  if ((Tecla=='u') || (Tecla=='d')) // Fue presionada una Tecla UP o Down???
  	PasarASCII(text_box->TxtDpy0[Valor_Tmp],0);    //mostrar display superior

  
}

/* Procesador de Textual1   */
/****************************/
void ProcTextual1(Textual1 * text_box){
  ProcTTextual(&text_box->BaseTextual);
  if (Tecla=='r')  
    set_proximo_box(((TParametro*)text_box)->num_elementos,text_box->Teclar);
}


/* Procesador de Textual  con salto condicional  */
/*************************************************/
void ProcTextJumpCond(TextualJumpCond * text_box){
   ProcTTextual(&text_box->BaseTextual);
   if (Tecla=='r' || Tecla=='f'){
    PunteroF prox_tmp= (*text_box->pf_siguiente)(Tecla);
    set_proximo_box(((TParametro*)text_box)->num_elementos,prox_tmp); 
   }
}

/* Procesador de Base Numerico  */
/********************************/
void ProcNumerico(TNumerico * num_box){
  
  if (FstTime){					// es la primera vez que ingresa??
    ParametroProc(&num_box->Parametro);
    /*  A Modificar!!!    */
    if((num_box->Dot>=DECIMALES_CANAL1))
      Pasar_Numero(Valor_Tmp,0,get_Decimales(num_box->Dot-DECIMALES_CANAL1)); // Valor en Dpy superior
    else
      Pasar_Numero(Valor_Tmp,0,num_box->Dot);
    
    /*    */
  }
  
  ParametroProc(&num_box->Parametro);
  
  if ((Tecla=='u') || (Tecla=='d')){ // Fue presionada una Tecla UP o Down???
  	/*  A Modificar!!!    */
  	if((num_box->Dot>=DECIMALES_CANAL1))
      Pasar_Numero(Valor_Tmp,0,get_Decimales(num_box->Dot-DECIMALES_CANAL1+numero_elemento)); // Valor en Dpy superior
    else
      Pasar_Numero(Valor_Tmp,0,num_box->Dot);
  }
    /*      */
  
}

/* Procesador de Numerico1  */
/****************************/
void ProcNumerico1(Numerico1 * num_box){
   ProcNumerico(&num_box->BaseNumerico);
   if (Tecla=='r')  
    set_proximo_box(((TParametro*)num_box)->num_elementos,num_box->Teclar); 
}


/* Procesador de Numerico2  */
/****************************/
void ProcNumerico2(Numerico2 * num_box){
   ProcNumerico1(&num_box->BoxNumerico);
   if (Tecla=='f')  
    set_proximo(num_box->Teclaf); 
}

/* Procesador de Numerico3  */
/****************************/
void ProcNumerico3(Numerico3 * num_box){
   ProcNumerico(&num_box->BaseNumerico);
   if (Tecla=='r')  
    set_proximo_box(
                  ((TParametro*)num_box)->num_elementos,
                  (num_box->siguientes).Teclar[(*((num_box->siguientes).get_VarNavegacion))()]
                  ); 
}

/* Procesador de Numerico4  */
/****************************/
void ProcNumerico4(Numerico4 * num_box){
   ProcNumerico3(&num_box->BoxNumerico);
   if (Tecla=='f')  
    set_proximo(num_box->Teclaf); 
}

/* Procesador de Numerico con salto condicional  */
/*************************************************/
void ProcNumJumpCond(NumericoJumpCond * num_box){
   ProcNumerico(&num_box->BaseNumerico);
   if (Tecla=='r' || Tecla=='f'){
    PunteroF prox_tmp= (*num_box->pf_siguiente)(Tecla);
    set_proximo_box(((TParametro*)num_box)->num_elementos,prox_tmp); 
   }
}


/* maneja titulos: carga buffer de
   los display sup.e inf., con los
   textos de los boxes */
         
void ProcTitle(Titulo * tit_box){
	
// Primer Ingreso
	if (FstTime){					// es la primera vez que ingresa??
		BoxProc(&tit_box->Box);
		PasarASCII(tit_box->TxtDpySup,0);    //mostrar display superior
	};
	
	BoxProc(&tit_box->Box);
		
//T0QUE RÁPIDO  O MANTENIDO
  if(!Fsh_to_save()){    
	  if (Tecla=='r') set_proximo( tit_box->Teclar);
	  else if (Tecla=='f') set_proximo( tit_box->Teclaf); 
  }



}

/* Procesador de Base Parametro Read Only*/
/*****************************************/
void ParametroROProc(TParametro_Read_Only * parametro){
  if (FstTime){					// es la primera vez que ingresa??
    BoxProc(&parametro->Box);
    if(numero_elemento>0){
      const char str[MAX_DIGITOS];
      int i;
      for(i=0;(parametro->Box).TxtDpy[i];i++)
        str[i]=(parametro->Box).TxtDpy[i];
      str[i-1]= numero_elemento+'1';
      str[i]='\0';
      PasarASCII(str,1); //mostrar display inferior	
    }
    Valor_Tmp = (*parametro->get)(numero_elemento);    
  }  
  BoxProc(&parametro->Box);    
}

/* Procesador de Numerico Read Only*/
/***********************************/
void ProcNumericoRO(NumericoRO * num_box){
  
  if (FstTime){					// es la primera vez que ingresa??
    ParametroROProc(&num_box->parametro);
    /*  A Modificar!!!    */
    if((num_box->Dot>=DECIMALES_CANAL1))
      Pasar_Numero(Valor_Tmp,0,get_Decimales(num_box->Dot-DECIMALES_CANAL1+numero_elemento)); // Valor en Dpy superior
    else
      Pasar_Numero(Valor_Tmp,0,num_box->Dot);
    
    /*    */
  } 
  ParametroROProc(&num_box->parametro);
}

/* Procesador de Numerico1 Read Only*/
/************************************/
void ProcNumericoRO1(NumericoRO1 * num_box){ 
  ProcNumericoRO(&num_box->numerico_base);
  if (Tecla=='r')  
    set_proximo_box(((TParametro_Read_Only*)num_box)->num_elementos,num_box->Teclar); 
}

/* Procesador de Numerico Read Only Con Salto Condicional*/
/*********************************************************/
void ProcNumRO_JmpCond(NumRO_JmpCond * num_box){ 
  ProcNumericoRO(&num_box->numerico_base);
  if (Tecla=='r' || Tecla=='f'){
    PunteroF prox_tmp= (*num_box->pf_siguiente)(Tecla);
    set_proximo_box(((TParametro_Read_Only*)num_box)->num_elementos,prox_tmp); 
   }
}

/* Procesador de los boxes con pantalla exponencial en pirani*/
/*************************************************************/
#ifdef pirani
void NumExpoHandler(Numerico1 * num_box){
// Primer Ingreso	
	if (FstTime){				// es la primera vez que ingresa??
			ParametroProc(num_box->Parametro);
		  FstTime=FALSE;  // sacar primera vez
			save=FALSE; /*Reseteo flag de mandar a grabar*/
			PtrBox.Num=(Numerico*)PtrTmp;	 // Poner el puntero PtrBox.Num con el valor del Box actual
	    if(PtrBox.Num->sDato->Fdir != NULL)
	      Valor_Tmp = *(PtrBox.Num->sDato->Fdir); // Cargar el valor de la variable correspondiente al Box en el buffer
		  else
		    Valor_Tmp=0;			
// analizo punto decimal
				 
		if ((PtrBox.Num->Dot)>=DECIMALES_CANAL1) // El punto decimal depende del Sensor??
      DotNum[0]=get_Decimales(PtrBox.Num->Dot-DECIMALES_CANAL1);
			else											 // sino
			DotNum[0]=PtrBox.Num->Dot; // Cargar PD que indica el Box		
// mando mensajes
						
		PasarASCII(PtrBox.Num->TxtDpy,1);     //Mostrar DisplayInf

    #ifdef  pirani
    if(get_Sensor(0)==SENSOR_PIR)
      Pasar_Numero_Expo(Valor_Tmp,0,DotNum[0]);
    else
      Pasar_Numero(Valor_Tmp,0,DotNum[0]);						 //Mostrar Variable del Proceso
		#else
      Pasar_Numero(Valor_Tmp,0,DotNum[0]);						 //Mostrar Variable del Proceso
		#endif			
	}
																		
// KeyEdgeS UP O DOWN
if ((Tecla=='u') || (Tecla=='d')){ // Fue presionada una Tecla UP o Down???
int sumador,div;  
    
  #ifdef pirani
	if(get_Sensor(0)==SENSOR_PIR){
  for(div=1;(Valor_Tmp/div)>0;div*=10);
  if(div>1)
    div/=10;
  if(div>1)
    div/=10;
  if(((Valor_Tmp)/(div*10))==1 && ((Valor_Tmp)%(div*10))==0 && (div>=10))
    div/=10;
  sumador=div;
	}
  #endif
  
	/* proceso Tecla UP */
	if (Tecla=='u'){									 // Fue presionada una Tecla UP ???
		    if (Valor_Tmp+sumador<(*PtrBox.Num->sDato->Sup)) Valor_Tmp+=sumador; // El Buffer es menor que el LimiteSup?? Si-> Incrementar Buffer
				else Valor_Tmp=(*PtrBox.Num->sDato->Sup);						 // No-> Poner Buffer en maximo valor
				
	};
	
	/* proceso Tecla down */
	if (Tecla=='d'){		  					      // Fue presionada una Tecla Down???
				if (Valor_Tmp-sumador>(*PtrBox.Num->sDato->Inf)) Valor_Tmp-=sumador;		// El Buffer es mayor que el LimiteInf?? Si-> Decrementar Buffer
				else                    Valor_Tmp=(*PtrBox.Num->sDato->Inf);	// No-> Poner Buffer en el minimo valor			
				
		};
	
	 	if(get_Sensor(0)==SENSOR_PIR)
      Pasar_Numero_Expo(Valor_Tmp,0,DotNum[0]);
    else
      Pasar_Numero(Valor_Tmp,0,DotNum[0]);						 //Mostrar Variable del Proceso
		save=TRUE;							// Grabar parametros
	//	Tecla=' ';							//Borrar Tecla presionada
}

/////////////////////// T0QUE RÁPIDO //////////////////////////

	if (Tecla=='r')	{
		if (save)								    		  
  		  set_ValParametro(Valor_Tmp,PtrBox.Num->sDato);
  Salir_num();		// funcion de salida			
	};
		
/////////////////////// TOQUE MANTENIDO ////////////////////////

if (Tecla=='f')
  Salir_num();	 // funcion de salida

/////////////////////// EXIT //////////////////////////

	if (Tecla== 'k') Exit();	 // Boton de Exit
}
#endif
/* Procesador de los boxes de tiempo del Segmento corriendo*/
/***********************************************************/
#ifdef _PROGRAMADOR
void TieSegHandler(Numerico1 * num_box ){
bool Fst=FstTime;
byte chan,seg,prog;
T_Segmento tipo_seg;
  
  ProcNumerico1(num_box);
  
  if(Tecla=='u' || Tecla=='d' || Fst){
    chan = numero_elemento;
    seg = get_iActualSegment(chan);
    
    if(seg+1>get_Lim_Seg(chan))
      Tecla='r'; //Exit
    prog = get_iActualProgram(chan);
    tipo_seg= Prg_get_TipoSeg(prog,seg);
    if(tipo_seg ==SEG_RMP_V){
      if(!(seg>0 || Prg_get_TipoTempIni(prog)!=TEMP_INI_AMBIENTE))
        Tecla='r'; //Exit
    }
  }
  
/*  if (Fst){
    Valor_Tmp= get_TiempoMinutos(chan);
    Pasar_Numero(Valor_Tmp,0,(num_box->BaseNumerico).Dot);		          //Mostrar DisplaySup
  }
  */
}
#endif
/* Procesador de los boxes de Ancho de banda/histeresis*/
/*******************************************************/
#ifdef _APARATO_VIEJO
void ABHandler(Numerico1 * num_box){
bool Fst=FstTime;
char new_text[5]="H   ";  
  
 
  ProcNumerico1(num_box);
  
  if(Fst || Tecla=='u' || Tecla=='d'){
    if(Valor_Tmp>0){
       new_text[0]='A';  
       new_text[1]='b';
    }
    new_text[3]='1'+numero_elemento;
    PasarASCII(new_text,1);     //Mostrar DisplayInf   
  }
}

void ABAHandler(Numerico1 * num_box){
bool Fst=FstTime;
char new_text[5]="HA 1";  
  
  ProcNumerico1(num_box);
  
  if(Fst || Tecla=='u' || Tecla=='d'){
    if(Valor_Tmp>0){
      new_text[0]='A';  
      new_text[1]='b';
      new_text[2]='A';
    }
    new_text[3]='1'+numero_elemento;
      PasarASCII(new_text,1);     //Mostrar DisplayInf  
  }
}
#endif
/* Procesador del box de Codigo*/
/*******************************/
void CodHandler(Numerico2 * num_box){
  if(FstTime){
    ProcNumerico2(num_box);
    Valor_Tmp=0;  
  }
  
  ProcNumerico2(num_box);
  if(Tecla=='f'){
    if (!(Valor_Tmp==get_SetC() || Valor_Tmp==2602))
        set_proximo((PunteroF)&Principal1);  
  }
}

#ifdef _PROGRAMADOR
/* Procesador del box de elección de programa (Utiliza NumHandler)*/
/******************************************************************/
/*
void ProgramaHandler(Numerico1 * num_box){

  ProcNumerico1(num_box);
  
  if (Tecla=='r'){		
    for(Lim_Segmento1=0;Programa[programa_ingresado].Segmento[Lim_Segmento1].tipo_segmento!=SEG_END;Lim_Segmento1++);
    segmento_ingresado=0;
    BoxAnterior =  PROGRAMA;
  }  
}
*/
/* Procesador del box de elección de segmento (Utiliza NumHandler)*/
/******************************************************************/
/*
void SegmentoHandler(Numerico1 * num_box){
  

  if(FstTime){
  byte i;
  TSegmentos * dir;
  char end[]="End ";
  TSegmentos BufferSegmento;			//Contiene los datos a grabar
    
    ProcNumerico1(num_box);
    if (BoxAnterior==NOPROGRAMA){
  //grabar
      BufferSegmento.tipo_segmento= tipo_segmento;
      BufferSegmento.condicion_emer = (byte) condicion_emer;
      BufferSegmento.tipo_tolerancia = (byte)tipo_tolerancia;
      BufferSegmento.temperatura_f = temperatura_f;
      BufferSegmento.tiempo = tiempo; 
      BufferSegmento.tolerancia = tolerancia;

      dir = &Programa[programa_ingresado].Segmento[0];
      dir+= segmento_ingresado-1;
    
      for(i=0;i<TAMANIO_SEGMENTO;i++)
        EscribirWord((word)dir+i*2,*((word*)&BufferSegmento.tipo_segmento+i)); 
      
      SaveNow=TRUE;
    
  //Actualizar
      if (segmento_ingresado==MAX_SEGMENTOS){    
        PasarASCII(end,0);     //DisplaySup
        Lim_Segmento1=segmento_ingresado=Valor_Tmp=MAX_SEGMENTOS-1;
      }
    
    }else BoxAnterior = NOPROGRAMA;
    
  } 
  
  ProcNumerico1(num_box);

  if(Tecla=='r'){
    if (!segmento_ingresado){ //Si es igual a 0, cargo la info de esos boxes
    tipo_temperatura_inicial = Programa[programa_ingresado].Gral.tipo_temperatura_inicial; 
    temperatura_inicial = Programa[programa_ingresado].Gral.temperatura_inicial;
    tipo_tolerancia_gral = Programa[programa_ingresado].Gral.tipo_tolerancia;
    tolerancia_gral = Programa[programa_ingresado].Gral.tolerancia;
    condicion_emer_gral = Programa[programa_ingresado].Gral.condicion_emer; 
    }else{
        if (Programa[programa_ingresado].Gral.tipo_tolerancia==no){
        next_tiempo=0; //ir a tolerancia(next box)
          if(Programa[programa_ingresado].Gral.condicion_emer==no){
          next_prog=next_tol = 0;  // ir a Condicon de emergencia(next box)
          }else {
            next_prog=next_tol = 1;//ir a segmento     
          }
        }
        else if (Programa[programa_ingresado].Gral.condicion_emer==no){
          next_prog=0;	 //ir a Condicon de emergencia(next box)
          next_tiempo=1; //ir a Condicon de emergencia(next box)
        }else{
          next_tiempo=2; //ir a segmento
          next_prog=1;	 //ir a segmento
        }
    }

    tipo_segmento = Programa[programa_ingresado].Segmento[segmento_ingresado].tipo_segmento;
    temperatura_f = Programa[programa_ingresado].Segmento[segmento_ingresado].temperatura_f;
    tiempo = Programa[programa_ingresado].Segmento[segmento_ingresado].tiempo;
    tolerancia =  Programa[programa_ingresado].Segmento[segmento_ingresado].tolerancia;
    tipo_tolerancia = Programa[programa_ingresado].Segmento[segmento_ingresado].tipo_tolerancia;
    condicion_emer = Programa[programa_ingresado].Segmento[segmento_ingresado].condicion_emer;


  #ifndef prog_viejo
    if(!segmento_ingresado)
      set_proximo(R_Seg[1]);
  #endif  


    segmento_ingresado++;
    Lim_Segmento1++;

  }
}
*/
#endif
/* Procesador de los boxes numéricos con refresco de pantalla*/
/*************************************************************/ 
/*
void Num_realtime_Handler(void){
static bool refresh;
// Primer Ingreso	
	if (FstTime){				// es la primera vez que ingresa??	
		  FstTime=FALSE;  // sacar primera vez
			PtrBox.NumRO=(NumericoRO*)PtrTmp;	 // Poner el puntero PtrBox.Num con el valor del Box actual

		if ((PtrBox.NumRO->Dot)>=DECIMALES_CANAL1) // El punto decimal depende del Sensor??
      DotNum[0]=(byte)PRom[R_Decimales+PtrBox.Num->Dot-DECIMALES_CANAL1];
			else											 // sino
			DotNum[0]=PtrBox.NumRO->Dot; // Cargar PD que indica el Box		
// mando mensajes
		  PasarASCII(PtrBox.NumRO->TxtDpy,1);     //Mostrar DisplayInf
			refresh=TRUE;
	}
	if(refresh){
	 refresh=FALSE;
	 Timer_Run(REFESH_NUMBER,&refresh,UNICO_SET,NULL);
	 Pasar_Numero(*(PtrBox.NumRO->Dato),0,DotNum[0]);
	}
/////////////////////// T0QUE RÁPIDO //////////////////////////

	if (Tecla=='r')  Salir_num();		// funcion de salida
			
		
/////////////////////// TOQUE MANTENIDO ////////////////////////

if (Tecla=='f')	Salir_num();	 // funcion de salida

/////////////////////// EXIT //////////////////////////

	if (Tecla== 'k') Exit();	 // Boton de Exit
}
 */
/* Procesador del  ingreso de fechas    */
/****************************************/

#ifdef adquisidor

void DiaHandler(void){
static byte Max_day;

if (Tecla=='u' || Tecla=='d'){
	if (Tecla=='u'){
  		if (Valor_Tmp < Max_day)
		    Valor_Tmp++;
 	    else Valor_Tmp=Max_day; 
	} else if (Tecla=='d'){
	if (Valor_Tmp > 1)
		Valor_Tmp--;
	else Valor_Tmp=1;
	
	}
	Pasar_Numero(Valor_Tmp,0);		           //DisplaySup
  save=TRUE;
}
	
	if (FstTime){
		  FstTime=FALSE;
		  save=FALSE; /*Reseteo flag de mandar a grabar*/
		  Max_day = TmDt1_GetMaxday(PRom[R_Ano],(byte)PRom[R_mes]);		
			PtrBox.Num=(Numerico*)PtrTmp;
			
	    Valor_Tmp=*(PtrBox.Num->Fdir);
			DotNum[0]=PtrBox.Num->Dot;		
		  
		  PasarASCII(PtrBox.Num->TxtDpy,1);     //DisplayInf
			Pasar_Numero(Valor_Tmp,0);		           //DisplaySup
					
	}
	
/////////////////////// T0QUE RÁPIDO //////////////////////////

	if (Tecla=='r'){
	      if (save){ 
	      set_ValParametro(Valor_Tmp,PtrBox.Num->sDato);
	      /* *(PtrBox.Num->Fdir)=Valor_Tmp;
	        if (Estado_Adquisicion!=1)(void)TmDt1_SetDate(PRom[R_Ano],(byte) PRom[R_mes],(byte)Valor_Tmp);
	       */
	       }
	        Salir_num('r');
	      
	}
		
/////////////////////// TOQUE MANTENIDO ////////////////////////

if (Tecla=='f')	Salir_num('f');
/////////////////////// EXIT //////////////////////////

if (Tecla== 'k') Exit();

}

/*   Procesador del  ingreso de hora    */
/****************************************/

void HoraHandler (void) {
  if (Tecla=='u' || Tecla=='d'){
	if (Tecla=='u'){
  		if (Valor_Tmp < 2359){
  		   Valor_Tmp++;
  			 if (((Valor_Tmp%100)%60)==0 && Valor_Tmp!=0) Valor_Tmp +=40;
  		}
 	    else Valor_Tmp=0; 
	} else if (Tecla=='d'){
	if (Valor_Tmp > 0){
	  
		if (((Valor_Tmp%100)%60)==0) Valor_Tmp-=40;
		Valor_Tmp--; 
	}
	else Valor_Tmp=2359;
	
	}
	Pasar_Numero(Valor_Tmp,0);		           //DisplaySup
  save=TRUE;
 // Tecla=' ';
}
	
	if (FstTime){
		  FstTime=FALSE;	
			
			PtrBox.Num=(Numerico*)PtrTmp;
			
	    Valor_Tmp=*(PtrBox.Num->Fdir);
			DotNum[0]=PtrBox.Num->Dot;		
		  
		  PasarASCII(PtrBox.Num->TxtDpy,1);     //DisplayInf
			Pasar_Numero(Valor_Tmp,0);		           //DisplaySup
					
	}
	
/////////////////////// T0QUE RÁPIDO //////////////////////////

	if (Tecla=='r'){
	if (save){ 
	  set_ValParametro(Valor_Tmp,PtrBox.Num->sDato);
	  /*
	  *(PtrBox.Num->Fdir)=Valor_Tmp;
	  if (Estado_Adquisicion!=1){
	    (void)TmDt1_SetTime((byte)(Valor_Tmp/100),(byte)(Valor_Tmp%100));
	    TmDt1_Enable(TRUE);
	  }
	  */
	}
	
	Salir_num('r');
	}
		
/////////////////////// TOQUE MANTENIDO ////////////////////////

if (Tecla=='f')	Salir_num('f');
/////////////////////// EXIT //////////////////////////

if (Tecla== 'k') Exit();


}

#endif

#ifdef prog_viejo
/* Procesador del box del titulo del Programador viejo */
/*******************************************************/
void ProcTitleProg(Titulo * tit_box){
  ProcTitle(tit_box); 
  if(Tecla=='r'){
    En_ProgConf();
    Reset_ProgSegMostrados();
  }
}									
/* Procesador de las pantallas del programador viejo */
/*****************************************************/
void ProgHandler(Numerico1 * num_box, void(*pHandler)(void*)){
bool Fst=FstTime;
char new_text[5]; 
 
  (*pHandler)(num_box);
  
  if (Fst==TRUE){
    byte prog_conf=ConfPrg_getSegMostrado();
    byte seg_conf=ConfPrg_getProgMostrado(); 
    new_text[0]=prog_conf+'0';
    new_text[1]=((TBox *)num_box)->TxtDpy[1];
    if(seg_conf/10){
      new_text[2]=seg_conf/10+'0'; 
      new_text[3]=seg_conf%10+'0';
    } else  {
      new_text[2]=' ';  
      new_text[3]=seg_conf+'0';
    }
    new_text[4]='\0';
    PasarASCII(new_text,1);
  }
}

/* Procesador del box de temperatura y tiempo de los segmentos siguientes */
/**************************************************************************/
void NumProgHandler(Numerico1 * num_box){
  ProgHandler(num_box,ProcNumerico1);
}

/* Procesador del box de condición de emergencia */
/*************************************************/
void ProcNumJmpCondProg(NumericoJumpCond * num_box){
  ProgHandler(num_box,ProcNumJumpCond);  
}

/* Procesador del box de condición de emergencia */
/*************************************************/
void ProcTxtJmpCondProg(TextualJumpCond * txt_box){
  ProgHandler(txt_box,ProcTextJumpCond);  
}
#endif

/* Procesador de la pantalla principal */
/***************************************/
static bool show_main_text;  //VARIABLE GLOBAL!!!!!!!!!!!!
#ifdef pirani
static const char UF[]="UF  ";
static const char OF[]="OF  ";
#else
static const char UF[]=" UF ";
static const char OF[]=" OF ";
#endif

 #define DotNum0 (byte)get_Decimales(0)
#if  CANTIDAD_CANALES == 1
 #define DotNum1 (byte)get_Decimales(0)
#elif  CANTIDAD_CANALES == 2
 #define DotNum1 (byte)get_Decimales(1)
#endif

void MainHandler( NumericoJumpCond * num_box){

extern word Result[4];
extern int SetPoint[4];
extern bool Mostrar_Proc;
extern int ValFinal[4];					
 		
/* ejecuto si es la primera vez que se llama al manejador */

	if (FstTime){													 // es la primera vez que ingresa??
	ProcNumJumpCond(num_box);
#if  CANTIDAD_CANALES == 1
	if((int*)get_DirPar(0) == &SetPoint[0])
	  Valor_Tmp = get_ValParametro(numero_elemento,((TParametro *)num_box)->sDato);		
	else
	  Valor_Tmp = *(int *)get_DirPar(0);	
#endif
  Mostrar_Proc=TRUE;
	};
	
#if  CANTIDAD_CANALES == 1 && !defined(HD90)


// KeyEdgeS UP O DOWN
  if(get_Version()==VER_BL4  &&
  #ifdef _PROGRAMADOR
     get_Programa(0)==CONF_NO_PROGRAMA	 &&
  #endif
  (int *)get_DirPar(0) == &SetPoint[0] &&  
  ((Tecla=='u') || (Tecla=='d'))/* && !save_parametros*/){ // Fue presionada una Tecla UP o Down???
    
  	 #ifndef pirani	  
        procesar_up_down(Tecla,&Valor_Tmp);
        Pasar_Numero(Valor_Tmp,1,DotNum0); 	 
     #else	 
    	 if(get_Sensor(0)!=SENSOR_PIR){
    	  procesar_up_down(Tecla,&Valor_Tmp);
        Pasar_Numero(Valor_Tmp,1,DotNum0);
    	 }else{	  
    	  procesar_expo_up_down(Tecla,((TParametro *)num_box)->sDato,&Valor_Tmp);
        Pasar_Numero_Expo(Valor_Tmp,1,DotNum0);
    	 }
     #endif
    	  Grabacion_DelaySave(4000);							// Grabar parametros con delay
    	  set_ValParametro(Valor_Tmp,numero_elemento,((TParametro *)num_box)->sDato);
    	  	  
  }else{
        if (show_main_text==TRUE)
              PasarASCII(main_text,1);  // Mostrar DisplayInf
        else
              Mostrar_Proc=TRUE; // Mostrar Display Inf y Sup
     }
#endif

  #ifdef _COLADA_CALIENTE
  /* Setea en manual/auto */
    if(Tecla=='m'){
      if(CNTR_getModSal(0)==_MAN)
         set_SalControl(get_SalControl(0),0);
      else
         CNTR_setModSal(_MAN,0);
    }
  #endif

/* muestro en la pantalla superior e inferior */		

  if (Mostrar_Proc){										// Se actualizaron los valores??
    #if CANTIDAD_CANALES == 2	 && !defined(_SP_EXTERNO)
    Main_Mostrar2_canales();
    #else
    Main_Mostrar_canal();
    #endif

    Mostrar_Proc=FALSE;  								 // Sacar el flag de mostrar
  }
  
// T0QUES de salida
  if (Tecla=='r' || Tecla=='f'){ 
    if(!Fsh_to_save())   
      ProcNumJumpCond(num_box);				
	}
}


///////////////////////////Funciones internas /////////////
///////////////////////////////////////////////////////////
/*
** ===================================================================
**     Method      :  Mostrar_ifExpo (Modulo  Boxes)
**     Description :
**         Muestra el resultado de forma exponencial si el sensor actual es pirani,
**     y de modo normal en caso contrario   
**     Parameters  :
**           valor            - Valor a mostrar
**     Num_display            - Display en el que se van a mostrar el valor
**             Dot						- Posicion del punto decimal
**     
**      Returns     :
**         ---             - None
** ===================================================================
*/
void Mostrar_ifExpo(int valor,byte Num_display,byte Dot){
    #ifdef pirani
    if(get_Sensor(0)==SENSOR_PIR)
      Pasar_Numero_Expo(valor,Num_display,Dot);
    else
    #endif
      Pasar_Numero(valor,Num_display,Dot);						 //Mostrar Variable del Proceso

}

/*
** ===================================================================
**     Method      :  Main_check_range (Modulo  Boxes)
**     Description :
**         Checkea que el rango este entre el valor máximo del 
**         display(ej: 9999) y el mínimo(ej -1999)
**     Parameters  :
**           valor            - Valor a checkear
**         * error            - se modifica si *error si no esta en rango
**     
**      Returns     :
**         ---             - None
** ===================================================================
*/

void Main_check_range(int valor, byte * error ){

  if(*error!=ERR_OK){    
    if (valor>MAX_NUM_DISPLAY) 
      * error = ERR_OF;
    else if (valor<MIN_NUM_DISPLAY) 
			* error = ERR_UF;  
  }
}

/*
** ===================================================================
**     Method      :  set_MainText (Modulo  Boxes)
**     Description :
**         setea un mensaje(string) en el display inferior de la 
**     pantalla principal.
**         Un string vacio("") deshabilita que se muestre el mensaje
**     Parameters  :
**           str            - string (debe tener un largo máximo de 
**                            la cantidad de digitos del display )
**                            str="" deshabilita los mensajes
**     
**      Returns     :
**         ---             - None
** ===================================================================
*/

void set_MainText(const char * str){
    Main_setTextWMode(str,TEXT_FLASHING);
}

/*
** ===================================================================
**     Method      :  set_MainStaticText (Modulo  Boxes)
**     Description :
**         setea un mensaje(string) en el display inferior de la 
**     pantalla principal.
**         Un string vacio("") deshabilita que se muestre el mensaje
**     Parameters  :
**           str            - string (debe tener un largo máximo de 
**                            la cantidad de digitos del display )
**                            str="" deshabilita los mensajes
**     
**      Returns     :
**         ---             - None
** ===================================================================
*/

void set_MainStaticText(const char * str){
    Main_setTextWMode(str,TEXT_CONTINUOS);
}

/*
** ===================================================================
**     Method      :  Main_setTextMode (Modulo  Boxes)
**     Description :
**         seteado un mensaje, da el modo de mostrarlo,
**
**     Parameters  :  
**           str            - string (debe tener un largo máximo de 
**                            la cantidad de digitos del display )
**                            str="" deshabilita los mensajes
**          mod       - TEXT_FLASHING (switchea entre el texto y el valor del dpy inferior)
**                      TEXT_CONTINUOS (queda el texto fijo en el display inferior)     
** ===================================================================
*/

void Main_setTextWMode(const char * str,T_MainTextMode mod){
byte i;
  for(i=0;(str[i]!='\0') && i<4;i++)
    main_text[i]=str[i];
  if(i==0){
    (void)Timer_Terminate(&show_main_text);
    show_main_text=FALSE;
  }else{
    main_text[i]='\0';
  
    if(mod == TEXT_FLASHING){
      show_main_text=TRUE;
      TimerRun(MAIN_TEXT_PERIOD,&show_main_text,CONTINUO_TOG,NULL);  
    }else{
      Timer_Terminate(&show_main_text);
      show_main_text=TRUE;
    }
  }
}


#pragma INLINE
void Main_Mostrar2_canales(void){
extern word Result[4];
extern int ValFinal[4];
byte i;  
  for(i=0;i<CANTIDAD_CANALES;i++){							 // Recorrer todos los canales
    Main_check_range(ValFinal[i],&Result[i]);

    if (Result[i]==ERR_OK){  							 // El REsultado de la linealización fue OK??
      Mostrar_ifExpo(ValFinal[i],i,get_Decimales(i));						 //Mostrar Variable del Proceso
    }
    else if (Result[i]==ERR_UF)					 // El REsultado de la linealización fue UF??
    PasarASCII((char *)UF,i);							 // Mostrar UF
    else if (Result[i]==ERR_OF)					 // El REsultado de la linealización fue OF??
    PasarASCII((char *)OF,i);							 // Mostrar OF
  }
 if (show_main_text==TRUE)
    PasarASCII(main_text,1);  // Mostrar DisplayInf
}

#pragma INLINE
void Main_Mostrar_canal(void){
extern word Result[4];
extern int ValFinal[4];
extern int SetPoint[4];
  
  /* Veo si se está fuera de rango */
  Main_check_range(ValFinal[0],&Result[0]);
  
  /*  Muestro Display Superior */
	if (Result[0]==ERR_UF)					 // El Resultado de la linealización fue UF??
    PasarASCII((char *)UF,0);							 // Mostrar UF
  else if (Result[0]==ERR_OF)					 // El REsultado de la linealización fue OF??
    PasarASCII((char *)OF,0);							 // Mostrar OF
  /*  Muestro Variable?*/
  else if (Result[0]==ERR_OK){  							 // El REsultado de la linealización fue OK??
    Mostrar_ifExpo(ValFinal[0],0,DotNum0);
  }

  /*  Muestro Display Inferior */
  if(
    #ifdef _PROGRAMADOR
    get_Programa(0)==CONF_NO_PROGRAMA && 
    #endif
    (int *)get_DirPar(0)==&SetPoint[0])
  {
    Mostrar_ifExpo(Valor_Tmp,1,DotNum1); // Mostrar DisplayInf
  }else{
    Mostrar_ifExpo(*(int *)get_DirPar(0),1,DotNum1);
  }
}

void procesar_up_down(byte tecla,int * valor_tmp){
int itmp=* valor_tmp;
/* proceso Tecla UP */
	if (tecla=='u'){									 // Fue presionada una Tecla UP ???
		    if (itmp<LimSup) itmp++; // El Buffer es menor que el LimiteSup?? Si-> Incrementar Buffer
				else itmp=LimSup;						 // No-> Poner Buffer en maximo valor
				
	};
	
	/* proceso Tecla down */
	if (tecla=='d'){		  					      // Fue presionada una Tecla Down???
				if (itmp>LimInf) itmp--;		// El Buffer es mayor que el LimiteInf?? Si-> Decrementar Buffer
				else itmp=LimInf;	// No-> Poner Buffer en el minimo valor			
				
		};
	* valor_tmp=itmp;
}

#ifdef pirani
void procesar_expo_up_down(byte tecla,int * valor_tmp){
  	  int sumador,div;  
      int valor = * valor_tmp;

	    if(get_Sensor(0)==SENSOR_PIR){
        for(div=1;(valor/div)>0;div*=10);
        if(div>1)
          div/=10;
        if(div>1)
          div/=10;
        if(((valor)/(div*10))==1 && ((valor)%(div*10))==0 && (div>=10) && tecla=='d')
          div/=10;
        sumador=div;
	    }
	    /* proceso Tecla UP */
	    if (tecla=='u'){									 // Fue presionada una Tecla UP ???
		    if (* valor_tmp+sumador<LimSup) * valor_tmp+=sumador; // El Buffer es menor que el LimiteSup?? Si-> Incrementar Buffer
				else * valor_tmp=LimSup;						 // No-> Poner Buffer en maximo valor
	    };
	    /* proceso Tecla down */
	    if (tecla=='d'){		  					      // Fue presionada una Tecla Down???
				if (* valor_tmp-sumador>LimInf) * valor_tmp-=sumador;		// El Buffer es mayor que el LimiteInf?? Si-> Decrementar Buffer
				else  * valor_tmp=LimInf;	// No-> Poner Buffer en el minimo valor			
		  };  
}
#endif

void Exit(void){	// Funcion Boton de Exit 
  Box_set_new((PunteroF)&Principal1);
}

void set_proximo(PunteroF proximo){
  if ((proximo)!=NULL)		 // Se cargo un box existente???
		{ 
  		prepare_proximo();
  		numero_elemento=0;
  		PtrTmp=proximo;				 //Cargar puntero a la funcion correspondiente (TitleHandler, NumHandler, etc.)
		}
}



/******************************************************
**        FUNCIONES DE BOXES PARA CANAL VARIABLE     **
/******************************************************/ 
#ifdef _BUTTON_CHANEL_HMI 

///////////////////////////////////
byte canalaMostrar;



/* Cambia el canal a mostrar */
/*****************************/
void Boxes_change_chan(void) {
  canalaMostrar++;
  if(canalaMostrar>CANTIDAD_CANALES-1) 
    canalaMostrar=0;   
}
#endif