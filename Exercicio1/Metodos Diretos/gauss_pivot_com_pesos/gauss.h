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
 * @brief Eliminação de Gauss com pivotamento escalonado (com pesos) — COM tolerância.
 *
 * @details
 * Para cada coluna k:
 * - Calcula-se previamente os pesos de cada linha: s[i] = max_j |A[i,j]|;
 * - Seleciona-se como pivô a linha i ≥ k que maximiza |A[i,k]| / s[i];
 * - Troca-se as linhas k ↔ i, se necessário, mantendo consistência dos pesos;
 * - Zera-se os elementos abaixo do pivô na coluna k.
 *
 * Caso o melhor pivô encontrado seja menor que a tolerância, retorna GAUSS_SINGULAR.
 *
 * @param matrizEstendida Matriz aumentada [A|b], modificada in-place em [U|c].
 * @param ordemMatriz     Ordem n da matriz quadrada A.
 * @param tolerancia      Limite numérico para considerar pivô ≈ 0.
 * @return GAUSS_OK se sucesso, GAUSS_SINGULAR se pivô inválido.
 */
GaussStatus eliminacao_escalonada(double** matrizEstendida, int ordemMatriz, double tolerancia);

/**
 * @brief Eliminação de Gauss com pivotamento escalonado (com pesos) — SEM tolerância.
 *
 * @details
 * Mesma lógica da versão com tolerância, mas sem checagem de pivôs pequenos.
 * Útil para observar o efeito da instabilidade numérica sem abortar a execução.
 *
 * @param matrizEstendida Matriz aumentada [A|b], modificada in-place em [U|c].
 * @param ordemMatriz     Ordem n da matriz quadrada A.
 * @return GAUSS_OK sempre.
 */
GaussStatus eliminacao_escalonada_sem_tolerancia(double** matrizEstendida, int ordemMatriz);

/**
 * @brief Substituição regressiva em sistema triangular superior (Ux = c).
 *
 * @param matrizEstendida Matriz [U|c] já triangular superior.
 * @param ordemMatriz     Ordem n da matriz.
 * @param vetorSolucao    Vetor solução x (saída).
 * @return GAUSS_OK.
 */
GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao);

/**
 * @brief Resolve Ax = b via Gauss com pivotamento escalonado — COM tolerância.
 *
 * @details
 * Aplica @c eliminacao_escalonada seguida de @c substituicaoRegressiva.
 *
 * @param matrizEstendida Matriz [A|b], modificada in-place para [U|c].
 * @param ordemMatriz     Ordem n da matriz quadrada A.
 * @param vetorSolucao    Vetor solução x (saída).
 * @param tolerancia      Limite numérico para considerar pivô ≈ 0.
 * @return GAUSS_OK em sucesso, GAUSS_SINGULAR em falha.
 */
GaussStatus gauss_escalonado(double** matrizEstendida, int ordemMatriz, double* vetorSolucao, double tolerancia);

/**
 * @brief Resolve Ax = b via Gauss com pivotamento escalonado — SEM tolerância.
 *
 * @details
 * Aplica @c eliminacao_escalonada_sem_tolerancia seguida de @c substituicaoRegressiva.
 *
 * @param matrizEstendida Matriz [A|b], modificada in-place para [U|c].
 * @param ordemMatriz     Ordem n da matriz quadrada A.
 * @param vetorSolucao    Vetor solução x (saída).
 * @return GAUSS_OK.
 */
GaussStatus gauss_escalonado_sem_tolerancia(double** matrizEstendida, int ordemMatriz, double* vetorSolucao);

/**
 * @brief Imprime mensagem textual correspondente ao status do método de Gauss.
 *
 * @param status Código de retorno (GAUSS_OK, GAUSS_SINGULAR, GAUSS_INCONSISTENTE).
 */
void imprimirStatus(GaussStatus status);

#endif /* GAUSS_H */
