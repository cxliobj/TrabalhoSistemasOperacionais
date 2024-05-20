#ifndef THREADS_HPP
#define THREADS_HPP

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

void sum(Matrix** matrix, int dimension, int num_threads);

void multiply(Matrix** matrix, int dimension, int num_threads);

long long int reduce(Matrix** matrix, int dimension, int num_threads);

#endif