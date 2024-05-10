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

void* writeMatrix (void* matrix_ref)
{
    Matrix* matrix = (Matrix*) matrix_ref;
    long long int dimension = matrix->dimension;
    register unsigned int i, j;

    for (i = 0; i < dimension; i++)
    {
        for (j = 0; j < dimension; j++)
        {
            fprintf(matrix->fileArray, "%lld ", (matrix->array)[(position(i, j, dimension))]);
        }
        fprintf(matrix->fileArray, "\n");
    }
    fclose(matrix->fileArray);
    pthread_exit(NULL);
}

void* thrdSomaParcial(void* parameters_ref)
{
    ThreadParameters* parameters = (ThreadParameters*) parameters_ref;
    register unsigned int i, start, final;
    long long int* array1;
    long long int* array2;
    long long int* array3;
    start = parameters->idx_start;
    final  = parameters->idx_final;
    array1 = parameters->array1;
    array2 = parameters->array2;
    array3 = parameters->array3;

    for (i = start; i <= final; i++)
    {
        array3[i] = array1[i] + array2[i];
    }
    pthread_exit(NULL);
}

void sumMatrix(long long int* array1, long long int* array2, long long int* array3, long long dimension, long long int num_threads)
{
    register unsigned int i;
    ThreadParameters* parameters = newThreadParameters(num_threads);
    pthread_t* tids = newThreadIDs(num_threads);
    
    long long int quantElementos = (dimension * dimension) / num_threads;
    for (i = 0; i < num_threads; i++)
    {
        parameters[i].idx_start = quantElementos * i;
        parameters[i].idx_final = (quantElementos * (i+1)) - 1;
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
}

void* multiplyMatrix (void* matrix_ref)
{
    Matrix* matrix = (Matrix*) matrix_ref;
    long long int dimension = matrix[0].dimension;
    register unsigned int i, j, k;

    for (i = 0; i < dimension; i++)
    {
        for (k = 0; k < dimension; k++)
        {
            for (j = 0; j < dimension; j++)
            {
                (matrix[4].array)[position(i, j, dimension)] = (matrix[4].array)[position(i, j, dimension)] + (matrix[2].array)[position(i, k, dimension)] * (matrix[3].array)[position(k, j, dimension)];
            }
        }
    }
    pthread_exit(NULL);
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