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

void* sumMatrix(void* matrix_ref)
{
    Matrix* matrix = (Matrix*) matrix_ref;
    long long int size = matrix[0].dimension * matrix[0].dimension;
    register unsigned int i;

    for (i = 0; i < size; i++)
    {
        (matrix[3].array)[i] = (matrix[0].array)[i] + (matrix[1].array)[i];
    }
    pthread_exit(NULL);
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