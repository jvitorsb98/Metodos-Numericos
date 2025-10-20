#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Lê um sistema linear Ax = b de um arquivo.
 *
 * O arquivo deve conter:
 *  - Primeira linha: ordem da matriz (n).
 *  - Próximas n linhas: n coeficientes de A seguidos do termo b.
 *
 * @param nomeArquivo Nome do arquivo de entrada.
 * @param ordemMatriz Ponteiro para inteiro onde será armazenada a ordem da matriz.
 * @return Matriz estendida [A|b] de tamanho n × (n+1).
 */
double** lerEntrada(const char* nomeArquivo, int* ordemMatriz);

/**
 * @brief Imprime a matriz estendida [A|b] no console.
 *
 * @param matrizEstendida Matriz a ser impressa.
 * @param ordemMatriz Ordem da matriz quadrada A.
 */
void imprimirMatriz(double** matrizEstendida, int ordemMatriz);

/**
 * @brief Libera a memória alocada para a matriz estendida [A|b].
 *
 * @param matrizEstendida Matriz a ser liberada.
 * @param ordemMatriz Ordem da matriz quadrada A.
 */
void liberarMatriz(double** matrizEstendida, int ordemMatriz);

/**
 * @brief Cria (aloca) o vetor solução x.
 *
 * @param ordemMatriz Dimensão do sistema (n).
 * @return Ponteiro para vetor solução alocado.
 */
double* criarVetorSolucao(int ordemMatriz);

/**
 * @brief Libera a memória ocupada pelo vetor solução.
 *
 * @param vetorSolucao Vetor solução a ser liberado.
 */
void liberarVetorSolucao(double* vetorSolucao);

/**
 * @brief Imprime no console o vetor solução x.
 *
 * @param vetorSolucao Vetor solução.
 * @param ordemMatriz Dimensão do sistema.
 */
void imprimirSolucao(const double* vetorSolucao, int ordemMatriz);

/**
 * @brief Libera a matriz estendida [A|b] e o vetor solução de uma vez.
 *
 * @param matrizEstendida Matriz a ser liberada.
 * @param ordemMatriz Ordem da matriz quadrada A.
 * @param vetorSolucao Vetor solução a ser liberado.
 */
void liberar(double** matrizEstendida, int ordemMatriz, double* vetorSolucao);

#endif
