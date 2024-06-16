#include "../include/resources.h"

int stringToInt(char* str) 
{
    char *endptr;
    errno = 0;
    long int number = strtol(str, &endptr, 10);

    if (errno != 0)
    {
        perror("strtol");
        exit(EXIT_FAILURE);
    }
    if (endptr == str) {
        fprintf(stderr, "No digits were found\n");
        exit(EXIT_FAILURE);
    }
    return ((int) number);
}

FILE* openFile(char* file_name, char* file_mode)
{
    FILE* file = fopen(file_name, file_mode);
    verify_open_file(file, file_name);
    return file;
}

long long int* newArray(int dimension)
{
    long long int* array = (long long int*) calloc(dimension * dimension, sizeof(long long int));
    verify_allocation_memory(array);
    return array;
}

Matrix* newMatrix(char* file_name, char* file_mode, int dimension)
{
    Matrix* matrix = (Matrix*) malloc(sizeof(Matrix));
    verify_allocation_memory(matrix);
    matrix->fileArray = openFile(file_name, file_mode);
    matrix->array = newArray(dimension);
    matrix->dimension = dimension;
    return matrix;
}

pthread_t* newThreadIDs(int num_threads)
{
    pthread_t *threadIDs = (pthread_t*) malloc(num_threads * sizeof(pthread_t));
    verify_allocation_memory(threadIDs);
    return threadIDs;
}

Parameters* newParameters(int num_threads)
{
    Parameters* parameters = (Parameters*) malloc(num_threads * sizeof(Parameters));
    verify_allocation_memory(parameters);
    return parameters;
}