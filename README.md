# Projeto Prático - Multi-Thread em C
Projeto prático da matéria TT304 (Sistemas Operacionais) realizado no terceiro semestre do curso de Sistemas de Informação (FT, Unicamp).
Este readme contém algumas informações básicas sobre o projeto[¹].
[^1]: As demais informações estão no relatório do trabalho.

## Integrantes
- Celio Benhami Junior (246625)
- Gabriel Gato Piragini Santana (169025)

## Descrição do problema
O projeto consiste em um a série de operações com matrizes e manipulação de arquivos. 
Teremos 5 matrizes (A, B, C, D, E) e o algoritmo deve fazer operações com tais.

Para o projeto, podemos definir 3 tipos de thread:
1. __Thread de escrita (Te):__ Usada para gravação em arquivos.
2. __Thread de leitura (Tl):__ Usada para leitura de arquivos.
3. __Thread de processamento (Tp):__ Usada para as operações com matrizes (soma, multiplicação e redução). 

O projeto consiste em:
1. Leitura da Matriz A // Leitura da Matriz B ***(2 threads Tl)***
2. Soma das Matrizes A + B = D ***(T threads Tp)***
3. Gravação da Matriz D // Leitura da Matriz C ***(1 thread Te + 1 thread Tl)***
4. Multiplicação das Matrizes D x C = E ***(T threads Tp)***
5. Gravação da Matriz E // Redução da Matriz E ***(1 thread Te + T threads Tp)***

## Requisitos
1. Utilização da Linguagem C (pura)
2. Todos os dados necessários para a execução do programa devem ser repassadas por linha de comando.
	- Fomato: ./programa T n arqA.dat arqB.dat arqC.dat arqD.dat arqE.dat
4. Todos os arquivos de matrizes devem estar armazenados em formato texto.
5. Número de threads de processamento (T): 1, 2 ou 4.
6. Tamanho das matrizes (n): 100 ou 1000.
7. Caso tenhamos 1 thread, não devem ser criadas threads adicionais.
8. Para cada thread de processamento devemos calcular o tempo das operações, além de exibir o tempo total (soma dos 3 processos).
9. Todas as matrizes devem ser alocadas dinamicamente (não pode haver alocação estática).
10. As matrizes devem ser alocadas em uma única etapa.
11. O programa deve compilar sem erros.
12. Utilização de um makefile para compilação e execução

## Instruções para compilação
Para compilar o programa com todas as dependências necessárias basta digitar no terminal:
```
make
```
## Instruções para execução
Para executar o código basta digitar no terminal `make run-(T)-(n)`, em que T seja o número de threads e n o tamanho da matriz. 
Portanto, com todas as 6 variações possíveis temos:
```
make run-100-1
```
```
make run-100-2
```
```
make run-100-4
```
```
make run-1000-1
```
```
make run-1000-2
```
```
make run-1000-4
```

## Instruções para limpeza dos arquivos
Para excluir todos os arquivos gerados no processo de compilação e execução basta digitar o comando:
```
make clean
```
Para excluir as matrizes D e E (de qualquer pasta de teste) geradas no processo de execução deve-se executar:
```
make clean-de
```
Para excluir o diretório out (que contém os redirecionamento de saída do programa) é necessário o comando:
```
make clean-out
```
