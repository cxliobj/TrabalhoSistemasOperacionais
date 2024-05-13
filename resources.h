#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include "errorMessages.h"

    typedef struct ThreadParameters
    {
        FILE* fileArray;
        long long int* array1;
        long long int* array2;
        long long int* array3;
        int dimension;
        int idx_start;
        int idx_final;
    } ThreadParameters;

    pthread_t* newThreadIDs(int num_threads);

    ThreadParameters* newThreadParameters (int num_threads);

    long long int* newMatrix (long long int dimension);

    FILE* openFile(char* argv_file_matrix);

    int stringToInt (char* argv);

#endif