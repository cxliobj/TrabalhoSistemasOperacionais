#include "matrix.h"

void* transcribeMatrix (void* matrix_ref)
{
    Matrix* matrix = (Matrix*) matrix_ref;
    long long int finput=0;
    register unsigned int i = 0;

    while (fscanf(matrix->fileArray, "%lld", &finput) != EOF)
    {
        (matrix->array)[i] = finput;
        i++;
    }
    fclose(matrix->fileArray);
    pthread_exit(NULL);
}

void* threadWriteMatrix (void* parameters_ref)
{
    ThreadParameters* parameters = (ThreadParameters*) parameters_ref;
    register unsigned int i, j, dimension;
    FILE* fileArray;
    long long int* array;
    fileArray = parameters->fileArray;
    dimension = parameters->dimension;
    array = parameters->array1;

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

void writeMatrix (long long int* array1, FILE* fileArray, long long int dimension, long long int num_threads)
{
    ThreadParameters* parameters = newThreadParameters(1);
    pthread_t* tids = newThreadIDs(1);
    int thread;

    parameters[0].array1 = array1;
    parameters[0].dimension = dimension;
    parameters[0].fileArray = fileArray;
    thread = pthread_create(&tids[0], NULL, threadWriteMatrix, (void*) &parameters[0]);
    show_thread_create_error(thread);

    thread = pthread_join(tids[0], NULL);
    show_thread_join_error (thread);

    free(parameters);
    free(tids);
}

void* thrdSomaParcial (void* parameters_ref)
{
    ThreadParameters* parameters = (ThreadParameters*) parameters_ref;
    register unsigned int i, start, final;
    long long int* array1;
    long long int* array2;
    long long int* array3;
    start = parameters->idx_start;
    final = parameters->idx_final;
    array1 = parameters->array1;
    array2 = parameters->array2;
    array3 = parameters->array3;

    for (i = start; i < final; i++)
    {
        array3[i] = array1[i] + array2[i];
    }
    pthread_exit(NULL);
}

void sumMatrix (long long int* array1, long long int* array2, long long int* array3, long long dimension, long long int num_threads)
{
    register unsigned int i;
    ThreadParameters* parameters = newThreadParameters(num_threads);
    pthread_t* tids = newThreadIDs(num_threads);
    
    long long int quantElementos = (dimension * dimension) / num_threads;
    for (i = 0; i < num_threads; i++)
    {
        parameters[i].idx_start = quantElementos * i;
        parameters[i].idx_final = (quantElementos * (i+1));
        parameters[i].array1 = array1;
        parameters[i].array2 = array2;
        parameters[i].array3 = array3;
        int thread = pthread_create(&tids[i], NULL, thrdSomaParcial, (void*) &parameters[i]);
        show_thread_create_error(thread);
    }
    for (int i = 0; i < num_threads; i++)
    {
        int thread = pthread_join(tids[i], NULL);
        show_thread_join_error (thread);
    }
    free(parameters);
    free(tids);
}

void* threadPartialMulti (void* parameters_ref)
{
    ThreadParameters* parameters = (ThreadParameters*) parameters_ref;
    register unsigned int i, j, start, final;
    long long int* array1;
    long long int* array2;
    long long int* array3;
    long long int dimension;
    start = parameters->idx_start;
    final = parameters->idx_final;
    array1 = parameters->array1;
    array2 = parameters->array2;
    array3 = parameters->array3;
    dimension = parameters->dimension;

    for (i = start; i < final; ++i) {
        int row = i % dimension;
        int col = i / dimension;
        for (j = 0; j < dimension; ++j) {
            array3[position(row, col, dimension)] += array1[position(row, j, dimension)] * array2[position(j, col, dimension)];
        }
    }
    pthread_exit(NULL);
}

void multiplyMatrix(long long int* array1, long long int* array2, long long int* array3, long long dimension, long long int num_threads)
{
    register unsigned int i;
    ThreadParameters* parameters = newThreadParameters(num_threads);
    pthread_t* tids = newThreadIDs(num_threads);
    
    long long int quantElementos = (dimension * dimension) / num_threads;
    for (i = 0; i < num_threads; i++)
    {
        parameters[i].idx_start = quantElementos * i;
        parameters[i].idx_final = (quantElementos * (i+1));
        parameters[i].array1 = array1;
        parameters[i].array2 = array2;
        parameters[i].array3 = array3;
        parameters[i].dimension = dimension;
        int thread = pthread_create(&tids[i], NULL, threadPartialMulti, (void*) &parameters[i]);
        show_thread_create_error(thread);
    }
    for (int i = 0; i < num_threads; i++)
    {
        int thread = pthread_join(tids[i], NULL);
        show_thread_join_error (thread);
    }
    free(parameters);
    free(tids);
}

void* reduceMatrix (void* matrix_ref)
{
    Matrix* matrix = (Matrix*) matrix_ref;
    long long int size = matrix->dimension * matrix->dimension;
    long long int sum = 0;
    register unsigned int i;

    for (i = 0; i < size; i++)
    {
        sum += (matrix->array)[i];
    }

    long long int* answer = malloc(sizeof(answer));
    if (answer == NULL)
    {
        printf("Erro no malloc answer.\n");
        exit(EXIT_FAILURE);
    }
    *answer = sum;
    pthread_exit(answer);
}