#ifndef RESOURCES_H
#define RESOURCES_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include "../include/errorMessages.h"

typedef struct Matrix
{
    FILE* fileArray;
    long long int* array;
    int dimension;
} Matrix;

typedef struct Parameters
{
    long long int* array1;
    long long int* array2;
    long long int* array3;
    int dimension;
    int idx_start;
    int idx_final;
} Parameters;

/**
 * Converte uma string em um número inteiro.
 * @param argv_number Número em formato char* obtido da matriz argv.
 * @return Número inteiro convertido para int.
**/
int stringToInt(char* argv_number);

/**
 * Abre um arquivo no modo leitura e escrita (r+).
 * @param file_name Nome do arquivo.
 * @return Ponteiro do tipo arquivo (FILE*).
 * @throw Retorna 2 se o arquivo não puder ser aberto, junto com uma mensagem de erro.
**/
FILE* openFile(char* file_name);

/**
 * Cria dinamicamente um vetor.
 * @param dimension Tamanho da matriz.
 * @return Ponteiro do tipo long long int.
 * @throw Retorna 2 se a alocação falhar, junto com uma mensagem de erro.
**/
long long int* newArray(int dimension);

/**
 * Cria dinamicamente uma estrutura do tipo Matrix*.
 * @param file_name Nome do arquivo associado a estrutura.
 * @param dimension Tamanho do array associado a estrutura.
 * @return Ponteiro do tipo Matrix (Matrix*).
 * @throw Retorna 2 se a alocação falhar, junto com uma mensagem de erro.
**/
Matrix* newMatrix(char* file_name, int dimension);

/**
 * Cria um vetor dinamicamente comentendo IDs de threads.
 * @param num_threads Tamanho do vetor
 * @return Vetor contendo os IDs.
 * @throw Retorna 2 se a alocação falhar, junto com uma mensagem de erro.
**/
pthread_t* newThreadIDs(int num_threads);

/**
 * Cria dinamicamente uma estrutura do tipo Parameters*.
 * @param file_name Nome do arquivo associado a matriz
 * @param dimension Tamanho do vetor de parâmetros
 * @return Ponteiro do tipo Parameters
 * @throw Retorna 2 se a alocação falhar, junto com uma mensagem de erro.
**/
Parameters* newParameters(int num_threads);

#endif