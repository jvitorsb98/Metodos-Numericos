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
 * @brief Resolve Ax = b pelo método de Gauss com pivotamento parcial.
 *
 * O pivotamento parcial escolhe, em cada coluna k, a linha i ≥ k cujo |A[i,k]| é máximo,
 * e troca a linha k com essa linha i (apenas troca de linhas).
 *
 * @param matrizEstendida Matriz [A|b], modificada in-place durante o processo.
 * @param ordemMatriz Ordem n da matriz A.
 * @param vetorSolucao Vetor solução (saída), tamanho n.
 * @param tolerancia Limite para considerar pivô ≈ 0.
 * @return GAUSS_OK se sucesso, GAUSS_SINGULAR/GAUSS_INCONSISTENTE em falha.
 */
GaussStatus gauss(double** matrizEstendida, int ordemMatriz, double* vetorSolucao, double tolerancia);

/**
 * @brief Substituição regressiva em matriz triangular superior U.
 *
 * @param matrizEstendida Matriz [U|c] após a eliminação.
 * @param ordemMatriz Ordem n da matriz.
 * @param vetorSolucao Vetor solução (saída).
 * @return GAUSS_OK ou GAUSS_SINGULAR (se encontrar pivô ≈ 0).
 */
GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao);

/**
 * @brief Fase de eliminação com pivotamento parcial (troca de linhas).
 *
 * Em cada etapa k:
 *  - encontra i ≥ k que maximiza |A[i,k]|;
 *  - troca linhas k e i;
 *  - zera os elementos abaixo do pivô em A[* , k].
 *
 * @param matrizEstendida Matriz [A|b] (entrada) → [U|c] (saída), modificada in-place.
 * @param ordemMatriz Ordem n da matriz.
 * @param tolerancia Limite para considerar pivô ≈ 0.
 * @return GAUSS_OK ou GAUSS_SINGULAR.
 */
GaussStatus eliminacao(double** matrizEstendida, int ordemMatriz, double tolerancia);

/**
 * @brief Imprime em texto o status retornado.
 *
 * @param status Código de retorno.
 */
void imprimirStatus(GaussStatus status);

#endif
