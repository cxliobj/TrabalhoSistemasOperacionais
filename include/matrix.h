#ifndef MATRIX_HPP
#define MATRIX_HPP
#define position(I, J, DIMENSION) ((I)*(DIMENSION) + (J))

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/errorMessages.h"
#include "../include/resources.h"

/**
 * A função matrix_transcribe lê um arquivo com uma matriz (tipo long long int) e guarda item a item em um array, 
 * até que se encontre um EOF.
 * 
 * PARÂMETROS: Matrix* (aka. typedef struct Matrix*)
**/
void* matrix_transcribe(void* matrix_ref);

/**
 * A função matrix_write utiliza um array e guarda item por item em um arquivo, no formato MxN.
 * 
 * PARÂMETROS: Matrix* (aka. typedef struct Matrix*) 
**/
void* matrix_write(void* matrix_ref);

/** 
 * A função matrix_sum faz a soma inteira ou parcial de duas matrizes se utlizando do 
 * algoritmo clássico: cada item no índice "i" das repectivas matrizes são somados e o 
 * resultado é guardado numa terceira matriz.
 * 
 * PARÂMETROS: ThreadParameters* (aka. typedef struct ThreadParameters*) 
**/
void* matrix_sum(void* parameters_ref);

/**
 * A  função matrix_multiplication é um algoritmo de multiplicação de matrizes 
 * otimizado para multi-thread.
 * 
 * PARÂMETROS: ThreadParameters* (aka. typedef struct ThreadParameters*)
**/
void* matrix_multiplication(void* parameters_ref);

/**
 * A função matrix_reduce soma item a item por todo o array para retornar um void* 
 * mascarado de long long int*.
 * 
 * PARÂMETROS: ThreadParameters* (aka. typedef struct ThreadParameters*)
**/
void* matrix_reduce(void* parameters_ref);

#endif