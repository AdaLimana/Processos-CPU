

/* 
 * File:   main.c
 * Author:  Adair
 *
 * Created on 03 de Março de 2016, 10:14
 */

#include <stdio.h>
#include "CPU.h"

void imprimeTabela(processo *p, int qnt);
void imprimeResultados(CPU *x, int qnt);
void legenda();

int main() {
    srand(time(NULL));
    int qntProcesso;
    int incremento;
    CPU a;
    
    printf("\nInforme a quantidade de processos\n");
    scanf("%d",&qntProcesso);
    
    printf("\nInforme o tempo de criacao de um processo par o outro\n");
    scanf("%d",&incremento);
    
    if(!inicializaProcesso(&a,qntProcesso,incremento)){
        printf("\nNão ha espaco na memoria\n");
        return 0;
    } 
    
    imprimeTabela(a.listaProcesso, qntProcesso);
    
    imprimeResultados(&a, qntProcesso);
    
    free(a.listaProcesso);
    
    return (0);
}

/*
  Imprime a tabela dos processos
*/
void imprimeTabela(processo *p, int qnt){

    int i=0;
    legenda();
    printf("\n||PID||TCP||TEC||TEX||TSC||TEF||TOC||\n");
    while(i<qnt){
        printf("||%3d||%3d||%3d||%3d||%3d||%3d||%3d||\n",
        p[i].PID,p[i].TCP,p[i].TEC,p[i].TEX,p[i].TSC,p[i].TEF,p[i].TOC);
        i++;
    } 

}

/*
  Imprime os dados da CPU apos a
  execucao de todos os processos
*/
void imprimeResultados(CPU *x, int qnt){

    printf("\nTempo medio em fila = %f\n",tempoMedioFila(x, qnt));
    printf("Tempo medio de execucao = %f\n", tempoMedioExecucao(x, qnt));
    printf("Tempo ocioso da CPU = %d\n", tempoOcioso(x, qnt));
}

/*
  Legenda das colunas da tabela
*/
void legenda(){
    
    printf("\n#######################################3#############\n");
    printf("# PID (Identificacao)   TCP (Tempo criacao processo)#\n");
    printf("# TEX (Tempo execucao)  TEC (Tempo entrada CPU)     #\n");
    printf("# TES (Tempo saida CPU)   TEF (Tempo espera fila)   #\n");
    printf("# TOC (Tempo ocioso do processador)                 #\n");
    printf("#######################################3#############\n");

}
