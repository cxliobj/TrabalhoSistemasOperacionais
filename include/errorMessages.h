#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

/**
 * Verifica o valor retornado do comando pthread_create. 
 * Se for 0, a thread foi criada com sucesso.
 * Qualquer valor diferente disso é considerado como erro.
**/
void verify_thread_create(int err);

/**
 * Verifica o valor retornado do comando pthread_join. 
 * Se for 0, a thread foi criada com sucesso.
 * Qualquer valor diferente disso é considerado como erro.
**/
void verify_thread_join(int err);

/**
 * Verifica se o inteiro repassado para uma determinada função é valido para a alocação de memória.
 * Em caso de falha o programa aborta a execução.
**/
void verify_allocation_memory_size(int obj);

/**
 * Verifica se a alocação de memória foi concluída com sucesso.
 * Em caso de falha o programa aborta a execução.
 * @param obj Qualquer ponteiro usado para alocação dinamica de memória.
**/
void verify_allocation_memory(void* obj);

/**
 * Verifica se o arquivo foi aberto corretamente.
 * Um ponteiro nulo indica que a abertura do arquivo falhou.
 * Em caso de falha o programa aborta a execução.
 * @param file Qualquer ponteiro de arquivo que já foi aberto.
**/
void verify_open_file(FILE* file, char* file_name);

/**
 * Verifica se o programa recebeu exatamente os 8 parametros necessário para rodar corretamente.
 * Em caso de falha o programa aborta a execução.
 * @param argc Número de argumentos usados na execução do programa
**/
void verify_num_args(int argc);

/**
 * Essa função verifica algumas condições dado o número de threads.
 * Como o programa só executa para 1, 2 e 4 threads, somente estes valores são aceitos.
 * Em caso de valor incompatível o programa aborta a execução.
**/
void verify_num_threads(int num_threads);

/**
 * Essa função verifica se o tamanho da matriz (dimensão) é valido.
 * Em caso de valor incompatível o programa aborta a execução.
**/
void verify_num_dimension(int dimension);

#endif