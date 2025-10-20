#ifndef GAUSS_H
#define GAUSS_H

/**
 * @brief Status de retorno das rotinas do método de Gauss.
 */
typedef enum {
    GAUSS_OK = 0,           /**< Execução normal. */
    GAUSS_SINGULAR = 1,     /**< Sistema singular ou pivô ≈ 0 (sem solução única). */
    GAUSS_INCONSISTENTE = 2 /**< Sistema inconsistente (linha nula em A com b ≠ 0). */
} GaussStatus;

/**
 * @brief Executa o método de Gauss para resolver Ax = b.
 *
 * Combina eliminação e substituição regressiva.
 *
 * @param matrizEstendida Matriz [A|b], que será modificada durante o processo.
 * @param ordemMatriz Ordem n da matriz quadrada A.
 * @param vetorSolucao Vetor onde será armazenada a solução x.
 * @param tolerancia Limite mínimo para considerar um pivô ≈ 0.
 * @return GAUSS_OK se o sistema foi resolvido, ou outro status em caso de falha.
 */
GaussStatus gauss(double** matrizEstendida, int ordemMatriz, double* vetorSolucao, double tolerancia);

/**
 * @brief Realiza a substituição regressiva em uma matriz triangular superior.
 *
 * @param matrizEstendida Matriz [A|b], já triangular superior.
 * @param ordemMatriz Ordem n da matriz quadrada A.
 * @param vetorSolucao Vetor onde será armazenada a solução x.
 * @return GAUSS_OK se bem-sucedido, GAUSS_SINGULAR se algum pivô ≈ 0.
 */
GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao);

/**
 * @brief Realiza a etapa de eliminação de Gauss (sem pivotamento).
 *
 * Transforma a matriz estendida em forma triangular superior.
 *
 * @param matrizEstendida Matriz [A|b], que será modificada.
 * @param ordemMatriz Ordem n da matriz quadrada A.
 * @param tolerancia Limite mínimo para considerar um pivô ≈ 0.
 * @return GAUSS_OK se bem-sucedido, GAUSS_SINGULAR se pivô inválido encontrado.
 */
GaussStatus eliminacao(double** matrizEstendida, int ordemMatriz, double tolerancia);

/**
 * @brief Imprime no console o status retornado pelas funções de Gauss.
 *
 * @param status Valor do tipo GaussStatus a ser exibido.
 */
void imprimirStatus(GaussStatus status);

#endif
