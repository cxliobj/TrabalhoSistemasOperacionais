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

FILE* openFile(char* file_name)
{
    FILE* file = fopen(file_name, "r+");
    verify_open_file(file);
    return file;
}

long long int* newArray(int dimension)
{
    verify_allocation_memory_size(dimension);
    long long int* array = (long long int*) malloc(dimension * dimension * sizeof(long long int));
    verify_allocation_memory(array);
    return array;
}

Matrix* newMatrix(char* file_name, int dimension)
{
    verify_allocation_memory_size(dimension);
    Matrix* matrix = (Matrix*) malloc(sizeof(Matrix));
    verify_allocation_memory(matrix);
    matrix->fileArray = openFile(file_name);
    matrix->array = newArray(dimension);
    matrix->dimension = dimension;
    return matrix;
}

pthread_t* newThreadIDs(int num_threads)
{
    verify_allocation_memory_size(num_threads);
    pthread_t *threadIDs = (pthread_t*) malloc(num_threads * sizeof(pthread_t));
    verify_allocation_memory(threadIDs);
    return threadIDs;
}

ThreadParameters* newThreadParameters(int num_threads)
{
    verify_allocation_memory_size(num_threads);
    ThreadParameters* parameters = (ThreadParameters*) malloc(num_threads * sizeof(ThreadParameters));
    verify_allocation_memory(parameters);
    return parameters;
}