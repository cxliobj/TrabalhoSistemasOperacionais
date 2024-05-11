#ifndef MATRIX_HPP
#define MATRIX_HPP
#define position(I, J, DIMENSION) ((I)*(DIMENSION) + (J))

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "errorMessages.h"
#include "resources.h"

    void* threadtranscribeMatrix (void* parameters_ref);

    void transcribeMatrix (long long int* array1, FILE* fileArray, long long int dimension);

    void* threadWriteMatrix (void* parameters_ref);

    void writeMatrix (long long int* array1, FILE* fileArray, long long int dimension);

    void* threadPartialSum(void* parameters_ref);

    void sumMatrix(long long int* array1, long long int* array2, long long int* array3, long long dimension, long long int num_threads);

    void* threadPartialMulti (void* parameters_ref);

    void multiplyMatrix(long long int* array1, long long int* array2, long long int* array3, long long dimension, long long int num_threads);

    void* threadReduceMatrix (void* parameters_ref);

    long long int reduceMatrix (long long int* array1, long long dimension, long long int num_threads);

#endif