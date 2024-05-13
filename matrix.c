#include "matrix.h"

void* matrix_transcribe (void* parameters_ref)
{
    ThreadParameters* parameters = (ThreadParameters*) parameters_ref;
    FILE* fileArray = parameters->fileArray;
    long long int* array = parameters->array1;
    long long int finput;
    register unsigned int i = 0;

    while (fscanf(fileArray, "%lld", &finput) != EOF)
    {
        array[i] = finput;
        i++;
    }
    fclose(fileArray);
    pthread_exit(parameters);
}

void thread_matrix_transcribe (FILE* fileArray, long long int* array, int dimension)
{
    ThreadParameters* parameters = newThreadParameters(1);
    pthread_t* thread_ids = newThreadIDs(1);
    parameters[0].fileArray = fileArray;
    parameters[0].array1 = array;
    parameters[0].dimension = dimension;

    int thread = pthread_create(&thread_ids[0], NULL, matrix_transcribe, (void*) &parameters[0]);
    verify_thread_create(thread);

    thread = pthread_join(thread_ids[0], NULL);
    verify_thread_join(thread);

    free(parameters);
    free(thread_ids);
}

void* matrix_write (void* parameters_ref)
{
    ThreadParameters* parameters = (ThreadParameters*) parameters_ref;
    FILE* fileArray = parameters->fileArray;
    long long int* array = parameters->array1;
    register unsigned int dimension = parameters->dimension;
    register unsigned int i, j;

    for (i = 0; i < dimension; i++)
    {
        for (j = 0; j < dimension; j++)
        {
            fprintf(fileArray, "%lld ", array[(position(i, j, dimension))]);
        }
        fprintf(fileArray, "\n");
    }
    fclose(fileArray);
    pthread_exit(NULL);
}

void thread_matrix_write (FILE* fileArray, long long int* array, int dimension)
{
    ThreadParameters* parameters = newThreadParameters(1);
    pthread_t* thread_ids = newThreadIDs(1);
    parameters[0].fileArray = fileArray;
    parameters[0].array1 = array;
    parameters[0].dimension = dimension;
    
    int thread = pthread_create(&thread_ids[0], NULL, matrix_write, (void*) &parameters[0]);
    verify_thread_create(thread);

    thread = pthread_join(thread_ids[0], NULL);
    verify_thread_join(thread);

    free(parameters);
    free(thread_ids);
}

void* matrix_sum (void* parameters_ref)
{
    ThreadParameters* parameters = (ThreadParameters*) parameters_ref;
    long long int* array1 = parameters->array1;
    long long int* array2 = parameters->array2;
    long long int* array3 = parameters->array3;
    register unsigned int start = parameters->idx_start;
    register unsigned int final = parameters->idx_final;
    register unsigned int i;

    for (i = start; i < final; i++)
    {
        array3[i] = array1[i] + array2[i];
    }
    pthread_exit(NULL);
}

void thread_matrix_sum (long long int* array1, long long int* array2, long long int* array3, int dimension, int num_threads)
{
    ThreadParameters* parameters = newThreadParameters(num_threads);
    pthread_t* thread_ids = newThreadIDs(num_threads);
    register unsigned int num_elements = (dimension * dimension) / num_threads;
    register unsigned int i;
    
    for (i = 0; i < num_threads; i++)
    {
        parameters[i].array1 = array1;
        parameters[i].array2 = array2;
        parameters[i].array3 = array3;
        parameters[i].idx_start = num_elements * i;
        parameters[i].idx_final = (num_elements * (i+1));
        
        int thread = pthread_create(&thread_ids[i], NULL, matrix_sum, (void*) &parameters[i]);
        verify_thread_create(thread);
    }
    for (int i = 0; i < num_threads; i++)
    {
        int thread = pthread_join(thread_ids[i], NULL);
        verify_thread_join(thread);
    }
    free(parameters);
    free(thread_ids);
}

void* matrix_multiplication (void* parameters_ref)
{
    ThreadParameters* parameters = (ThreadParameters*) parameters_ref;
    long long int* array1 = parameters->array1;
    long long int* array2 = parameters->array2;
    long long int* array3 = parameters->array3;
    register unsigned int dimension = parameters->dimension;
    register unsigned int start = parameters->idx_start;
    register unsigned int final = parameters->idx_final;
    register unsigned int i, j;
    
    for (i = start; i < final; ++i) {
        register unsigned int row = i % dimension;
        register unsigned int col = i / dimension;

        for (j = 0; j < dimension; ++j) {
            array3[position(row, col, dimension)] += array1[position(row, j, dimension)] * array2[position(j, col, dimension)];
        }
    }
    pthread_exit(NULL);
}

void thread_matrix_multiplication (long long int* array1, long long int* array2, long long int* array3, int dimension, int num_threads)
{
    ThreadParameters* parameters = newThreadParameters(num_threads);
    pthread_t* thread_ids = newThreadIDs(num_threads);
    register unsigned int num_elements = (dimension * dimension) / num_threads;
    register unsigned int i;
    
    for (i = 0; i < num_threads; i++)
    {
        parameters[i].array1 = array1;
        parameters[i].array2 = array2;
        parameters[i].array3 = array3;
        parameters[i].dimension = dimension;
        parameters[i].idx_start = num_elements * i;
        parameters[i].idx_final = (num_elements * (i+1));

        int thread = pthread_create(&thread_ids[i], NULL, matrix_multiplication, (void*) &parameters[i]);
        verify_thread_create(thread);
    }
    for (int i = 0; i < num_threads; i++)
    {
        int thread = pthread_join(thread_ids[i], NULL);
        verify_thread_join(thread);
    }
    free(parameters);
    free(thread_ids);
}

void* matrix_reduce (void* parameters_ref)
{
    ThreadParameters* parameters = (ThreadParameters*) parameters_ref;
    long long int* array = parameters->array1;
    long long int sum = 0;
    register unsigned int start = parameters->idx_start;
    register unsigned int final = parameters->idx_final;
    register unsigned int i;

    for (i = start; i < final; i++)
    {
        sum += array[i];
    }

    long long int* answer = malloc(sizeof(answer));
    verify_allocation_memory(answer);
    *answer = sum;
    pthread_exit(answer);
}

long long int thread_matrix_reduce (long long int* array1, int dimension, int num_threads)
{
    ThreadParameters* parameters = newThreadParameters(num_threads);
    pthread_t* thread_ids = newThreadIDs(num_threads);
    long long int* partialSum = NULL;
    long long int sum = 0;
    register unsigned int i;
    
    register unsigned int num_elements = (dimension * dimension) / num_threads;
    for (i = 0; i < num_threads; i++)
    {
        parameters[i].array1 = array1;
        parameters[i].idx_start = num_elements * i;
        parameters[i].idx_final = (num_elements * (i+1));
        
        int thread = pthread_create(&thread_ids[i], NULL, matrix_reduce, (void*) &parameters[i]);
        verify_thread_create(thread);
    }
    for (int i = 0; i < num_threads; i++)
    {
        int thread = pthread_join(thread_ids[i], (void**) &partialSum);
        verify_thread_join(thread);

        sum += *(long long int*) partialSum;
    }
    free(parameters);
    free(thread_ids);
    return sum;
}