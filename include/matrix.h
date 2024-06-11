#ifndef MATRIX_H
#define MATRIX_H
#define position(I, J, DIMENSION) ((I)*(DIMENSION) + (J))

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/errorMessages.h"
#include "../include/resources.h"

/**
 * A função matrix_transcribe lê um arquivo de uma matriz com números inteiros 
 * e guarda item a item em um array, até que se encontre um EOF.
 * 
 * @param matrix_ref Matrix* (aka. typedef struct Matrix*)
 * @return não há retorno (NULL)
**/
void* matrix_transcribe(void* matrix_ref);

/**
 * A função matrix_write utiliza um array e guarda item por item em um arquivo, no formato MxN.
 * 
 * @param matrix_ref Matrix* (aka. typedef struct Matrix*)
 * @return não há retorno (NULL)
**/
void* matrix_write(void* matrix_ref);

/** 
 * A função matrix_sum faz a soma inteira ou parcial de duas matrizes se utlizando do 
 * algoritmo clássico: cada item no índice "i" das repectivas matrizes são somados e o 
 * resultado é guardado numa terceira matriz.
 * 
 * @param parameters_ref ThreadParameters* (aka. typedef struct ThreadParameters*)
 * @return não há retorno (NULL)
**/
void* matrix_sum(void* parameters_ref);

/**
 * A  função matrix_multiplication é um algoritmo de multiplicação de matrizes 
 * otimizado para multi-thread.
 * 
 * @param parameters_ref ThreadParameters* (aka. typedef struct ThreadParameters*)
 * @return não há retorno (NULL)
**/
void* matrix_multiplication(void* parameters_ref);

/**
 * A função matrix_reduce soma item a item por todo o array para retornar um void* 
 * mascarado de long long int*.
 * 
 * @param parameters_ref ThreadParameters* (aka. typedef struct ThreadParameters*)
 * @return há retorno de um número inteiro (long long int)
**/
void* matrix_reduce(void* parameters_ref);

#endif