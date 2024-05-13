#include "resources.h"

pthread_t* newThreadIDs(int num_threads)
{
    verify_allocation_memory_size(num_threads);
    pthread_t *threadIDs = (pthread_t*) malloc(num_threads * sizeof(pthread_t));
    verify_allocation_memory(threadIDs);
    return threadIDs;
}

ThreadParameters* newThreadParameters (int num_threads)
{
    verify_allocation_memory_size(num_threads);
    ThreadParameters* parameters = (ThreadParameters*) malloc(num_threads * sizeof(ThreadParameters));
    verify_allocation_memory(parameters);
    return parameters;
}

long long int* newMatrix (long long int dimension)
{
    verify_allocation_memory_size(dimension);
    long long int* vector = (long long int*) calloc (dimension * dimension, sizeof(long long int));
    verify_allocation_memory(vector);
    return vector;
}

FILE* openFile(char* argv_file_matrix)
{
    FILE* file = fopen(argv_file_matrix, "r+");
    verify_open_file(file);
    return file;
}

int stringToInt (char* str) 
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

    return number;
}
