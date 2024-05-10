#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "errorMessages.h"
#include "resources.h"

#define position(I, J, DIMENSION) ((I)*(DIMENSION) + (J))

    void* transcribeMatrix (void* matrix_ref);

    void* writeMatrix (void* matrix_ref);

    void* thrdSomaParcial(void* parameters_ref);

    void sumMatrix(long long int* array1, long long int* array2, long long int* array3, long long dimension, long long int num_threads);

    void* multiplyMatrix (void* matrix_ref);

    void* reduceMatrix (void* matrix_ref);

#endif