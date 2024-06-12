#ifndef THREADS_H
#define THREADS_H

/**
 * MatrizA: matriz[0] 
 * MatrizB: matriz[1]
 * MatrizC: matriz[2]
 * MatrizD: matriz[3]
 * MatrizE: matriz[4]
**/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/errorMessages.h"
#include "../include/resources.h"
#include "../include/matrix.h"

void passo_1 (Matrix** matrix, int num_threads); //nome temporario

void sum(Matrix** matrix, int dimension, int num_threads);

void passo_3 (Matrix** matrix, int num_threads); //nome temporario

void multiply(Matrix** matrix, int dimension, int num_threads);

long long int reduce(Matrix** matrix, int dimension, int num_threads);

#endif