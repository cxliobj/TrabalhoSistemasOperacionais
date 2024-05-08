#include "matrix.h"

void* transcribeMatrix (void* matrix_ref)
{
    Matrix* matrix = (Matrix*) matrix_ref;
    int position = 0;
    long long int finput=0;

    while (fscanf(matrix->fileArray, "%lld", &finput) != EOF)
    {
        (matrix->array)[position] = finput;
        position++;
    }
    fclose(matrix->fileArray);
    pthread_exit(NULL);
}

void* writeMatrix (void* matrix_ref)
{
    Matrix* matrix = (Matrix*) matrix_ref;
    int dimension = matrix->dimension;

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
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
    int size = matrix[0].dimension * matrix[0].dimension;

    for (int position = 0; position < size; position++)
    {
        (matrix[3].array)[position] = (matrix[0].array)[position] + (matrix[1].array)[position];
    }
    pthread_exit(NULL);
}

void* multiplyMatrix (void* matrix_ref)
{
    Matrix* matrix = (Matrix*) matrix_ref;
    int dimension = matrix[0].dimension;

    for (int i = 0; i < dimension; i++)
    {
        for (int k = 0; k < dimension; k++)
        {
            for (int j = 0; j < dimension; j++)
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
    int size = matrix->dimension * matrix->dimension;
    long long sum = 0;

    for (int position = 0; position < size; position++)
    {
        sum += (matrix->array)[position];
    }

    long long* answer = malloc(sizeof(answer));
    *answer = sum;
    pthread_exit(answer);
}