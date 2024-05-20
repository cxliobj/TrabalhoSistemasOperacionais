#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "errorMessages.h"
#include "resources.h"
#include "matrix.h"
#include "threads.h"

int main(int argc, char** argv)
{
    verify_num_args(argc);

/*** DECLARATIONS ***************************************************************** ***/

    int num_threads = (int) stringToInt(argv[1]);
    int dimension = (int) stringToInt(argv[2]);
    verify_num_threads_dimension(num_threads, dimension);

    Matrix* matrix[5];
    for (int i = 0; i < 5; i++)
    {
        matrix[i] = newMatrix(argv[i+3], dimension);
    }

/*** START ************************************************************************ ***/

    clock_t start_global = clock();

/*** SOMA ************************************************************************* ***/

    clock_t start_sum = clock();
    
    sum(matrix, dimension, num_threads);

    clock_t end_sum = clock() - start_sum;

/*** MULTIPLICATION *************************************************************** ***/

    clock_t start_multiplication = clock();
    
    multiply(matrix, dimension, num_threads);
    
    clock_t end_multiplication = clock() - start_multiplication;

/*** REDUCTION ******************************************************************** ***/

    clock_t start_reduction = clock();

    long long int reduction = reduce(matrix, dimension, num_threads);

    clock_t end_reduction = clock() - start_reduction;
    
/*** FINAL ************************************************************************ ***/

    clock_t end_global = clock() - start_global;

/*** PRINTING DATA **************************************************************** ***/

    double total_time_sum = ((double) end_sum) / CLOCKS_PER_SEC;
    double total_time_multiplication = ((double) end_multiplication) / CLOCKS_PER_SEC;
    double total_time_reduction = ((double) end_reduction) / CLOCKS_PER_SEC;
    double total_time_global = ((double) end_global) / CLOCKS_PER_SEC;

    printf("Reducao: %lld.\n", reduction);
    printf("Tempo soma: %lf segundos.\n", total_time_sum);
    printf("Tempo multiplicacao: %lf segundos.\n", total_time_multiplication);
    printf("Tempo reducao: %lf segundos.\n", total_time_reduction);
    printf("Tempo total: %lf segundos.\n", total_time_global);

    return 0;
}