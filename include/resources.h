#ifndef RESOURCES_H
#define RESOURCES_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include "../include/errorMessages.h"

/**
 * A estrutura Matrix guarda os dados básicos iniciais que cada matriz deve ter: arquivo, vetor e ordem.
**/
typedef struct Matrix
{
    FILE* fileArray;
    long long int* array;
    int dimension;
} Matrix;

/**
 * A estrutura Parameters possui os parâmetros necessários para uma execução multi-thread das
 * funções soma, multiplicação e redução.
 * Estes dados serão os argumentos repassado ao pthread_create.
**/
typedef struct Parameters
{
    long long int* array1;
    long long int* array2;
    long long int* array3;
    int dimension;
    int start_pos;
    int final_pos;
} Parameters;

/**
 * Converte uma string em um número inteiro.
 * @param argv_number Número em formato char* obtido do ponteiro argv
 * @return Número inteiro convertido para int.
 * @throw Retorna 1 se a conversão da string falhou, junto com uma mensagem de erro.
**/
int stringToInt(char* argv_number);

/**
 * Abre um arquivo no modo leitura e escrita (r+).
 * @param file_name Nome do arquivo
 * @return Ponteiro do tipo arquivo (FILE*).
**/
FILE* openFile(char* file_name, char* file_mode);

/**
 * Cria dinamicamente um vetor.
 * @param dimension Ordem da matriz
 * @return Ponteiro do tipo long long int.
**/
long long int* newArray(int dimension);

/**
 * Cria dinamicamente uma estrutura do tipo Matrix*.
 * @param file_name Nome do arquivo associado a estrutura
 * @param dimension Tamanho do array associado a estrutura
 * @return Ponteiro do tipo Matrix (Matrix*).
**/
Matrix* newMatrix(char* file_name, char* file_mode, int dimension);

/**
 * Cria um vetor dinamicamente comentendo IDs de threads.
 * @param num_threads Tamanho do vetor
 * @return Ponteiro do tipo.
**/
pthread_t* newThreadIDs(int num_threads);

/**
 * Cria dinamicamente uma estrutura do tipo Parameters*.
 * @param file_name Nome do arquivo associado a matriz
 * @param dimension Tamanho do vetor de parâmetros
 * @return Ponteiro do tipo Parameters (Parameters*).
**/
Parameters* newParameters(int num_threads);

#endif