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
 * @brief Resolve Ax = b por Gauss com pivotamento parcial com pesos (scaled).
 *
 * Em cada coluna k, a linha pivô i ≥ k é escolhida maximizando
 * |A[i,k]| / s[i], onde s[i] = max_j |A[i,j]| (peso da linha).
 * Apenas troca de **linhas** é realizada.
 *
 * @param matrizEstendida Matriz [A|b], modificada in-place para [U|c].
 * @param ordemMatriz Ordem n da matriz A.
 * @param vetorSolucao Vetor solução (saída), tamanho n.
 * @param tolerancia Limite para considerar pivô ≈ 0.
 * @return GAUSS_OK se sucesso; GAUSS_SINGULAR/GAUSS_INCONSISTENTE em falha.
 */
GaussStatus gauss(double** matrizEstendida, int ordemMatriz, double* vetorSolucao, double tolerancia);

/**
 * @brief Substituição regressiva (resolve Ux = c após a eliminação).
 *
 * @param matrizEstendida Matriz [U|c] após a eliminação.
 * @param ordemMatriz Ordem n da matriz.
 * @param vetorSolucao Vetor solução (saída).
 * @return GAUSS_OK ou GAUSS_SINGULAR (se pivô da diagonal ≈ 0).
 */
GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao);

/**
 * @brief Eliminação de Gauss com pivotamento parcial com pesos.
 *
 * Para cada etapa k:
 *  - calcula/usa pesos s[i] = max_j |A[i,j]| (por linha);
 *  - escolhe i ≥ k que maximiza |A[i,k]| / s[i];
 *  - troca linhas k ↔ i (ponteiros);
 *  - zera elementos abaixo do pivô na coluna k.
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
 * @param status Código de retorno (GAUSS_OK, GAUSS_SINGULAR, GAUSS_INCONSISTENTE).
 */
void imprimirStatus(GaussStatus status);

#endif
