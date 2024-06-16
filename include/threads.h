#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/errorMessages.h"
#include "../include/resources.h"
#include "../include/matrix.h"

/**
 * Função para fazer a leitura das matrizes A e B.
 * @param matrix_A Ponteiro que armazena as infromações da matriz A
 * @param matrix_B Ponteiro que armazena as infromações da matriz B
 * @param num_threads Número de threads
 * @return A função retorna NULL.
 * @throw Retorna 2 se alguma thread falhar, junto com uma mensagem de erro.
**/
void transcribe_A_and_B(Matrix* matrix_A, Matrix* matrix_B, int num_threads);

/**
 * Função para fazer a soma das matrizes A e B.
 * @param matrix_A Ponteiro que armazena as infromações da matriz A
 * @param matrix_B Ponteiro que armazena as infromações da matriz B
 * @param matrix_D Ponteiro que armazena as infromações da matriz D
 * @param dimension Ordem da matriz
 * @param num_threads Número de threads
 * @return A função retorna NULL.
 * @throw Retorna 2 se alguma thread falhar, junto com uma mensagem de erro.
**/
void sum(Matrix* matrix_A, Matrix* matrix_B, Matrix* matrix_D, int dimension, int num_threads);

/**
 * Função para fazer a gravação da matriz D e leitura das matriz C.
 * @param matrix_C Ponteiro que armazena as infromações da matriz C
 * @param matrix_D Ponteiro que armazena as infromações da matriz D
 * @param num_threads Número de threads
 * @return A função retorna NULL.
 * @throw Retorna 2 se alguma thread falhar, junto com uma mensagem de erro.
**/
void write_D_transcribe_C(Matrix* matrix_C, Matrix* matrix_D, int num_threads);

/**
 * Função para fazer a gravação da matriz D e redução da matriz E.
 * @param matrix_C Ponteiro que armazena as infromações da matriz C
 * @param matrix_D Ponteiro que armazena as infromações da matriz D
 * @param matrix_E Ponteiro que armazena as infromações da matriz E
 * @param dimension Ordem da matriz
 * @param num_threads Número de threads
 * @return A função retorna NULL.
 * @throw Retorna 2 se alguma thread falhar, junto com uma mensagem de erro.
**/
void multiply(Matrix* matrix_C, Matrix* matrix_D, Matrix* matrix_E, int dimension, int num_threads);

/**
 * Função para fazer a gravação da matriz D e redução da matriz E.
 * @param matrix_E Ponteiro que armazena as infromações da matriz E
 * @param dimension Ordem da matriz
 * @param num_threads Número de threads
 * @return Retorna um inteiro de tipo long long int contendo a soma da operação de redução.
 * @throw Retorna 2 se alguma thread falhar, junto com uma mensagem de erro.
**/
long long int reduce(Matrix* matrix_E, int dimension, int num_threads);

#endif