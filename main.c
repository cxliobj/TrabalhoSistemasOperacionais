#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "errorMessages.h"
#include "resources.h"
#include "matrix.h"

int main(int argc, char** argv)
{
    show_error_num_args(argc);

/*** DECLARATIONS ******************************************************************************************************************* */

    long long int num_threads = stringToInt(argv[1]);
    long long int dimension = stringToInt(argv[2]);

    show_error_numThreads_dimension (num_threads, dimension);

    long long int* matrix[5];
    FILE* file[5];

    for (int i = 0; i < 5; i++)
    {
        file[i] = openFile(argv[i + 3]);
        matrix[i] = newMatrix(dimension);
    }
    
/*** START ************************************************************************************************************************** */

    clock_t start_global = clock();

    /*
    PASSO 1: Leitura da Matriz A // Leitura da Matriz B (2 threads Tl)
    */

    transcribeMatrix (matrix[0], file[0], dimension);
    transcribeMatrix (matrix[1], file[1], dimension);

    /*
    PASSO 2: Soma das Matrizes A + B = D (T threads Tp)
    */

    clock_t start_sum = clock();
    
    sumMatrix(matrix[0], matrix[1], matrix[3], dimension, num_threads);

    clock_t end_sum = clock() - start_sum;

    /*
    PASSO 3 // PASSO 4: Gravação da Matriz D // Leitura da Matriz C (1 thread Te e 1 thread Tl)
    */

    writeMatrix (matrix[3], file[3], dimension);

    transcribeMatrix (matrix[2], file[2], dimension);

    /*
    PASSO 5: Multiplicação das Matrizes D x C = E (T threads Tp)
    */

    clock_t start_multiplication = clock();
    
    multiplyMatrix(matrix[3], matrix[2], matrix[4], dimension, num_threads);
    
    clock_t end_multiplication = clock() - start_multiplication;

    /*
    PASSO 6 // PASSO 7: Gravação da Matriz E // Redução da Matriz E (1 thread Te e T threads Tp)
    */

    writeMatrix (matrix[4], file[4], dimension);

    clock_t start_reduction = clock();

    long long int reduction = reduceMatrix(matrix[4], dimension, num_threads);

    clock_t end_reduction = clock() - start_reduction;

    clock_t end_global = clock() - start_global;

/*** FINAL ************************************************************************************************************************** */

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