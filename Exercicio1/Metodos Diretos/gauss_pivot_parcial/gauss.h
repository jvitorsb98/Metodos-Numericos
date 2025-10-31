#ifndef GAUSS_H
#define GAUSS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Status de retorno das rotinas do método de Gauss.
 */
typedef enum {
    GAUSS_OK = 0,           /**< Execução normal. */
    GAUSS_SINGULAR = 1,     /**< Sistema singular/instável (pivô ≈ 0). */
    GAUSS_INCONSISTENTE = 2 /**< Sistema inconsistente (linha nula em A com b ≠ 0). */
} GaussStatus;

/**
 * @brief Executa a eliminação de Gauss com **pivotamento parcial** (troca de linhas) **com tolerância**.
 *
 * Em cada coluna k, escolhe-se a linha pivô i ≥ k com maior |A[i,k]|, realiza-se
 * a troca de linhas (se necessário) e elimina-se os elementos abaixo do pivô.
 * Se o módulo do pivô selecionado for menor que @p tolerancia, a função retorna
 * GAUSS_SINGULAR.
 *
 * @param matrizEstendida Matriz aumentada [A|b], modificada in-place para [U|c].
 *                        Dimensão: @p ordemMatriz linhas por (@p ordemMatriz + 1) colunas.
 * @param ordemMatriz     Ordem n da matriz A (n >= 1).
 * @param tolerancia      Limite abaixo do qual um pivô é considerado nulo (ex.: 1e-12).
 * @return GAUSS_OK em sucesso; GAUSS_SINGULAR se pivô inválido (≈0) for encontrado.
 */
GaussStatus eliminacao_com_tolerancia(double** matrizEstendida,
                                      int ordemMatriz,
                                      double tolerancia);

/**
 * @brief Executa a eliminação de Gauss com **pivotamento parcial** (troca de linhas) **sem tolerância**.
 *
 * Igual à versão com tolerância, porém não verifica o tamanho do pivô. Útil para
 * fins diagnósticos (observação de instabilidades). Pode resultar em estouro/NaN
 * se o pivô for muito pequeno.
 *
 * @param matrizEstendida Matriz aumentada [A|b], modificada in-place para [U|c].
 * @param ordemMatriz     Ordem n da matriz A (n >= 1).
 * @return GAUSS_OK (não aborta por pivô pequeno).
 */
GaussStatus eliminacao(double** matrizEstendida, int ordemMatriz);

/**
 * @brief Realiza a substituição regressiva em um sistema triangular superior Ux = c.
 *
 * Supõe que @p matrizEstendida encontra-se em forma triangular superior [U|c]
 * após a eliminação. Escreve a solução em @p vetorSolucao.
 *
 * @param matrizEstendida Matriz [U|c] (n linhas × (n+1) colunas).
 * @param ordemMatriz     Ordem n da matriz U.
 * @param vetorSolucao    Vetor de saída com a solução x (tamanho n).
 * @return GAUSS_OK em sucesso.
 */
GaussStatus substituicaoRegressiva(double** matrizEstendida,
                                   int ordemMatriz,
                                   double* vetorSolucao);

/**
 * @brief Resolve Ax = b por Gauss com pivotamento parcial **sem tolerância**.
 *
 * Wrapper que executa @ref eliminacao (sem tolerância) seguido de
 * @ref substituicaoRegressiva.
 *
 * @param matrizEstendida Matriz [A|b], modificada para [U|c] durante o processo.
 * @param ordemMatriz     Ordem n da matriz.
 * @param vetorSolucao    Vetor solução (saída), tamanho n.
 * @return GAUSS_OK em sucesso.
 */
GaussStatus gauss(double** matrizEstendida,
                  int ordemMatriz,
                  double* vetorSolucao);

/**
 * @brief Resolve Ax = b por Gauss com pivotamento parcial **com tolerância**.
 *
 * Wrapper que executa @ref eliminacao_com_tolerancia seguido de
 * @ref substituicaoRegressiva. Se um pivô for considerado nulo, retorna GAUSS_SINGULAR.
 *
 * @param matrizEstendida Matriz [A|b], modificada para [U|c] durante o processo.
 * @param ordemMatriz     Ordem n da matriz.
 * @param vetorSolucao    Vetor solução (saída), tamanho n.
 * @param tolerancia      Limite mínimo para o pivô (ex.: 1e-12).
 * @return GAUSS_OK em sucesso; GAUSS_SINGULAR se pivô ≈ 0.
 */
GaussStatus gauss_com_tolerancia(double** matrizEstendida,
                                 int ordemMatriz,
                                 double* vetorSolucao,
                                 double tolerancia);

/**
 * @brief Imprime, em texto, o significado do código de status.
 *
 * @param status Código retornado pelas rotinas (GAUSS_OK, GAUSS_SINGULAR, GAUSS_INCONSISTENTE).
 */
void imprimirStatus(GaussStatus status);

#ifdef __cplusplus
}
#endif

#endif /* GAUSS_H */
