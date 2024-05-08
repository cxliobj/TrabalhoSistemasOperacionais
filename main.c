#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "matrix.h"
#include "string.h"

int main(int argc, char** argv)
{
    if (argc != 8) 
    {
        printf("Quantidade de argumentos incorreta.\n");
        exit(EXIT_FAILURE);
    }

    clock_t start_global, end_global, start_sum, end_sum, start_multiplication, end_multiplication, start_reduction, end_reduction;
    long int num_threads = stringToInt(argv[1]);
    long int dimension = stringToInt(argv[2]);
    Matrix matrix[5];
    pthread_t tids[num_threads];

    for (int i = 0; i < 5; i++)
    {
        matrix[i].fileArray = fopen(argv[i + 3], "r+");
        if (matrix[i].fileArray == NULL) 
        { 
            printf("Arquivo txt %d nao foi aberto.\n", i); 
            exit(EXIT_FAILURE); 
        }
        matrix[i].dimension = dimension;
        matrix[i].array = (long long int*) calloc (dimension * dimension, sizeof(long long int));
    }

/* START **************************************************************************************************************************** */

    start_global = clock();

    // PASSO 1 (2 threads Tl)

    for (int i = 0; i < 2; i++)
    {
        pthread_create(&tids[i], NULL, transcribeMatrix, &matrix[i]);
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_join(tids[i], NULL);
    }

    // PASSO 2 (T threads Tp)

    start_sum = clock();

    pthread_create(&tids[0], NULL, sumMatrix, &matrix);
    pthread_join(tids[0], NULL);

    end_sum = clock() - start_sum;

    // PASSO 3 (1 thread Te)

    pthread_create(&tids[0], NULL, writeMatrix, &matrix[3]);
    pthread_join(tids[0], NULL);

    // PASSO 4 (1 thread Tl)

    pthread_create(&tids[0], NULL, transcribeMatrix, &matrix[2]);
    pthread_join(tids[0], NULL);

    // PASSO 5 (2 threads Tp)

    start_multiplication = clock();
    
    pthread_create(&tids[0], NULL, multiplyMatrix, &matrix);
    pthread_join(tids[0], NULL);
    
    end_multiplication = clock() - start_multiplication;

    // PASSO 6 (1 thread Te)

    pthread_create(&tids[0], NULL, writeMatrix, &matrix[4]);
    pthread_join(tids[0], NULL);

    // PASSO 7 (1 thread Tp)

    start_reduction = clock();

    long long* reduction;
    pthread_create(&tids[0], NULL, reduceMatrix, &matrix[4]);
    pthread_join(tids[0], (void**) &reduction);

    end_reduction = clock() - start_reduction;

    end_global = clock() - start_global;

/* FINAL **************************************************************************************************************************** */

    double total_time_sum = ((double) end_sum) / CLOCKS_PER_SEC;
    double total_time_multiplication = ((double) end_multiplication) / CLOCKS_PER_SEC;
    double total_time_reduction = ((double) end_reduction) / CLOCKS_PER_SEC;
    double total_time_global = ((double) end_global) / CLOCKS_PER_SEC;

    printf("Reducao: %lld.\n", *reduction);
    printf("Tempo soma: %lf segundos.\n", total_time_sum);
    printf("Tempo multiplicacao: %lf segundos.\n", total_time_multiplication);
    printf("Tempo reducao: %lf segundos.\n", total_time_reduction);
    printf("Tempo total: %lf segundos.\n", total_time_global);

    return 0;
}