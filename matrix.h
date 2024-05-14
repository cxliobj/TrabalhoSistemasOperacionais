#ifndef MATRIX_HPP
#define MATRIX_HPP
#define position(I, J, DIMENSION) ((I)*(DIMENSION) + (J))

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "errorMessages.h"
#include "resources.h"

void* matrix_transcribe (void* parameters_ref);

void* init_transcribe (FILE* fileArray, long long int* array1, int dimension, int num_threads);

// ****************************************************************

void* matrix_write (void* parameters_ref);

void* init_write (FILE* fileArray, long long int* array1, int dimension, int num_threads);

// ****************************************************************

void* matrix_sum (void* parameters_ref);

void* init_sum (long long int* array1, long long int* array2, long long int* array3, int dimension, int num_threads);

// ****************************************************************

void* matrix_multiplication (void* parameters_ref);

void* init_multiplication (long long int* array1, long long int* array2, long long int* array3, int dimension, int num_threads);

// ****************************************************************

void* matrix_reduce (void* parameters_ref);

void* init_reduce (long long int* array1, int dimension, int num_threads);

// ****************************************************************

void end_1 (void* ptr, int num_threads);

void end_2 (void* ptr, int num_threads);

long long int end_3 (void* ptr, int num_threads);

#endif