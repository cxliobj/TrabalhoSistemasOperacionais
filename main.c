#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "matrix.h"
#include "string.h"
#include "resources.h"

void show_thread_create_error (int thread)
{
    if (thread != 0)
    {
        printf("Thread create failed.\n");
        exit(EXIT_FAILURE);
    }
}

void show_thread_join_error (int thread)
{
    if (thread != 0)
    {
        printf("Thread join failed.\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char** argv)
{
    if (argc != 8) 
    {
        printf("Quantidade de argumentos incorreta.\n");
        exit(EXIT_FAILURE);
    }

/* DECLARATIONS ********************************************************************************************************************* */

    clock_t start_global, end_global, start_sum, end_sum, start_multiplication, end_multiplication, start_reduction, end_reduction;
    long long int num_threads = stringToInt(argv[1]);
    long long int dimension = stringToInt(argv[2]);
    pthread_t tids[num_threads];
    
    Matrix* matrix = newMatrix();

    for (int i = 0; i < 5; i++)
    {
        matrix[i].fileArray = openFile(argv[i + 3]);
        matrix[i].dimension = dimension;
        matrix[i].array = vectorAllocation(dimension);
    }
    
/* START **************************************************************************************************************************** */

    start_global = clock();

    // PASSO 1 (2 threads Tl)
    int thread;
    for (int i = 0; i < 2; i++)
    {
        thread = pthread_create(&tids[i], NULL, transcribeMatrix, (void*) &matrix[i]);
        show_thread_create_error(thread);
    }

    for (int i = 0; i < 2; i++)
    {
        thread = pthread_join(tids[i], NULL);
        show_thread_join_error(thread);
    }

    // PASSO 2 (T threads Tp)

    start_sum = clock();

    thread = pthread_create(&tids[0], NULL, sumMatrix, (void*) matrix);
    show_thread_create_error(thread);

    thread = pthread_join(tids[0], NULL);
    show_thread_join_error(thread);

    end_sum = clock() - start_sum;

    // PASSO 3 (1 thread Te)

    pthread_create(&tids[0], NULL, writeMatrix, (void*) &matrix[3]);
    show_thread_create_error(thread);

    pthread_join(tids[0], NULL);
    show_thread_join_error(thread);

    // PASSO 4 (1 thread Tl)

    pthread_create(&tids[0], NULL, transcribeMatrix, (void*) &matrix[2]);
    show_thread_create_error(thread);

    pthread_join(tids[0], NULL);
    show_thread_join_error(thread);

    // PASSO 5 (2 threads Tp)

    start_multiplication = clock();
    
    pthread_create(&tids[0], NULL, multiplyMatrix, (void*) matrix);
    show_thread_create_error(thread);

    pthread_join(tids[0], NULL);
    show_thread_join_error(thread);
    
    end_multiplication = clock() - start_multiplication;

    // PASSO 6 (1 thread Te)

    pthread_create(&tids[0], NULL, writeMatrix, (void*) &matrix[4]);
    show_thread_create_error(thread);

    pthread_join(tids[0], NULL);
    show_thread_join_error(thread);

    // PASSO 7 (1 thread Tp)

    start_reduction = clock();

    long long int* reduction;
    
    pthread_create(&tids[0], NULL, reduceMatrix, (void*) &matrix[4]);
    show_thread_create_error(thread);

    pthread_join(tids[0], (void**) &reduction);
    show_thread_join_error(thread);

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