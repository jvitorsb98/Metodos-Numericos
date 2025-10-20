#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Lê um sistema linear Ax = b de um arquivo.
 *
 * O arquivo deve começar com a ordem da matriz (n),
 * seguida pelos coeficientes da matriz A e do vetor b.
 *
 * @param nomeArquivo Caminho do arquivo de entrada.
 * @param ordemMatriz Ponteiro para inteiro onde será armazenada a ordem lida.
 * @return double** Matriz estendida [A|b] de tamanho n × (n+1).
 */
double** lerEntrada(const char* nomeArquivo, int* ordemMatriz);

/**
 * @brief Imprime no console a matriz estendida [A|b].
 *
 * @param matrizEstendida Matriz estendida [A|b].
 * @param ordemMatriz Ordem da matriz quadrada A.
 */
void imprimirMatriz(double** matrizEstendida, int ordemMatriz);

/**
 * @brief Libera a memória alocada para a matriz estendida.
 *
 * @param matrizEstendida Matriz estendida a ser liberada.
 * @param ordemMatriz Ordem da matriz quadrada A.
 */
void liberarMatriz(double** matrizEstendida, int ordemMatriz);

/**
 * @brief Cria um vetor de solução (x) com o tamanho da ordem.
 *
 * @param ordemMatriz Ordem da matriz (tamanho do vetor).
 * @return double* Vetor de solução alocado dinamicamente.
 */
double* criarVetorSolucao(int ordemMatriz);

/**
 * @brief Libera a memória alocada para o vetor de solução.
 *
 * @param vetorSolucao Vetor a ser liberado.
 */
void liberarVetorSolucao(double* vetorSolucao);

/**
 * @brief Imprime o vetor de solução no console.
 *
 * @param vetorSolucao Vetor solução calculado.
 * @param ordemMatriz Tamanho do vetor de solução.
 */
void imprimirSolucao(const double* vetorSolucao, int ordemMatriz);

/**
 * @brief Libera de uma vez a matriz estendida e o vetor solução.
 *
 * @param matrizEstendida Matriz estendida [A|b].
 * @param ordemMatriz Ordem da matriz quadrada A.
 * @param vetorSolucao Vetor de solução.
 */
void liberar(double** matrizEstendida, int ordemMatriz, double* vetorSolucao);

#endif
