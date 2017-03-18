/*
 * Arquivo .h que implementa uma strutura de dados do tipo (CPU)
 */
/* 
 * File:   CPU.h
 * Author:  Adair
 *
 * Created on 01 de MArço de 2016, 23:44
 */
#include "processo.h"
#include <stdlib.h>
#include <time.h>

typedef struct{
    processo *listaProcesso;
    float tempoMedioFila; /*armazena o tempo médio dos processos em fila*/
    float tempoMedioExec; /*armazena tempo medio em execução*/
    int tempoOcioso; /*armazena o tempo em que a CPU fica ociosa*/
}CPU;

/*
  Inicializa todos os processos e
  os armazena na (listaProcesso)  
*/
int inicializaProcesso(CPU *x, int qntProcesso, int incremento){
    
    int i=0;
    int valor=0;
    
    /*Aloca para listaProcesso um vetor de tamanho qntProcesso*/
    processo *p = malloc(qntProcesso*sizeof(processo));
   
    if(!p){/*Caso malloc falhar ele retorna zero*/
        return 0;
    }
    
    while(i<qntProcesso){
        
        p[i].PID = i+1;/*Gera os PID de cada processo*/
        
        if(!i){
            valor = 1;/*Caso for o primeiro processo o tempo de Geração é 1*/
            p[i].TEC = 1; /*E o tempo de entrada também é um*/
            p[i].TOC = 1; /*Tempo ocioso é um*/
            p[i].TEF = 0; /*E o tempo de fila é zero*/
            tempoCriacao(&p[i],valor);
        }
        else{
            valor= valor+incremento;
            tempoCriacao(&p[i],valor);
            tempoEntrada(&p[i-1],&p[i]);
        }
        tempoExecucao(&p[i]);
        tempoSaida(&p[i]);
        i++;
    }
 
   
    x->listaProcesso = p;
    return 1;
}

/*
  Determina o tempo de criacao do processo
*/
void tempoCriacao(processo *x, int incremento){
    x->TCP = incremento;
}

/*
  Determina o aleatoriamente (5 a 10)
  o tempo de execucao do processo
*/
void tempoExecucao(processo *x){    
    x->TEX = (rand()%6)+5;
}

/*Determina o tempo de entrada, do 
processo, na CPU*/

void tempoEntrada(processo *anterior, processo *atual ){

    if(anterior->TSC >= atual->TCP){    
        atual->TEC = anterior->TSC; 
        atual->TEF = anterior->TSC -atual->TCP;
        atual->TOC =0;     
    }                               
    else{					/*Se o processo anterior terminar antes */
        atual->TEC = atual->TCP;		/*do atual ser criado, o processo só    */    	
        atual->TOC = atual->TCP-anterior->TSC;	/* entrará em execução quando for criado*/
        atual->TEF = 0;				/*e a CPU ficará um tempo ocioso, e seu */
    }						/*tempo de fila será zero*/	
}

/*
  Determina o tempo de saida do processo,
  o qual se da pela soma do TEC (tempo 
  entra na CPU) e TEX (tempo de execucao) 
*/
void tempoSaida(processo *x){
 
    x->TSC = x->TEC + x->TEX;

}

/*
  Determina o tempo medio de fila dos
  processos
*/
float tempoMedioFila(CPU *x, int qnt){
    int i=0;
    processo *p = x->listaProcesso;
    x->tempoMedioFila = 0; 
    while(i<qnt){
        x->tempoMedioFila = x->tempoMedioFila + p[i].TEF;
        i++;
    }
    x->tempoMedioFila = x->tempoMedioFila/qnt;
    return x->tempoMedioFila;
}

/*
  Determina o tempo medio de execucao
  da CPU
*/
float tempoMedioExecucao(CPU *x, int qnt){
    int i=0;
    processo *p = x->listaProcesso;
    x->tempoMedioExec = 0;
    while(i<qnt){
        x->tempoMedioExec = x->tempoMedioExec+p[i].TEX;
        i++;
    }
    x->tempoMedioExec = x->tempoMedioExec/qnt;
    return x->tempoMedioExec;
}

/*
  Determina o tempo Ocioso da CPU
*/
int tempoOcioso(CPU *x, int qnt){
    int i=0;
    processo *p = x->listaProcesso;
    x->tempoOcioso = 0;
    while(i<qnt){
        x->tempoOcioso = x->tempoOcioso + p[i].TOC;
        i++;
    }
    return x->tempoOcioso;

}
