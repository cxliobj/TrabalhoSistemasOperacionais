#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include "../include/errorMessages.h"

    typedef struct Matrix
    {
        FILE* fileArray;
        long long int* array;
        int dimension;
    } Matrix;

    typedef struct ThreadParameters
    {
        long long int* array1;
        long long int* array2;
        long long int* array3;
        int dimension;
        int idx_start;
        int idx_final;
    } ThreadParameters;

    int stringToInt(char* argv);
    
    FILE* openFile(char* file_name);
    
    long long int* newArray(int dimension);
    
    Matrix* newMatrix(char* file_name, int dimension);

    pthread_t* newThreadIDs(int num_threads);

    ThreadParameters* newThreadParameters(int num_threads);

#endif