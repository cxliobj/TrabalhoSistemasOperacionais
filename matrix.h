#ifndef MATRIX_HPP
#define MATRIX_HPP
#define position(I, J, DIMENSION) ((I)*(DIMENSION) + (J))

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "errorMessages.h"
#include "resources.h"

/**
 *  Item por item e lido no arquivo e guardado na respectiva matrix alocada dinamicamente, ate que se encontre um EOF 
**/
void* matrix_transcribe(void* parameters_ref);

/**
 *  Item por item e lido no arquivo e guardado na respectiva matrix alocada dinamicamente, ate que se encontre um EOF 
**/
void* matrix_write(void* parameters_ref);

/** 
 * A soma e feita pelo algoritmo classico: cada item no indice "i" das repectivas matrizes sao somados e o resultado e guardado numa terceira matriz 
**/
void* matrix_sum(void* parameters_ref);

void* matrix_multiplication(void* parameters_ref);

void* matrix_reduce(void* parameters_ref);

void sum(Matrix** matrix, int dimension, int num_threads);

void multiply(Matrix** matrix, int dimension, int num_threads);

long long int reduce(Matrix** matrix, int dimension, int num_threads);

#endif