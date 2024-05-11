#include "resources.h"

pthread_t* newThreadIDs(int num_threads)
{
    show_error_size_allocation_memory(num_threads);
    pthread_t *threadIDs = (pthread_t*) malloc(num_threads * sizeof(pthread_t));
    show_error_allocation_memory(threadIDs);
    return threadIDs;
}

ThreadParameters* newThreadParameters (int num_threads)
{
    show_error_size_allocation_memory(num_threads);
    ThreadParameters* parameters = (ThreadParameters*) malloc(num_threads * sizeof(ThreadParameters));
    show_error_allocation_memory(parameters);
    return parameters;
}

long long int* newMatrix (long long int dimension)
{
    show_error_size_allocation_memory(dimension);
    long long int* vector = (long long int*) calloc (dimension * dimension, sizeof(long long int));
    show_error_allocation_memory(vector);
    return vector;
}

FILE* openFile(char* argv_file_matrix)
{
    FILE* file = fopen(argv_file_matrix, "r+");
    show_error_open_file(file);
    return file;
}

int stringToInt (char* argv) 
{
    char *endPtr;
    long int number = strtol(argv, &endPtr, 10);

    if (!*endPtr)
    {
        return number;
    }
    else
    {
        printf("Conversao stringToInt falhou.\n");
        exit(EXIT_FAILURE);
    }
}
