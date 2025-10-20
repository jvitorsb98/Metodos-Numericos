#ifndef GAUSS_H
#define GAUSS_H

/**
 * @brief Códigos de retorno das rotinas de Gauss.
 */
typedef enum {
    GAUSS_OK = 0,          /**< Execução normal */
    GAUSS_SINGULAR = 1,    /**< Pivô ~ 0 → sistema singular/indeterminado */
    GAUSS_INCONSISTENTE = 2/**< Linha nula em A e b != 0 → sistema sem solução */
} GaussStatus;

/**
 * @brief Resolve Ax = b pelo método de Gauss com pivotamento total.
 *
 * @param matrizEstendida Matriz [A|b] (n × (n+1)).
 * @param ordemMatriz Ordem da matriz A.
 * @param vetorSolucao Vetor solução (saída), tamanho n.
 * @param tolerancia Valor usado para checar pivôs muito pequenos.
 * @return GAUSS_OK, GAUSS_SINGULAR ou GAUSS_INCONSISTENTE.
 */
GaussStatus gauss(double** matrizEstendida, int ordemMatriz, double* vetorSolucao, double tolerancia);

/**
 * @brief Executa a substituição regressiva após a eliminação.
 *
 * @param matrizEstendida Matriz [U|c] após a eliminação.
 * @param ordemMatriz Ordem da matriz.
 * @param vetorSolucao Vetor solução (saída).
 * @return GAUSS_OK ou GAUSS_SINGULAR.
 */
GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao);

/**
 * @brief Executa a fase de eliminação com pivotamento total.
 *
 * @param matrizEstendida Matriz [A|b] de entrada, modificada para [U|c].
 * @param ordemMatriz Ordem da matriz.
 * @param tolerancia Valor usado para checar pivôs muito pequenos.
 * @return GAUSS_OK ou GAUSS_SINGULAR.
 */
GaussStatus eliminacao(double** matrizEstendida, int ordemMatriz, double tolerancia);

/**
 * @brief Imprime em texto o status retornado pelas rotinas.
 *
 * @param status Código de retorno.
 */
void imprimirStatus(GaussStatus status);

#endif
