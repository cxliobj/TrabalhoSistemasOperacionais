#include "resources.h"

Matrix* newMatrix ()
{
    Matrix* matrix = (Matrix*) malloc(5 * sizeof(Matrix));
    if (matrix  == NULL)
    {
        printf("Error malloc allocation memory.\n");
        exit(EXIT_FAILURE);
    }
    return matrix;
}

long long int* vectorAllocation(long long int dimension)
{
    if (dimension <= 0)
    {
        printf("Matrix size is incompatible to allocate.\n");
        exit(EXIT_FAILURE);
    }

    long long int* vector = (long long int*) calloc (dimension * dimension, sizeof(long long int));
    if (vector == NULL)
    {
        printf("Error calloc allocation memory.\n");
        exit(EXIT_FAILURE);
    }
    return vector;
}

FILE* openFile(char* argv_file_matrix)
{
    FILE* file = fopen(argv_file_matrix, "r+");
    if (file == NULL)
    { 
        printf("Cannot open file.\n"); 
        exit(EXIT_FAILURE); 
    }
    return file;
}
