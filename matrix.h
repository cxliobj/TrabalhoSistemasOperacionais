#ifndef MATRIX_HPP
#define MATRIX_HPP
#define position(I, J, DIMENSION) ((I)*(DIMENSION) + (J))
#define NUM_THREADS_LEITURA 1
#define NUM_THREADS_GRAVACAO 1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "errorMessages.h"
#include "resources.h"

void* matrix_transcribe (void* parameters_ref);

void* init_transcribe (FILE* fileArray, long long int* array1, int dimension, int num_threads);

void end_transcribe (void* thread_ids, int num_threads);

// ****************************************************************

void* matrix_write (void* parameters_ref);

void* init_write (FILE* fileArray, long long int* array1, int dimension, int num_threads);

void end_write (void* tids, int num_threads);

// ****************************************************************

void* matrix_sum (void* parameters_ref);

void thread_matrix_sum (long long int* array1, long long int* array2, long long int* array3, int dimension, int num_threads);

void* matrix_multiplication (void* parameters_ref);

void thread_matrix_multiplication (long long int* array1, long long int* array2, long long int* array3, int dimension, int num_threads);

void* matrix_reduce (void* parameters_ref);

long long int thread_matrix_reduce (long long int* array1, int dimension, int num_threads);

#endif