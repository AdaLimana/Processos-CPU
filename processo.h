/*
 *Arquivo .h que implementa uma strutura de dados do tipo (processo) 
 */

/* 
 * File:   processo.h
 * Author: Adair
 * 
 *
 * Created on 01 de Março de 2016, 23:30
 */

typedef struct{
    int PID; /* Número de identificação do processo*/
    int TCP; /* Tempo de criação do processo*/
    int TEC; /* Tempo de entrada na CPU*/
    int TEX; /* Tempo de execução*/
    int TSC; /* Tempo de saída da CPU*/
    int TEF; /* Tempo de espera na fila*/
    int TOC; /* Tempo de ocilação da CPU*/
}processo;
