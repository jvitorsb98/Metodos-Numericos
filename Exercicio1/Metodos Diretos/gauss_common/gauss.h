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
 * @brief Realiza a etapa de eliminação de Gauss (sem pivotamento) com tolerância.
 *
 * Transforma a matriz estendida [A|b] em forma triangular superior.
 * Caso algum pivô satisfaça |a_kk| < tolerância, retorna GAUSS_SINGULAR.
 *
 * @param matrizEstendida Matriz [A|b], que será modificada (n x (n+1)).
 * @param ordemMatriz Ordem n da matriz quadrada A.
 * @param tolerancia Limite mínimo para considerar um pivô ≈ 0.
 * @return GAUSS_OK se bem-sucedido; GAUSS_SINGULAR caso pivô inválido seja encontrado.
 */
GaussStatus eliminacao_com_tolerancia(double** matrizEstendida, int ordemMatriz, double tolerancia);

/**
 * @brief Realiza a etapa de eliminação de Gauss (sem pivotamento) sem checagens.
 *
 * Transforma a matriz estendida [A|b] em triangular superior sem verificar pivôs,
 * permitindo divisões por valores muito pequenos (modo diagnóstico).
 *
 * @param matrizEstendida Matriz [A|b], que será modificada (n x (n+1)).
 * @param ordemMatriz Ordem n da matriz A.
 * @return GAUSS_OK sempre (não aborta por pivô pequeno).
 */
GaussStatus eliminacao(double** matrizEstendida, int ordemMatriz);

/**
 * @brief Realiza a substituição regressiva (resolve Ux = c).
 *
 * @param matrizEstendida Matriz [A|b] em forma triangular superior.
 * @param ordemMatriz Ordem n da matriz A.
 * @param vetorSolucao Vetor onde será armazenada a solução x (tamanho n).
 * @return GAUSS_OK.
 */
GaussStatus substituicaoRegressiva(double** matrizEstendida, int ordemMatriz, double* vetorSolucao);

/**
 * @brief Executa o método de Gauss com verificação de tolerância.
 *
 * Durante a eliminação, pivôs com valor absoluto inferior à tolerância
 * são considerados nulos, retornando GAUSS_SINGULAR para indicar falha
 * de estabilidade ou singularidade.
 *
 * @param matrizEstendida Matriz [A|b], modificada durante o processo.
 * @param ordemMatriz Ordem n da matriz quadrada A.
 * @param vetorSolucao Vetor onde será armazenada a solução aproximada x.
 * @param tolerancia Valor mínimo aceito para um pivô (ex.: 1e-12).
 * @return GAUSS_OK se o sistema foi resolvido, GAUSS_SINGULAR caso pivô ≈ 0.
 */
GaussStatus gauss_com_tolerancia(double** matrizEstendida, int ordemMatriz,
                                 double* vetorSolucao, double tolerancia);

/**
 * @brief Resolve Ax = b via Gauss SEM guardas (eliminação sem checagens + regressiva).
 *
 * Útil para observar propagação de erros em casos mal-condicionados.
 *
 * @param matrizEstendida Matriz [A|b], modificada durante o processo.
 * @param ordemMatriz Ordem n de A.
 * @param vetorSolucao Vetor solução x (tamanho n).
 * @return GAUSS_OK.
 */
GaussStatus gauss(double** matrizEstendida, int ordemMatriz, double* vetorSolucao);

/**
 * @brief Imprime no console o status retornado pelas funções de Gauss.
 *
 * @param status Valor do tipo GaussStatus a ser exibido.
 */
void imprimirStatus(GaussStatus status);

#endif
