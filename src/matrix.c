#include "../include/matrix.h"

void* matrix_transcribe(void* matrix_ref)
{
    Matrix* matrix = (Matrix*) matrix_ref;
    FILE* fileArray = matrix->fileArray;
    long long int* array = matrix->array;
    long long int finput;
    register unsigned int i = 0;

    while (fscanf(fileArray, "%lld", &finput) != EOF)
    {
        array[i] = finput;
        i++;
    }
    fclose(fileArray);
    return NULL;
}

void* matrix_write(void* matrix_ref)
{
    Matrix* matrix = (Matrix*) matrix_ref;
    FILE* fileArray = matrix->fileArray;
    long long int* array = matrix->array;
    register unsigned int dimension = matrix->dimension;
    register unsigned int i, j;

    for (i = 0; i < dimension; i++)
    {
        for (j = 0; j < dimension; j++)
        {
            fprintf(fileArray, "%lld ", array[position(i, j, dimension)]);
        }
        fprintf(fileArray, "\n");
    }
    fclose(fileArray);
    return NULL;
}

void* matrix_sum(void* parameters_ref)
{
    Parameters* parameters = (Parameters*) parameters_ref;
    long long int* array1 = parameters->array1;
    long long int* array2 = parameters->array2;
    long long int* array3 = parameters->array3;
    register unsigned int start = parameters->start_pos;
    register unsigned int final = parameters->final_pos;
    register unsigned int i;

    for (i = start; i < final; i++)
    {
        array3[i] = array1[i] + array2[i];
    }
    return NULL;
}

void* matrix_multiplication(void* parameters_ref)
{
    Parameters* parameters = (Parameters*) parameters_ref;
    long long int* array1 = parameters->array1;
    long long int* array2 = parameters->array2;
    long long int* array3 = parameters->array3;
    register unsigned int dimension = parameters->dimension;
    register unsigned int start = parameters->start_pos;
    register unsigned int final = parameters->final_pos;
    register unsigned int i, j, k;

    for(i = start; i < final; i++)
    {
        for(k = 0; k < dimension; k++)
        {
            for(j = 0; j < dimension; j++)
            {
                array3[position(i, j, dimension)] += array1[position(i, k, dimension)] * array2[position(k, j, dimension)];
            }
        }
    }
    return NULL;
}

void* matrix_reduce(void* parameters_ref)
{
    Parameters* parameters = (Parameters*) parameters_ref;
    long long int* array = parameters->array1;
    long long int sum = 0;
    register unsigned int start = parameters->start_pos;
    register unsigned int final = parameters->final_pos;
    register unsigned int i;

    for (i = start; i < final; i++)
    {
        sum += array[i];
    }
    long long int* answer = malloc(sizeof(answer));
    verify_allocation_memory(answer);
    *answer = sum;
    return answer;
}