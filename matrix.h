#include <stdio.h>
#include <stdlib.h>

#ifndef MATRIX_HPP

    #define MATRIX_HPP

    #define position(I, J, DIMENSION) ((I)*(DIMENSION) + (J))

    typedef struct Matrix 
    {
        FILE* fileArray;
        int* array;
        int dimension;
        long long reduction;
    } Matrix;

    Matrix* newMatrix (int dimension, FILE* argv_file_matrix);

    void sumMatrix (Matrix* matrix1, Matrix* matrix2, Matrix* matrix3);

    void multiplyMatrix (Matrix* matrix1, Matrix* matrix2, Matrix* matrix3);

    void transcribeMatrix (Matrix* matrix);

    void writeMatrix (Matrix* matrix);

    void reduceMatrix (Matrix* matrix);

    #endif
