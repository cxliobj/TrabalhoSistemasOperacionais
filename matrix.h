#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define position(I, J, DIMENSION) ((I)*(DIMENSION) + (J))

    typedef struct Matrix
    {
        FILE* fileArray;
        long long int* array;
        long long int dimension;
    } Matrix;

    Matrix* newMatrix ();

    long long int* vectorAllocation(long long int dimension);

    FILE* openFile(char* argv_file_matrix);

    void* transcribeMatrix (void* matrix_ref);

    void* writeMatrix (void* matrix_ref);

    void* sumMatrix(void* matrix_ref);

    void* multiplyMatrix (void* matrix_ref);

    void* reduceMatrix (void* matrix_ref);

#endif