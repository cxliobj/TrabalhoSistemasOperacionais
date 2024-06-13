#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "../include/errorMessages.h"
#include "../include/resources.h"
#include "../include/matrix.h"
#include "../include/threads.h"

int main(int argc, char** argv)
{
    verify_num_args(argc);

    int num_threads = stringToInt(argv[1]);
    verify_num_threads(num_threads);
    
    int dimension = stringToInt(argv[2]);
    verify_num_dimension(dimension);

    Matrix* matrix[5];
    for (int i = 0; i < 5; i++)
    {
        matrix[i] = newMatrix(argv[i+3], dimension);
    }

    clock_t start_global = clock();
    
    transcribe_A_and_B(matrix, num_threads);

    clock_t start_sum = clock();
    sum(matrix, dimension, num_threads);
    clock_t end_sum = clock() - start_sum;

    write_D_transcribe_C(matrix, num_threads);

    clock_t start_multiplication = clock();
    multiply(matrix, dimension, num_threads);
    clock_t end_multiplication = clock() - start_multiplication;

    clock_t start_reduction = clock();
    long long int reduction = reduce(matrix, dimension, num_threads);
    clock_t end_reduction = clock() - start_reduction;

    clock_t end_global = clock() - start_global;

    double total_time_sum = (((double) end_sum) / num_threads) / CLOCKS_PER_SEC;
    double total_time_multiplication = (((double) end_multiplication) / num_threads) / CLOCKS_PER_SEC;
    double total_time_reduction = (((double) end_reduction) / num_threads) / CLOCKS_PER_SEC;
    double total_time_global = (((double) end_global) / num_threads) / CLOCKS_PER_SEC;

    printf("Reducao: %lld.\n", reduction);
    printf("Tempo soma: %lf segundos.\n", total_time_sum);
    printf("Tempo multiplicacao: %lf segundos.\n", total_time_multiplication);
    printf("Tempo reducao: %lf segundos.\n", total_time_reduction);
    printf("Tempo total: %lf segundos.\n", total_time_global);

    return 0;
}