#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "errorMessages.h"
#include "resources.h"
#include "matrix.h"

int main(int argc, char** argv)
{
    verify_num_args(argc);

/*** DECLARATIONS ******************************************************************************************************************* */

    int num_threads = (int) stringToInt(argv[1]);
    int dimension = (int) stringToInt(argv[2]);

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

    void* thread1_transcribe = init_transcribe (file[0], matrix[0], dimension, num_threads);
    void* thread2_transcribe = init_transcribe (file[1], matrix[1], dimension, num_threads);
    end_transcribe(thread1_transcribe, num_threads);
    end_transcribe(thread2_transcribe, num_threads);

    /*
    PASSO 2: Soma das Matrizes A + B = D (T threads Tp)
    */

    clock_t start_sum = clock();
    
    thread_matrix_sum (matrix[0], matrix[1], matrix[3], dimension, num_threads);

    clock_t end_sum = clock() - start_sum;

    /*
    PASSO 3 // PASSO 4: Gravação da Matriz D // Leitura da Matriz C (1 thread Te e 1 thread Tl)
    */

    void* thread1_write = init_write (file[3], matrix[3], dimension, num_threads);

    end_write(thread1_write, num_threads);

    void* thread3_transcribe = init_transcribe (file[2], matrix[2], dimension, num_threads);

    end_transcribe(thread3_transcribe, num_threads);
    /*
    PASSO 5: Multiplicação das Matrizes D x C = E (T threads Tp)
    */

    clock_t start_multiplication = clock();
    
    thread_matrix_multiplication (matrix[3], matrix[2], matrix[4], dimension, num_threads);
    
    clock_t end_multiplication = clock() - start_multiplication;

    /*
    PASSO 6 // PASSO 7: Gravação da Matriz E // Redução da Matriz E (1 thread Te e T threads Tp)
    */

    void* thread2_write = init_write (file[4], matrix[4], dimension, num_threads);

    end_write(thread2_write, num_threads);

    clock_t start_reduction = clock();

    long long int reduction = thread_matrix_reduce (matrix[4], dimension, num_threads);

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