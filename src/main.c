/**
 * Nome do grupo: Vasco da Gama
 * Integrante 1: Celio Benhami Junior (246625) 
 * Integrante 2: Gabriel Gato Piragini Santana (169025)
*/

#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "../include/errorMessages.h"
#include "../include/resources.h"
#include "../include/matrix.h"
#include "../include/threads.h"

struct timespec start_sum, finish_sum;
struct timespec start_mult, finish_mult;
struct timespec start_reduc, finish_reduc;

int main(int argc, char** argv)
{
    verify_num_args(argc);

    int num_threads = stringToInt(argv[1]);
    verify_num_threads(num_threads);
    
    int dimension = stringToInt(argv[2]);
    verify_num_dimension(dimension);

    Matrix** matrix = (Matrix**) malloc(5 * sizeof(Matrix*));
    for (int i = 0; i < 5; i++)
    {
        matrix[i] = newMatrix(argv[i+3], dimension);
    }

    transcribe_A_and_B(matrix, num_threads);

    clock_gettime(CLOCK_MONOTONIC, &start_sum);
    sum(matrix, dimension, num_threads);
    clock_gettime(CLOCK_MONOTONIC, &finish_sum);

    write_D_transcribe_C(matrix, num_threads);

    clock_gettime(CLOCK_MONOTONIC, &start_mult);
    multiply(matrix, dimension, num_threads);
    clock_gettime(CLOCK_MONOTONIC, &finish_mult);

    clock_gettime(CLOCK_MONOTONIC, &start_reduc);
    long long int reduction = reduce(matrix, dimension, num_threads);
    clock_gettime(CLOCK_MONOTONIC, &finish_reduc);

    long double sum_elapsed = (finish_sum.tv_sec - start_sum.tv_sec);
    sum_elapsed += (finish_sum.tv_nsec - start_sum.tv_nsec) / 1000000000.0;

    long double mult_elapsed = (finish_mult.tv_sec - start_mult.tv_sec);
    mult_elapsed += (finish_mult.tv_nsec - start_mult.tv_nsec) / 1000000000.0;

    long double reduc_elapsed = (finish_reduc.tv_sec - start_reduc.tv_sec);
    reduc_elapsed += (finish_reduc.tv_nsec - start_reduc.tv_nsec) / 1000000000.0;

    long double global_elapsed = sum_elapsed + mult_elapsed + reduc_elapsed;

    printf("Reducao: %Ld.\n", reduction);
    printf("Tempo soma: %Lf segundos.\n", sum_elapsed);
    printf("Tempo multiplicacao: %Lf segundos.\n", mult_elapsed);
    printf("Tempo reducao: %Lf segundos.\n", reduc_elapsed);
    printf("Tempo total: %Lf segundos.\n", global_elapsed);

    return 0;
}