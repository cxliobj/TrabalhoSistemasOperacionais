#include "matrix.h"

Matrix* newMatrix(int dimension, FILE* argv_file_matrix)
{
    Matrix* matrix = (Matrix*) malloc(sizeof(Matrix));
    matrix->fileArray = argv_file_matrix;
    matrix->array = (int*) malloc (dimension * dimension * sizeof(int));
    matrix->dimension = dimension;
    matrix->reduction = 0;
    return matrix;
}

void sumMatrix(Matrix* matrix1, Matrix* matrix2, Matrix* matrix3)
{
    int size = matrix1->dimension * matrix1->dimension;

    for (int position = 0; position < size; position++)
    {
        (matrix3->array)[position] = (matrix1->array)[position] + (matrix2->array)[position];
    }
}

void multiplyMatrix (Matrix* matrix1, Matrix* matrix2, Matrix* matrix3)
{
    int dimension = matrix1->dimension;

    for (int i = 0; i < dimension; i++)
    {
        for (int k = 0; k < dimension; k++)
        {
            for (int j = 0; j < dimension; j++)
            {
                (matrix3->array)[position(i,j, matrix3->dimension)] = (matrix3->array)[position(i, j, matrix3->dimension)] +
                                                    (matrix1->array)[position(i, k, matrix1->dimension)] * (matrix2->array)[position(k, j, matrix2->dimension)];
            }
        }
    }
}

void transcribeMatrix (Matrix* matrix)
{
    int finput=0, position=0;
    while (fscanf(matrix->fileArray, "%d", &finput) != EOF)
    {
        (matrix->array)[position] = finput;
        position++;
    }
}

void writeMatrix (Matrix* matrix)
{
    int dimension = matrix->dimension;

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            fprintf(matrix->fileArray, "%d ", (matrix->array)[(position(i, j, dimension))]);
        }
        fprintf(matrix->fileArray, "\n");
    }
}

void reduceMatrix (Matrix* matrix)
{
    int size = matrix->dimension * matrix->dimension;
    
    long long sum = 0;

    for (int position = 0; position < size; position++)
    {
        sum += (matrix->array)[position];
    }
    matrix->reduction = sum;
}