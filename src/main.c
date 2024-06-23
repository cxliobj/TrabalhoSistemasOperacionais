/**
 * Nome do grupo: Vasco da Gama
 * Integrante 1: Celio Benhami Junior (246625) 
 * Integrante 2: Gabriel Gato Piragini Santana (169025)
*/

#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>
#include "../include/errorMessages.h"
#include "../include/resources.h"
#include "../include/threads.h"

#define file_matrix_A argv[3]
#define file_matrix_B argv[4]
#define file_matrix_C argv[5]
#define file_matrix_D argv[6]
#define file_matrix_E argv[7]

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

    Matrix* matrix_A = newMatrix(file_matrix_A, "r+", dimension);
    Matrix* matrix_B = newMatrix(file_matrix_B, "r+", dimension);
    Matrix* matrix_C = newMatrix(file_matrix_C, "r+", dimension);
    Matrix* matrix_D = newMatrix(file_matrix_D, "w+", dimension);
    Matrix* matrix_E = newMatrix(file_matrix_E, "w+", dimension);
    
    transcribe_A_and_B(matrix_A, matrix_B, num_threads);
    
    clock_gettime(CLOCK_MONOTONIC, &start_sum);
    sum(matrix_A, matrix_B, matrix_D, dimension, num_threads);
    clock_gettime(CLOCK_MONOTONIC, &finish_sum);
    
    write_D_transcribe_C(matrix_C, matrix_D, num_threads);

    clock_gettime(CLOCK_MONOTONIC, &start_mult);
    multiply(matrix_C, matrix_D, matrix_E, dimension, num_threads);
    clock_gettime(CLOCK_MONOTONIC, &finish_mult);

    clock_gettime(CLOCK_MONOTONIC, &start_reduc);
    long long int reduction = reduce(matrix_E, dimension, num_threads);
    clock_gettime(CLOCK_MONOTONIC, &finish_reduc);

    double sum_elapsed = (finish_sum.tv_sec - start_sum.tv_sec);
    sum_elapsed += (finish_sum.tv_nsec - start_sum.tv_nsec) / 1000000000.0;

    double mult_elapsed = (finish_mult.tv_sec - start_mult.tv_sec);
    mult_elapsed += (finish_mult.tv_nsec - start_mult.tv_nsec) / 1000000000.0;

    double reduc_elapsed = (finish_reduc.tv_sec - start_reduc.tv_sec);
    reduc_elapsed += (finish_reduc.tv_nsec - start_reduc.tv_nsec) / 1000000000.0;

    double global_elapsed = sum_elapsed + mult_elapsed + reduc_elapsed;

    printf("Reducao: %lld.\n", reduction);
    printf("Tempo soma: %lf segundos.\n", sum_elapsed);
    printf("Tempo multiplicacao: %lf segundos.\n", mult_elapsed);
    printf("Tempo reducao: %lf segundos.\n", reduc_elapsed);
    printf("Tempo total: %lf segundos.\n", global_elapsed);

    return 0;
}
